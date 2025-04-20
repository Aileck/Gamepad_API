#pragma once
#include <string>

#include "globals.h"
#include "GamepadResult.h"

namespace gamepadmanager {
	class GAMEPAD_API Gamepad {
		public:
			Gamepad(const std::string& name);
			virtual ~Gamepad();

			virtual void create() = 0;
            virtual void release() = 0;
			virtual void cleanInput() = 0;

		private:
			std::string gamepadName;
			std::string gamepadCustomName;
		};
};

