#include "pch.h"
#include "Xbox.h"
#include "Gamepad.h"
#include "GamepadSharedAction.h"

#include <string>

gamepadmanager::Xbox::Xbox(PVIGEM_TARGET id, ULONG index) : Gamepad("", id, index)
{
	ZeroMemory(&report, sizeof(report));
}

gamepadmanager::Xbox::~Xbox()
{
	release();
}

void gamepadmanager::Xbox::create()
{
}

void gamepadmanager::Xbox::release()
{
}

XUSB_REPORT gamepadmanager::Xbox::handleInputButton(_XUSB_BUTTON button, BUTTON_STATE state)
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

XUSB_REPORT gamepadmanager::Xbox::handleInputStick(DIRECTION direction, SHORT x, SHORT y)
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

XUSB_REPORT gamepadmanager::Xbox::HandleInputTrigger(DIRECTION direction, BYTE val)
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

void gamepadmanager::Xbox::cleanInput()
{
	ZeroMemory(&report, sizeof(report));
}
