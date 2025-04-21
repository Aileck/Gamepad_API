#include "pch.h"
#include "GamepadAPI.h"
#include "GamepadInputManager.h"
#include "GamepadSharedAction.h"

extern "C" {

	// System
	GAMEPAD_API Gamepad_Result gamepadapi::initialize()
	{
		return gamepadapi::GamepadInputManager::getInstance().initializeManager();
	}

	GAMEPAD_API Gamepad_Result gamepadapi::release()
	{
		return gamepadapi::GamepadInputManager::getInstance().cleanUp();
	}

	// XBOX

	GAMEPAD_API Gamepad_Result gamepadapi::create_xbox_controller(int& id)
	{
		return gamepadapi::GamepadInputManager::getInstance().createGamepad(&id, GAMEPAD_TYPE::GAMEPAD_XBOX360);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_up(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_UP, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_down(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_DOWN, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_left(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_LEFT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_right(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_DPAD_RIGHT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_a(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_A, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_b(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_B, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_x(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_X, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_y(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_Y, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_left_stick(int id, SHORT x, SHORT y)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputStick(id, DIRECTION::LEFT, x, y);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_right_stick(int id, SHORT x, SHORT y)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputStick(id, DIRECTION::RIGHT, x, y);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_lb(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_LEFT_SHOULDER, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_rb(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_RIGHT_SHOULDER, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_lt(int id, int val)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputTrigger(id, DIRECTION::LEFT, val);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_rt(int id, int val)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputTrigger(id, DIRECTION::RIGHT, val);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_left_analog_button(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_LEFT_THUMB, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_right_analog_button(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_RIGHT_THUMB, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_start(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_START, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_back(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_BACK, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::xbox_input_guide(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().xboxInputButton(id, XUSB_GAMEPAD_GUIDE, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	// DUALSHOCK4
	GAMEPAD_API Gamepad_Result gamepadapi::create_dualshock4_controller(int& id)
	{
		return gamepadapi::GamepadInputManager::getInstance().createGamepad(&id, GAMEPAD_TYPE::GAMEPAD_DUALSHOCK4);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_up(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_NORTH, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_down(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_SOUTH, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_left(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_WEST, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_right(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_EAST, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_up_left(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_NORTHWEST, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_up_right(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_NORTHEAST, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_down_left(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_SOUTHWEST, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_down_right(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputDpad(id, DS4_BUTTON_DPAD_SOUTHEAST, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_square(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_SQUARE, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_triangle(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_TRIANGLE, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_circle(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_CIRCLE, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_cross(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_CROSS, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_left_stick(int id, SHORT x, SHORT y)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputStick(id, DIRECTION::LEFT, x, y);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_right_stick(int id, SHORT x, SHORT y)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputStick(id, DIRECTION::RIGHT, x, y);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_l1(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_SHOULDER_LEFT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_r1(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_SHOULDER_RIGHT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_l2(int id, int val)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputTrigger(id, DIRECTION::LEFT, val);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_r2(int id, int val)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputTrigger(id, DIRECTION::RIGHT, val);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_l3(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_THUMB_LEFT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_r3(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_THUMB_RIGHT, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_share(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_SHARE, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_options(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputButton(id, DS4_BUTTON_OPTIONS, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_touchpad(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputSpecial(id, DS4_SPECIAL_BUTTON_TOUCHPAD, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}

	GAMEPAD_API Gamepad_Result gamepadapi::ds4_input_ps(int id, bool keydown)
	{
		return gamepadapi::GamepadInputManager::getInstance().ds4InputSpecial(id, DS4_SPECIAL_BUTTON_PS, keydown ? BUTTON_STATE::PRESSED : BUTTON_STATE::RELEASED);
	}
}