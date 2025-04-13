#pragma once
#include "pch.h"
#include <string>
#include <ViGEm/Client.h>


namespace gamepadmanager
{
	class GAMEPADSDK_API HelloWorld
	{
	public:
		const std::string getHelloMessage() const;

		const int initXboxController();
		const int createXboxController();
		const int xbox_down_dpad_controller();
		const int closeXboxController();

	private:
		PVIGEM_CLIENT client;
		VIGEM_ERROR retval;
		PVIGEM_TARGET pad;
	};

	extern "C" {
		GAMEPADSDK_API const char* say_hello();
		GAMEPADSDK_API int init_xbox_controller();
		GAMEPADSDK_API int create_xbox_controller();
		GAMEPADSDK_API int xbox_down_dpad_controller();
		GAMEPADSDK_API int close_xbox_controller();
	}
}
