#pragma once
#include "Gamepad.h"

#include "GamepadResult.h"
#include <ViGEm/Client.h>
#include <memory>

namespace gamepadapi {
    enum class BUTTON_STATE;
    enum class DIRECTION;

    class GAMEPAD_API Xbox : public Gamepad {
    public:
        Xbox(PVIGEM_TARGET id);
        ~Xbox();

        void create();
        void release();

        PXUSB_REPORT handleInputButton(XUSB_BUTTON button, BUTTON_STATE state);
        PXUSB_REPORT handleInputStick(DIRECTION direction, SHORT x, SHORT y);
        PXUSB_REPORT HandleInputTrigger(DIRECTION direction, BYTE val);

      private:
        void cleanInput();

        // To save controller state for xbox
        std::unique_ptr<XUSB_REPORT> report;
    };
}; // namespace gamepadapi
