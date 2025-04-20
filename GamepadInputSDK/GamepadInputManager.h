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
    enum class BUTTON_STATE;
    enum class DIRECTION;

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
        Gamepad_Result createGamepad(int *id, GAMEPAD_TYPE type);

        Gamepad_Result cleanUp();

        Gamepad_Result xboxInputButton(int id, _XUSB_BUTTON button, BUTTON_STATE state);
		Gamepad_Result xboxInputStick(int id, DIRECTION direction, SHORT x, SHORT y);
        Gamepad_Result xboxInputTrigger(int id, DIRECTION direction, BYTE val);

    private:
        GamepadInputManager();
        ~GamepadInputManager();
        GamepadInputManager(const GamepadInputManager&) = delete;
        GamepadInputManager& operator=(const GamepadInputManager&) = delete;

        Gamepad_Result createXboxGamepad(int* id);
        inline void incrementSession() { session++; }
        inline void resetSession() { session--; }

        PVIGEM_CLIENT client;
        std::unordered_map<int, std::shared_ptr<Gamepad>> gamepads;

        int session;
    };
}
