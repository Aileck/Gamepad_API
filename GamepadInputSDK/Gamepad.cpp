#include "pch.h"
#include "Gamepad.h"

namespace gamepadmanager {
    Gamepad::Gamepad(const std::string& name) {
      if (name == "") {
        gamepadName = "Unknown Gamepad";
      }
      else {
        gamepadName = name;
      }
    }

	Gamepad::~Gamepad() = default;

} // namespace gamepadmanager
