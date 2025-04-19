#pragma once
#include "pch.h"
#include "globals.h"
#include "GamepadResult.h"
#include <ViGEm/Client.h>
#include <vector>

namespace gamepadmanager
{
    class GAMEPAD_API GamepadInputManager
    {
    public:
        // Singleton manager
        static GamepadInputManager& getInstance();

        const Gamepad_Result initializeManager();
        const Gamepad_Result createXboxController(int* id);
        const Gamepad_Result releaseManager();
        const Gamepad_Result xboxPressButton(int id, _XUSB_BUTTON button);
        const Gamepad_Result xboxReleaseButton(int id);

		const Gamepad_Result xboxMoveThumb(int id, bool leftStick, SHORT x, SHORT y);
        const Gamepad_Result xboxReleaseThumb(int id, bool leftStick);

        const Gamepad_Result xboxPressTrigger(int id, bool leftTrigger, BYTE val);
		const Gamepad_Result xboxReleaseTrigger(int id, bool leftTrigger);

    private:
        GamepadInputManager();
        ~GamepadInputManager();
        GamepadInputManager(const GamepadInputManager&) = delete;
        GamepadInputManager& operator=(const GamepadInputManager&) = delete;

        PVIGEM_CLIENT client;
        VIGEM_ERROR retval;
        std::vector<PVIGEM_TARGET> pads;
    };

    extern "C" {
        GAMEPAD_API Gamepad_Result initialize();
        GAMEPAD_API Gamepad_Result create_xbox_controller(int &id);
        GAMEPAD_API Gamepad_Result release();

		// Xbox controller button press simulation
        GAMEPAD_API Gamepad_Result xbox_press_a(int id);
		GAMEPAD_API Gamepad_Result xbox_press_b(int id);
		GAMEPAD_API Gamepad_Result xbox_press_x(int id);
		GAMEPAD_API Gamepad_Result xbox_press_y(int id);

		GAMEPAD_API Gamepad_Result xbox_press_start(int id);
		GAMEPAD_API Gamepad_Result xbox_press_back(int id);

		GAMEPAD_API Gamepad_Result xbox_press_dpad_up(int id);
		GAMEPAD_API Gamepad_Result xbox_press_dpad_down(int id);
		GAMEPAD_API Gamepad_Result xbox_press_dpad_left(int id);
		GAMEPAD_API Gamepad_Result xbox_press_dpad_right(int id);

		GAMEPAD_API Gamepad_Result xbox_press_left_shoulder(int id);
		GAMEPAD_API Gamepad_Result xbox_press_right_shoulder(int id);

        GAMEPAD_API Gamepad_Result xbox_press_left_thumb(int id);
        GAMEPAD_API Gamepad_Result xbox_press_right_thumb(int id);

		GAMEPAD_API Gamepad_Result xbox_release_button(int id);

		GAMEPAD_API Gamepad_Result xbox_move_stick_left(int id, int x, int y);
        GAMEPAD_API Gamepad_Result xbox_move_stick_right(int id, int x, int y);

		GAMEPAD_API Gamepad_Result xbox_release_stick_left(int id);
		GAMEPAD_API Gamepad_Result xbox_release_stick_right(int id);

		GAMEPAD_API Gamepad_Result xbox_press_trigger_left(int id, int val);
        GAMEPAD_API Gamepad_Result xbox_press_trigger_right(int id, int val);

		GAMEPAD_API Gamepad_Result xbox_release_trigger_left(int id);
		GAMEPAD_API Gamepad_Result xbox_release_trigger_right(int id);
    }
}
