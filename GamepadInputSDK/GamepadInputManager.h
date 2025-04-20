#pragma once
#include "globals.h"
#include "GamepadResult.h"
#include <ViGEm/Client.h>
#include <vector>
#include <unordered_map>
#include <memory>


namespace gamepadmanager
{
    class Gamepad;

    enum class GAMEPAD_TYPE {
      GAMEPAD_XBOX,
      GAMEPAD_PS4,
    };

    class GAMEPAD_API GamepadInputManager
    {
    public:
        // Singleton manager
        static GamepadInputManager& getInstance();

        Gamepad_Result initializeManager();
        Gamepad_Result createXboxController(int *id);
        Gamepad_Result createGamepad(int *id, GAMEPAD_TYPE type);
		Gamepad_Result createXboxGamepad(int* id);

        Gamepad_Result cleanUp();
        Gamepad_Result xboxPressButton(int id, _XUSB_BUTTON button);
        Gamepad_Result xboxReleaseButton(int id);

		Gamepad_Result xboxMoveThumb(int id, bool leftStick, SHORT x, SHORT y);
        Gamepad_Result xboxReleaseThumb(int id, bool leftStick);

        Gamepad_Result xboxPressTrigger(int id, bool leftTrigger, BYTE val);
		Gamepad_Result xboxReleaseTrigger(int id, bool leftTrigger);

    private:
        GamepadInputManager();
        ~GamepadInputManager();
        GamepadInputManager(const GamepadInputManager&) = delete;
        GamepadInputManager& operator=(const GamepadInputManager&) = delete;

        inline void incrementSession() { session++; }
        inline void resetSession() { session--; }

        PVIGEM_CLIENT client;
        VIGEM_ERROR retval;

        std::vector<PVIGEM_TARGET> pads;
        std::unordered_map<int, std::shared_ptr<Gamepad>> gamepads;

        int session;
    };
}
