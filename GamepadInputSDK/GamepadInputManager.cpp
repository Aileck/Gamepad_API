#include "pch.h"
#include "GamepadInputManager.h"
#include "Xbox.h"
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
		session = 0;
	}

	gamepadapi::GamepadInputManager::~GamepadInputManager()
	{
		cleanUp();
	}

	Gamepad_Result gamepadapi::GamepadInputManager::initializeManager()
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

		if (type == GAMEPAD_TYPE::GAMEPAD_XBOX)
		{
			result = createXboxGamepad(id);
		}
		else if (type == GAMEPAD_TYPE::GAMEPAD_PS4)
		{
			result = Gamepad_Result{ 0, VIGEM_ERROR_NOT_SUPPORTED };
		}

		// Check if the gamepad was created successfully
		if (result.STATUS == 1)
		{
			incrementSession();
		}

		return result;
	}

	Gamepad_Result GamepadInputManager::createXboxGamepad(int* id)
	{
		PVIGEM_TARGET pad = vigem_target_x360_alloc();

		const auto pir = vigem_target_add(client, pad);
		if (!VIGEM_SUCCESS(pir)) {
			std::cerr << "Target plugin failed with error code: 0x" << std::hex << pir << std::endl;
			return Gamepad_Result{ 0, VIGEM_ERROR_BUS_NOT_FOUND };
		}

		XINPUT_STATE state;
		XInputGetState(0, &state);

		vigem_target_x360_update(client, pad, *reinterpret_cast<XUSB_REPORT*>(&state.Gamepad));

		ULONG index;
		vigem_target_x360_get_user_index(client, pad, &index);
		std::cout << "Virtual controller assigned to user index: " << index << std::endl;

		gamepads[session] = std::make_shared<Xbox>(pad, index);

		*id = session;
		std::cout << "Virtual controller assigned to user index: " << index << std::endl;

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result gamepadapi::GamepadInputManager::cleanUp()
	{
		vigem_disconnect(client);
		vigem_free(client);

		resetSession();

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	// *******
	// XBOX
	// *******

	Gamepad_Result GamepadInputManager::xboxInputButton(int id, _XUSB_BUTTON button, BUTTON_STATE state)
	{
		std::shared_ptr<Xbox> xboxGamepad = std::static_pointer_cast<Xbox>(gamepads[id]);

		XUSB_REPORT report = xboxGamepad->handleInputButton(button, state);

		vigem_target_x360_update(client, gamepads[id]->GetPadID(), report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::xboxInputStick(int id, DIRECTION direction, SHORT x, SHORT y)
	{
		std::shared_ptr<Xbox> xboxGamepad = std::static_pointer_cast<Xbox>(gamepads[id]);

		XUSB_REPORT report = xboxGamepad->handleInputStick(direction, x, y);

		vigem_target_x360_update(client, gamepads[id]->GetPadID(), report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	Gamepad_Result GamepadInputManager::xboxInputTrigger(int id, DIRECTION direction, BYTE val)
	{
		std::shared_ptr<Xbox> xboxGamepad = std::static_pointer_cast<Xbox>(gamepads[id]);

		XUSB_REPORT report = xboxGamepad->HandleInputTrigger(direction, val);

		vigem_target_x360_update(client, gamepads[id]->GetPadID(), report);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}
}