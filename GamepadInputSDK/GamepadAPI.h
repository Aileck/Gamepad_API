#pragma once
#include "pch.h"
#include "GamepadResult.h"

#ifdef __cplusplus
extern "C" {
	namespace gamepadapi {

#endif

	GAMEPAD_API Gamepad_Result initialize();
	GAMEPAD_API Gamepad_Result release();

	// Xbox360
	GAMEPAD_API Gamepad_Result create_xbox_controller(int& id);

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

	// DUALSHOCK4
	GAMEPAD_API Gamepad_Result create_dualshock4_controller(int& id);

	GAMEPAD_API Gamepad_Result ds4_input_up(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_down(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_left(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_right(int id, bool keydown);

	GAMEPAD_API Gamepad_Result ds4_input_up_left(int id, bool keydown);    
	GAMEPAD_API Gamepad_Result ds4_input_up_right(int id, bool keydown);    
	GAMEPAD_API Gamepad_Result ds4_input_down_left(int id, bool keydown);  
	GAMEPAD_API Gamepad_Result ds4_input_down_right(int id, bool keydown); 

	GAMEPAD_API Gamepad_Result ds4_input_square(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_triangle(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_circle(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_cross(int id, bool keydown);

	GAMEPAD_API Gamepad_Result ds4_input_left_stick(int id, SHORT x, SHORT y);
	GAMEPAD_API Gamepad_Result ds4_input_right_stick(int id, SHORT x, SHORT y);
	GAMEPAD_API Gamepad_Result ds4_input_l1(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_r1(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_l2(int id, int val);
	GAMEPAD_API Gamepad_Result ds4_input_r2(int id, int val);
	GAMEPAD_API Gamepad_Result ds4_input_l3(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_r3(int id, bool keydown);

	GAMEPAD_API Gamepad_Result ds4_input_share(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_options(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_touchpad(int id, bool keydown);
	GAMEPAD_API Gamepad_Result ds4_input_ps(int id, bool keydown);

#ifdef __cplusplus
	}
}
#endif
