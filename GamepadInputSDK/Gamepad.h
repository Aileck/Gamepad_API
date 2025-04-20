#pragma once
#include <string>

#include "globals.h"
#include "GamepadResult.h"

namespace gamepadmanager {
	class GAMEPAD_API Gamepad {
		public:
			Gamepad(const std::string& name, PVIGEM_TARGET id, ULONG index);
			virtual ~Gamepad();

			virtual void create() = 0;
            virtual void release() = 0;
			virtual void cleanInput() = 0;

			inline std::string GetGamepadName() const { return gamepadName; }
			inline std::string GetGamepadCustomName() const { return gamepadCustomName; }

			inline void SetGamepadName(const std::string& name) { gamepadName = name; }
			inline void SetGamepadCustomName(const std::string& name) { gamepadCustomName = name; }

			inline PVIGEM_TARGET GetPadID() const { return padID; }
			inline ULONG GetGamepadIndex() const { return gamepadIndex; }

		private:


			std::string gamepadName;
			std::string gamepadCustomName;

			// VIGEM's internal ID
			PVIGEM_TARGET padID;

			// User index defined by bus
			ULONG gamepadIndex;
		};
};

