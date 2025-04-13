#pragma once
#include "pch.h"
#include "GamepadResult.h"
#include <ViGEm/Client.h>
#include <vector>

namespace gamepadmanager
{
    constexpr int MAX_GAMEPADS = 8;

    class GAMEPAD_API GamepadInputManager
    {
    public:
        // Singleton manager
        static GamepadInputManager& getInstance();

        const Gamepad_Result initializeManager();
        const Gamepad_Result createXboxController(int* id);
        const Gamepad_Result releaseManager();
		const Gamepad_Result xboxDownDPad(int id);

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

		GAMEPAD_API Gamepad_Result xbox_down_dpad_controller(int id);
    }
}
