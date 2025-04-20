#include "pch.h"
#include "Xbox.h"

#include <string>

gamepadmanager::Xbox::Xbox(PVIGEM_TARGET id, ULONG index) : Gamepad("")
{
	padID = id;
	gamepadIndex = index;

	ZeroMemory(&report, sizeof(report));
}

gamepadmanager::Xbox::~Xbox()
{
}

void gamepadmanager::Xbox::create() {
}

void gamepadmanager::Xbox::release()
{
}
