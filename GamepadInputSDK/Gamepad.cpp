#include "pch.h"
#include "Gamepad.h"

namespace gamepadmanager {
    Gamepad::Gamepad(const std::string& name, PVIGEM_TARGET id, ULONG index) {
      if (name == "") {
        gamepadName = "Unknown Gamepad";
      }
      else {
        gamepadName = name;
      }

      padID = id;
      gamepadIndex = index;
    }

	Gamepad::~Gamepad() = default;

} // namespace gamepadmanager
