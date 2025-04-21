#pragma once
#include "globals.h"
#include "GamepadResult.h"
#include <ViGEm/Client.h>
#include <vector>
#include <unordered_map>
#include <memory>


namespace gamepadapi
{
    class Gamepad;
    enum class BUTTON_STATE;
    enum class DIRECTION;

    enum class GAMEPAD_TYPE {
      GAMEPAD_XBOX360,
      GAMEPAD_DUALSHOCK4,
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

		Gamepad_Result ds4InputButton(int id, DS4_BUTTONS button, BUTTON_STATE state);
		Gamepad_Result ds4InputDpad(int id, _DS4_DPAD_DIRECTIONS button, BUTTON_STATE state);
		Gamepad_Result ds4InputSpecial(int id, DS4_SPECIAL_BUTTONS button, BUTTON_STATE state);
		Gamepad_Result ds4InputStick(int id, DIRECTION direction, SHORT x, SHORT y);
		Gamepad_Result ds4InputTrigger(int id, DIRECTION direction, BYTE val);

    private:
        GamepadInputManager();
        ~GamepadInputManager();

		// Prevent copying and assignment since this is a singleton
        GamepadInputManager(const GamepadInputManager&) = delete;
        GamepadInputManager& operator=(const GamepadInputManager&) = delete;

        Gamepad_Result createXbox360Gamepad(int* id);
        Gamepad_Result createDualShock4Gamepad(int* id);

        inline void incrementSession() { session++; }
        inline void resetSession() { session--; }

        PVIGEM_CLIENT client;
        std::unordered_map<int, std::shared_ptr<Gamepad>> gamepads;

        int session;
    };
}
