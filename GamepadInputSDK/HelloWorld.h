#pragma once
#include "pch.h"
#include <string>

namespace gamepadsdk
{
	class GAMEPADSDK_API HelloWorld
	{
	public:
		const std::string getHelloMessage() const;
	};

	extern "C" GAMEPADSDK_API const char* say_hello();
}
