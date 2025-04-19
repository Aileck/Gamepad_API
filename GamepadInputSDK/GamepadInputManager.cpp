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
		for (int i = 0; i < MAX_GAMEPADS; ++i) {
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

				*id = i;
				std::cout << "Virtual controller assigned to user index: " << index << std::endl;

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

	const Gamepad_Result GamepadInputManager::xboxPressButton(int id, _XUSB_BUTTON button)
	{
		XUSB_REPORT report;
		ZeroMemory(&report, sizeof(report));
		report.wButtons = button;
		vigem_target_x360_update(client, pads[id], report);
		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	const Gamepad_Result GamepadInputManager::xboxReleaseButton(int id)
	{
		XUSB_REPORT report;
		ZeroMemory(&report, sizeof(report));
		report.wButtons = 0;
		vigem_target_x360_update(client, pads[id], report);
		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	const Gamepad_Result GamepadInputManager::xboxMoveThumb(int id, bool leftStick, SHORT x, SHORT y)
	{
		const std::string stick = (leftStick) ? "left " : "right ";
		std::cout << "Moving " << stick << "with values " << x << "," << y << std::endl;
		XUSB_REPORT report;
		ZeroMemory(&report, sizeof(report));

		if (leftStick)
		{
			report.sThumbLX = x;
			report.sThumbLY = y;
		}
		else
		{
			report.sThumbRX = x;
			report.sThumbRY = y;
		}

		vigem_target_x360_update(client, pads[id], report);
		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	const Gamepad_Result GamepadInputManager::xboxReleaseThumb(int id, bool leftStick)
	{
		XUSB_REPORT report;
		ZeroMemory(&report, sizeof(report));

		if (leftStick)
		{
			report.sThumbLX = 0;
			report.sThumbLY = 0;
		}
		else {
			report.sThumbRX = 0;
			report.sThumbRY = 0;
		}


		vigem_target_x360_update(client, pads[id], report);
		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	const Gamepad_Result GamepadInputManager::xboxPressTrigger(int id, bool leftTrigger, BYTE val)
	{
		XUSB_REPORT report;
		ZeroMemory(&report, sizeof(report));

		if (leftTrigger)
		{
			report.bLeftTrigger = val;
		}
		else
		{
			report.bRightTrigger = val;
		}

		vigem_target_x360_update(client, pads[id], report);
		return Gamepad_Result{ 1, VIGEM_ERROR_NONE };
	}

	const Gamepad_Result GamepadInputManager::xboxReleaseTrigger(int id, bool leftTrigger)
	{
		XUSB_REPORT report;
		ZeroMemory(&report, sizeof(report));

		if (leftTrigger)
		{
			report.bLeftTrigger = 0;
		}
		else if (leftTrigger)
		{
			report.bRightTrigger = 0;
		}

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

	GAMEPAD_API Gamepad_Result xbox_press_a(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_A);
	}

	GAMEPAD_API Gamepad_Result xbox_press_b(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_B);
	}

	GAMEPAD_API Gamepad_Result xbox_press_x(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_X);
	}

	GAMEPAD_API Gamepad_Result xbox_press_y(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_Y);
	}

	GAMEPAD_API Gamepad_Result xbox_press_start(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_START);
	}

	GAMEPAD_API Gamepad_Result xbox_press_back(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_BACK);
	}

	GAMEPAD_API Gamepad_Result xbox_press_dpad_up(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_DPAD_UP);
	}

	GAMEPAD_API Gamepad_Result xbox_press_dpad_down(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_DPAD_DOWN);
	}

	GAMEPAD_API Gamepad_Result xbox_press_dpad_left(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_DPAD_LEFT);
	}

	GAMEPAD_API Gamepad_Result xbox_press_dpad_right(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_DPAD_RIGHT);
	}

	GAMEPAD_API Gamepad_Result xbox_press_left_shoulder(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_LEFT_SHOULDER);
	}

	GAMEPAD_API Gamepad_Result xbox_press_right_shoulder(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_RIGHT_SHOULDER);
	}

	GAMEPAD_API Gamepad_Result xbox_press_left_thumb(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_LEFT_THUMB);
	}

	GAMEPAD_API Gamepad_Result xbox_press_right_thumb(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressButton(id, XUSB_GAMEPAD_RIGHT_THUMB);
	}

	GAMEPAD_API Gamepad_Result xbox_release_button(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxReleaseButton(id);
	}

	// Xbox controller thumb press simulation

	GAMEPAD_API Gamepad_Result xbox_move_stick_left(int id, int x, int y)
	{
		std::cout << "ID " << id << std::endl;
		std::cout << "Try to move " << x << ", " << y << std::endl;
		std::cout << "After conversion " << static_cast<SHORT>(x) << ", " << static_cast<SHORT>(y) << std::endl;

		return gamepadmanager::GamepadInputManager::getInstance().xboxMoveThumb(
			id, true, static_cast<SHORT>(x), static_cast<SHORT>(y));
	}

	GAMEPAD_API Gamepad_Result xbox_move_stick_right(int id, int x, int y)
	{

		return gamepadmanager::GamepadInputManager::getInstance().xboxMoveThumb(
			id, false, static_cast<SHORT>(x), static_cast<SHORT>(y));
	}

	GAMEPAD_API Gamepad_Result xbox_release_stick_left(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxReleaseThumb(id, true);
	}

	GAMEPAD_API Gamepad_Result xbox_release_stick_right(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxReleaseThumb(id, false);
	}


	// Xbox controller trigger press simulation

	GAMEPAD_API Gamepad_Result xbox_press_trigger_left(int id, int val)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressTrigger(id, true, static_cast<BYTE>(val));
	}

	GAMEPAD_API Gamepad_Result xbox_press_trigger_right(int id, int val)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxPressTrigger(id, false, static_cast<BYTE>(val));
	}

	GAMEPAD_API Gamepad_Result xbox_release_trigger_left(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxReleaseTrigger(id, true);
	}

	GAMEPAD_API Gamepad_Result xbox_release_trigger_right(int id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxReleaseTrigger(id, false);
	}
}