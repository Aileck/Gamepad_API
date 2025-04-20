#pragma once
#include "Gamepad.h"

#include "GamepadResult.h"
#include <ViGEm/Client.h>

namespace gamepadmanager {
    class GAMEPAD_API Xbox : public Gamepad {
    public:
        Xbox(PVIGEM_TARGET id, ULONG index);
        ~Xbox();

        void create();
        void release();

        const Gamepad_Result HandleInput(int id, _XUSB_BUTTON button);

      private:
		// VIGEM's internal ID
        PVIGEM_TARGET padID;

        // User index defined by bus
        ULONG gamepadIndex;

        // To save controller state for xbox
        XUSB_REPORT report;
    };
}; // namespace gamepadmanager
