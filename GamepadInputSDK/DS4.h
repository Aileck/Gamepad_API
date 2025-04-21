#pragma once
#include "Gamepad.h"
#include <memory>

#include "GamepadResult.h"
#include <ViGEm/Client.h>

namespace gamepadapi {
    enum class BUTTON_STATE;
    enum class DIRECTION;

    class DS4 : public Gamepad
    {
	public:
		DS4(PVIGEM_TARGET id);
		~DS4();

		void create();
		void release();

		PDS4_REPORT handleInputButton(DS4_BUTTONS button, BUTTON_STATE state);
		PDS4_REPORT handleInputDpad(DS4_DPAD_DIRECTIONS button, BUTTON_STATE state);
		PDS4_REPORT handleInputSpecial(DS4_SPECIAL_BUTTONS direction, BUTTON_STATE state);

		PDS4_REPORT handleInputStick(DIRECTION direction, BYTE x, BYTE y);
		PDS4_REPORT HandleInputTrigger(DIRECTION direction, BYTE val);

	private:
		void cleanInput();
		// To save controller state for xbox
		std::unique_ptr <DS4_REPORT> report;
    };
};

