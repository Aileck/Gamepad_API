#include "pch.h"
#include "GamepadAPI.h"
#include "GamepadInputManager.h"
#include "GamepadSharedAction.h"

extern "C" {

	// System
	GAMEPAD_API Gamepad_Result gamepadmanager::initialize()
	{
		return gamepadmanager::GamepadInputManager::getInstance().initializeManager();
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::release()
	{
		return gamepadmanager::GamepadInputManager::getInstance().cleanUp();
	}

	// XBOX

	GAMEPAD_API Gamepad_Result gamepadmanager::create_xbox_controller(int& id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().createGamepad(&id, GAMEPAD_TYPE::GAMEPAD_XBOX);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_up(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_UP, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_down(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_DOWN, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_left(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_LEFT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_right(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_RIGHT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_a(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_A, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_b(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_B, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_x(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_X, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_y(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_Y, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_left_stick(int id, SHORT x, SHORT y)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputStick(id, DIRECTION::LEFT, x, y);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_right_stick(int id, SHORT x, SHORT y)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputStick(id, DIRECTION::RIGHT, x, y);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_lb(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_LEFT_SHOULDER, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_rb(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_RIGHT_SHOULDER, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_lt(int id, int val)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputTrigger(id, DIRECTION::LEFT, val);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_rt(int id, int val)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputTrigger(id, DIRECTION::RIGHT, val);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_left_analog_button(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_LEFT_THUMB, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_right_analog_button(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_RIGHT_THUMB, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_start(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_START, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_back(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_BACK, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadmanager::xbox_input_guide(int id, bool keydown)
	{
		return gamepadmanager::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_GUIDE, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}
}