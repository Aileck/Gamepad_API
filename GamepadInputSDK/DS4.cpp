#include "pch.h"
#include "DS4.h"
#include "GamepadSharedAction.h"

gamepadapi::DS4::DS4(PVIGEM_TARGET id) : Gamepad("", id)
{
    report = std::make_unique<DS4_REPORT>();
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
	DS4_REPORT_INIT(report.get());
}

PDS4_REPORT gamepadapi::DS4::handleInputButton(DS4_BUTTONS button, BUTTON_STATE state)
{
    if (state == BUTTON_STATE::PRESSED)
    {
        report->wButtons |= button;
    }
    else if (state == BUTTON_STATE::RELEASED)
    {
        report->wButtons &= ~button;
    }

    return report.get();
}

PDS4_REPORT gamepadapi::DS4::handleInputDpad(DS4_DPAD_DIRECTIONS button, BUTTON_STATE state)
{
	// Clear the dpad state first
    DS4_SET_DPAD(report.get(), DS4_BUTTON_DPAD_NONE);

    if(state == BUTTON_STATE::PRESSED)
	{
        DS4_SET_DPAD(report.get(), button);
    }

	return report.get();
}

PDS4_REPORT gamepadapi::DS4::handleInputSpecial(DS4_SPECIAL_BUTTONS button, BUTTON_STATE state)
{
    if (state == BUTTON_STATE::PRESSED)
    {
        report->bSpecial |= button;
    }
    else if (state == BUTTON_STATE::RELEASED)
    {
        report->bSpecial &= ~button;
    }

    return report.get();
}

PDS4_REPORT gamepadapi::DS4::handleInputStick(DIRECTION direction, BYTE x, BYTE y)
{
    if (direction == DIRECTION::LEFT)
    {
        report->bThumbLX = x;
        report->bThumbLY = y;
    }
    else
    {
        report->bThumbRX = x;
        report->bThumbRY = y;
    }

    return report.get();
}

PDS4_REPORT gamepadapi::DS4::HandleInputTrigger(DIRECTION direction, BYTE val)
{
    if (direction == DIRECTION::LEFT)
    {
        report->bTriggerL = val;
    }
    else
    {
        report->bTriggerR = val;
    }

    return report.get();
}
