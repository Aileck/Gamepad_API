#include "pch.h"
#include "GamepadAPI.h"
#include "GamepadInputManager.h"

using namespace gamepadmanager;

extern "C" {

	GAMEPAD_API Gamepad_Result initialize()
	{
		return gamepadmanager::GamepadInputManager::getInstance().initializeManager();
	}

	GAMEPAD_API Gamepad_Result create_xbox_controller(int& id)
	{
		return gamepadmanager::GamepadInputManager::getInstance().createXboxController(&id);
	}

	GAMEPAD_API Gamepad_Result release()
	{
		return gamepadmanager::GamepadInputManager::getInstance().cleanUp();
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