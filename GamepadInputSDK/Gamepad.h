#pragma once
#include <string>

#include "globals.h"
#include "GamepadResult.h"

namespace gamepadapi {
	class GAMEPAD_API Gamepad {
		public:
			Gamepad(const std::string& name, PVIGEM_TARGET id);
			virtual ~Gamepad();

			virtual void create() = 0;
            virtual void release() = 0;

			inline std::string GetGamepadName() const { return gamepadName; }
			inline std::string GetGamepadCustomName() const { return gamepadCustomName; }

			inline void SetGamepadName(const std::string& name) { gamepadName = name; }
			inline void SetGamepadCustomName(const std::string& name) { gamepadCustomName = name; }

			inline PVIGEM_TARGET GetPadID() const { return padID; }

		private:
			virtual void cleanInput() = 0;

			std::string gamepadName;
			std::string gamepadCustomName;

			// VIGEM's internal ID
			PVIGEM_TARGET padID;
		};
};

