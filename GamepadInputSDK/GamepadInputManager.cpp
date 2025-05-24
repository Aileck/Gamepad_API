#include "pch.h"
#include "GamepadInputManager.h"
#include "Xbox.h"
#include "DS4.h"
#include "Gamepad.h"

#include <iostream>
#include <Xinput.h>
#include <thread>
#include <chrono>
#include <memory>

namespace gamepadapi
{
	GamepadInputManager& gamepadapi::GamepadInputManager::getInstance()
	{
		static GamepadInputManager instance;
		return instance;
	}

	GamepadInputManager::GamepadInputManager()
	{
		client = nullptr;
		session = 1;
	}

	GamepadInputManager::~GamepadInputManager()
	{
		cleanUp();
	}

	Gamepad_Result GamepadInputManager::initializeManager()
	{		
		// Allocate a VIGEM client
		client = vigem_alloc();
		if (client == nullptr) {
			return Gamepad_Result{0, VIGEM_ERROR_BUS_NOT_FOUND };
		}

		// Initialize the VIGEM client
		VIGEM_ERROR retval = vigem_connect(client);
		if (retval != VIGEM_ERROR_NONE) {
			vigem_free(client);
			std::cerr << "VIGEM Bus connection failed with error code: 0x" << std::hex << retval << std::endl;
			return Gamepad_Result{ 0, VIGEM_ERROR_BUS_NOT_FOUND };
		}

		// Reserve memory for the gamepad targets
		gamepads.reserve(MAX_GAMEPADS);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::createGamepad(int* id, GAMEPAD_TYPE type)
	{
		Gamepad_Result result = Gamepad_Result{ 0, VIGEM_ERROR_NOT_SUPPORTED };

		if (gamepads.size() >= MAX_GAMEPADS)
		{
			return Gamepad_Result{ 0, VIGEM_ERROR_NO_FREE_SLOT };
		}

		if (type == GAMEPAD_TYPE::GAMEPAD_XBOX360)
		{
			result = createXbox360Gamepad(id);
		}
		else if (type == GAMEPAD_TYPE::GAMEPAD_DUALSHOCK4)
		{
			result = createDualShock4Gamepad(id);
		}

		// Check if the gamepad was created successfully
		if (result.status == 1)
		{
			incrementSession();
		}

		return result;
	}

	Gamepad_Result GamepadInputManager::createXbox360Gamepad(int* id)
	{
		PVIGEM_TARGET pad = vigem_target_x360_alloc();

		const auto pir = vigem_target_add(client, pad);
		if (!VIGEM_SUCCESS(pir)) {
			std::cerr << "Target plugin failed with error code: 0x" << std::hex << pir << std::endl;
			return Gamepad_Result{ 0, VIGEM_ERROR_BUS_NOT_FOUND };
		}

		gamepads[session] = std::make_shared<Xbox>(pad);

		*id = session;
		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::createDualShock4Gamepad(int* id)
	{
		PVIGEM_TARGET pad = vigem_target_ds4_alloc();

		const auto pir = vigem_target_add(client, pad);
		if (!VIGEM_SUCCESS(pir)) {
			std::cerr << "DS4 target plugin failed with error code: 0x" << std::hex << pir << std::endl;
			return Gamepad_Result{ 0, VIGEM_ERROR_BUS_NOT_FOUND };
		}

		gamepads[session] = std::make_shared<DS4>(pad);

		*id = session;
		std::cout << "DS4 virtual controller assigned to session: " << session << std::endl;

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}
	Gamepad_Result GamepadInputManager::cleanUp()
	{
		for (auto & gamepad : gamepads)
		{
			if (gamepad.second != nullptr)
			{
				vigem_target_remove(client, gamepad.second->GetPadID());
				vigem_target_free(gamepad.second->GetPadID());
			}
		}

		gamepads.clear();

		vigem_disconnect(client);
		vigem_free(client);

		resetSession();

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::releaseGamepad(int id) {
		std::shared_ptr<Gamepad> gemepad = gamepads[id];
		
		try 
		{
			vigem_target_remove(client, gemepad->GetPadID());
			vigem_target_free(gemepad->GetPadID());

			return Gamepad_Result{ 1, VIGEM_ERROR_NONE };

		}
		catch (...) {
			return Gamepad_Result{ 0, VIGEM_ERROR_BUS_NOT_FOUND };
		}
	}


	// *******
	// XBOX
	// *******

	Gamepad_Result GamepadInputManager::xboxInputButton(int id, XUSB_BUTTON button, BUTTON_STATE state)
	{
		std::shared_ptr<Xbox> xboxGamepad = std::static_pointer_cast<Xbox>(gamepads[id]);

		PXUSB_REPORT report = xboxGamepad->handleInputButton(button, state);

		vigem_target_x360_update(client, xboxGamepad->GetPadID(), *report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::xboxInputStick(int id, DIRECTION direction, SHORT x, SHORT y)
	{
		std::shared_ptr<Xbox> xboxGamepad = std::static_pointer_cast<Xbox>(gamepads[id]);

		PXUSB_REPORT report = xboxGamepad->handleInputStick(direction, x, y);

		vigem_target_x360_update(client, xboxGamepad->GetPadID(), *report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::xboxInputTrigger(int id, DIRECTION direction, BYTE val)
	{
		std::shared_ptr<Xbox> xboxGamepad = std::static_pointer_cast<Xbox>(gamepads[id]);

		PXUSB_REPORT report = xboxGamepad->HandleInputTrigger(direction, val);

		vigem_target_x360_update(client, xboxGamepad->GetPadID(), *report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	// *******
	// DUALSHOCK4
	// *******

	Gamepad_Result GamepadInputManager::ds4InputButton(int id, DS4_BUTTONS button, BUTTON_STATE state)
	{
		std::shared_ptr<DS4> ds4Gamepad = std::static_pointer_cast<DS4>(gamepads[id]);
		
		PDS4_REPORT report = ds4Gamepad->handleInputButton(button, state);
		
		vigem_target_ds4_update(client, ds4Gamepad->GetPadID(), *report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::ds4InputSpecial(int id, DS4_SPECIAL_BUTTONS button, BUTTON_STATE state)
	{
		std::shared_ptr<DS4> ds4Gamepad = std::static_pointer_cast<DS4>(gamepads[id]);
		PDS4_REPORT report = ds4Gamepad->handleInputSpecial(button, state);
		
		vigem_target_ds4_update(client, ds4Gamepad->GetPadID(), *report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::ds4InputDpad(int id, DS4_DPAD_DIRECTIONS button, BUTTON_STATE state)
	{
		std::shared_ptr<DS4> ds4Gamepad = std::static_pointer_cast<DS4>(gamepads[id]);
		PDS4_REPORT report = ds4Gamepad->handleInputDpad(button, state);

		vigem_target_ds4_update(client, ds4Gamepad->GetPadID(), *report);
		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::ds4InputStick(int id, DIRECTION direction, BYTE x, BYTE y)
	{
		std::shared_ptr<DS4> ds4Gamepad = std::static_pointer_cast<DS4>(gamepads[id]);
		PDS4_REPORT report = ds4Gamepad->handleInputStick(direction, x, y);

		vigem_target_ds4_update(client, ds4Gamepad->GetPadID(), *report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::ds4InputTrigger(int id, DIRECTION direction, BYTE val)
	{
		std::shared_ptr<DS4> ds4Gamepad = std::static_pointer_cast<DS4>(gamepads[id]);
		PDS4_REPORT report = ds4Gamepad->HandleInputTrigger(direction, val);

		vigem_target_ds4_update(client, ds4Gamepad->GetPadID(), *report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}
}