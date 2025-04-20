#pragma once
#include "pch.h"
#include "GamepadResult.h"

#ifdef __cplusplus
extern "C" {
	namespace gamepadmanager {

#endif

	GAMEPAD_API Gamepad_Result initialize();
	GAMEPAD_API Gamepad_Result create_xbox_controller(int& id);
	GAMEPAD_API Gamepad_Result release();

	// Xbox controller button press simulation

	GAMEPAD_API Gamepad_Result xbox_input_up(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_down(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_left(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_right(int id, bool keydown);

	GAMEPAD_API Gamepad_Result xbox_input_a(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_b(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_x(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_y(int id, bool keydown);

	GAMEPAD_API Gamepad_Result xbox_input_left_stick(int id, SHORT x, SHORT y);
	GAMEPAD_API Gamepad_Result xbox_input_right_stick(int id, SHORT x, SHORT y);

	GAMEPAD_API Gamepad_Result xbox_input_lb(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_rb(int id, bool keydown);

	GAMEPAD_API Gamepad_Result xbox_input_lt(int id, int val);
	GAMEPAD_API Gamepad_Result xbox_input_rt(int id, int val);

	GAMEPAD_API Gamepad_Result xbox_input_left_analog_button(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_right_analog_button(int id, bool keydown);

	GAMEPAD_API Gamepad_Result xbox_input_start(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_back(int id, bool keydown);
	GAMEPAD_API Gamepad_Result xbox_input_guide(int id, bool keydown);


#ifdef __cplusplus
	}
}
#endif
