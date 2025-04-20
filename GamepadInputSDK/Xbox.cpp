#include "pch.h"
#include "Xbox.h"
#include "Gamepad.h"
#include "GamepadSharedAction.h"

#include <string>

gamepadapi::Xbox::Xbox(PVIGEM_TARGET id, ULONG index) : Gamepad("", id, index)
{
	ZeroMemory(&report, sizeof(report));
}

gamepadapi::Xbox::~Xbox()
{
	release();
}

void gamepadapi::Xbox::create()
{
}

void gamepadapi::Xbox::release()
{
}

XUSB_REPORT gamepadapi::Xbox::handleInputButton(_XUSB_BUTTON button, BUTTON_STATE state)
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

XUSB_REPORT gamepadapi::Xbox::handleInputStick(DIRECTION direction, SHORT x, SHORT y)
{
	if (direction == DIRECTION::LEFT)
	{
		report.sThumbLX = x;
		report.sThumbLY = y;
	}
	else 
	{
		report.sThumbRX = x;
		report.sThumbRY = y;
	}

	return report;
}

XUSB_REPORT gamepadapi::Xbox::HandleInputTrigger(DIRECTION direction, BYTE val)
{
	if (direction == DIRECTION::LEFT)
	{
		report.bLeftTrigger = val;
	}
	else
	{
		report.bRightTrigger = val;
	}

	return report;
}

void gamepadapi::Xbox::cleanInput()
{
	ZeroMemory(&report, sizeof(report));
}
