#include "pch.h"
#include "GamepadInputManager.h"

#include <iostream>
#include <Xinput.h>
#include <thread>
#include <chrono>

namespace gamepadmanager
{
	GamepadInputManager& gamepadmanager::GamepadInputManager::getInstance()
	{
		static GamepadInputManager instance;
		return instance;
	}

	GamepadInputManager::GamepadInputManager() : client(nullptr), retval(VIGEM_ERROR_NONE)
	{
	}

	gamepadmanager::GamepadInputManager::~GamepadInputManager()
	{
		release();
	}

	const Gamepad_Result gamepadmanager::GamepadInputManager::initializeManager()
	{
		// Allocate a VIGEM client
		client = vigem_alloc();
		if (client == nullptr) {
			return Gamepad_Result{0, VIGEM_ERROR_BUS_NOT_FOUND };
		}

		// Initialize the VIGEM client
		retval = vigem_connect(client);
		if (retval != VIGEM_ERROR_NONE) {
			vigem_free(client);
			std::cerr << "VIGEM Bus connection failed with error code: 0x" << std::hex << retval << std::endl;
			return Gamepad_Result{ 0, VIGEM_ERROR_BUS_NOT_FOUND };
		}

		// Reserve memory for the gamepad targets
		pads.reserve(MAX_GAMEPADS);

		for (size_t i = 0; i < MAX_GAMEPADS; ++i) {
			pads.push_back(nullptr);
		}

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	const Gamepad_Result gamepadmanager::GamepadInputManager::createXboxController(int* id)
	{
		// Get first not null target from pads list
		for (size_t i = 0; i < MAX_GAMEPADS; ++i) {
			if (pads[i] == nullptr) {
				pads[i] = vigem_target_x360_alloc();

				const auto pir = vigem_target_add(client, pads[i]);
				if (!VIGEM_SUCCESS(pir)) {
					std::cerr << "Target plugin failed with error code: 0x" << std::hex << pir << std::endl;
					return Gamepad_Result{ 0, VIGEM_ERROR_BUS_NOT_FOUND };
				}

				XINPUT_STATE state;
				XInputGetState(0, &state);

				vigem_target_x360_update(client, pads[i], *reinterpret_cast<XUSB_REPORT*>(&state.Gamepad));
			
				ULONG index;
				vigem_target_x360_get_user_index(client, pads[i], &index);
				std::cout << "Virtual controller assigned to user index: " << index << std::endl;

				*id = static_cast<int>(i);

				return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
			}
		}

		return Gamepad_Result{ 0, VIGEM_ERROR_NO_FREE_SLOT };
	}

	const Gamepad_Result gamepadmanager::GamepadInputManager::releaseManager()
	{
		for (size_t i = 0; i < MAX_GAMEPADS; i++)
		{
			if (pads[i] != nullptr) {
				vigem_target_remove(client, pads[i]);
				vigem_target_free(pads[i]);
				pads[i] = nullptr;
			}
		}

		vigem_disconnect(client);
		vigem_free(client);

		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}
	const Gamepad_Result GamepadInputManager::xboxDownDPad(int id)
	{
		XUSB_REPORT report;
		ZeroMemory(&report, sizeof(report));

		report.wButtons = XUSB_GAMEPAD_DPAD_DOWN;
		vigem_target_x360_update(client, pads[id], report);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		report.wButtons = 0;
		vigem_target_x360_update(client, pads[id], report);


		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}
}


extern "C" {

	GAMEPAD_API Gamepad_Result initialize()
	{
		return gamepadmanager::GamepadInputManager::getInstance().initializeManager();
	}

	GAMEPAD_API Gamepad_Result create_xbox_controller(int &id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().createXboxController(&id);
	}

	GAMEPAD_API Gamepad_Result release()
	{
		return gamepadmanager::GamepadInputManager::getInstance().releaseManager();
	}

	GAMEPAD_API Gamepad_Result xbox_down_dpad_controller(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxDownDPad(id);
	}

}