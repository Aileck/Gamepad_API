#include "pch.h"
#include "DS4.h"
#include "GamepadSharedAction.h"

gamepadapi::DS4::DS4(PVIGEM_TARGET id) : Gamepad("", id)
{
    cleanInput();
}

gamepadapi::DS4::~DS4()
{
	release();
}

void gamepadapi::DS4::create()
{
}

void gamepadapi::DS4::release()
{
}

void gamepadapi::DS4::cleanInput()
{
	DS4_REPORT_INIT(&report);
}

DS4_REPORT gamepadapi::DS4::handleInputButton(DS4_BUTTONS button, BUTTON_STATE state)
{
    if (state == BUTTON_STATE::PRESSED)
    {
        report.wButtons |= button;
    }
    else if (state == BUTTON_STATE::RELEASED)
    {
        report.wButtons &= ~button;
    }

    return report;
}

DS4_REPORT gamepadapi::DS4::handleInputDpad(_DS4_DPAD_DIRECTIONS button, BUTTON_STATE state)
{
    DS4_SET_DPAD(&report, DS4_BUTTON_DPAD_NONE);
    DS4_SET_DPAD(&report, button);

	return report;
}

DS4_REPORT gamepadapi::DS4::handleInputSpecial(DS4_SPECIAL_BUTTONS button, BUTTON_STATE state)
{
    if (state == BUTTON_STATE::PRESSED)
    {
        report.bSpecial |= button;
    }
    else if (state == BUTTON_STATE::RELEASED)
    {
        report.bSpecial &= ~button;
    }

    return report;
}

DS4_REPORT gamepadapi::DS4::handleInputStick(DIRECTION direction, SHORT x, SHORT y)
{
    if (direction == DIRECTION::LEFT)
    {
        report.bThumbLX = x;
        report.bThumbLY = y;
    }
    else
    {
        report.bThumbRX = x;
        report.bThumbRY = y;
    }

    return report;
}

DS4_REPORT gamepadapi::DS4::HandleInputTrigger(DIRECTION direction, BYTE val)
{
    if (direction == DIRECTION::LEFT)
    {
        report.bTriggerL = val;
    }
    else
    {
        report.bTriggerR = val;
    }

    return report;
}
