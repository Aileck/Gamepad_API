#pragma once
#include "Gamepad.h"

#include "GamepadResult.h"
#include <ViGEm/Client.h>

namespace gamepadmanager {
    enum class BUTTON_STATE;
    enum class DIRECTION;

    class GAMEPAD_API Xbox : public Gamepad {
    public:
        Xbox(PVIGEM_TARGET id, ULONG index);
        ~Xbox();

        void create();
        void release();

        XUSB_REPORT handleInputButton(_XUSB_BUTTON button, BUTTON_STATE state);
        XUSB_REPORT handleInputStick(DIRECTION direction, SHORT x, SHORT y);
        XUSB_REPORT HandleInputTrigger(DIRECTION direction, BYTE val);

      private:
        void cleanInput();

		// VIGEM's internal ID
        PVIGEM_TARGET padID;

        // User index defined by bus
        ULONG gamepadIndex;

        // To save controller state for xbox
        XUSB_REPORT report;
    };
}; // namespace gamepadmanager
