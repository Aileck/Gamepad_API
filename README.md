# GamepadAPI

A FFI-friendly wrapper for ViGEm to enable cross-language virtual gamepad support.

## Overview

GamepadAPI provides a simple C-style interface for creating and controlling virtual Xbox 360 and DualShock 4 controllers through the ViGEm framework. This wrapper makes it easy to integrate virtual gamepad functionality into applications written in any language that supports C FFI (Foreign Function Interface).

## Features

- Easy-to-use API for creating virtual controllers
- Support for Xbox 360 controllers
  - All buttons and inputs (A, B, X, Y, bumpers, triggers, sticks, etc.)
- Support for DualShock 4 controllers
  - All buttons and inputs (Cross, Circle, Square, Triangle, L1/R1, L2/R2, sticks, etc.)
- C-style API for maximum language compatibility
- Simple error handling with result codes

## Prerequisites

- Build tool: Visual Studio 2022
- [ViGEmBus Driver](https://github.com/ViGEm/ViGEmBus/releases) installed

## Installation

1. Install the ViGEmBus driver from the [official releases](https://github.com/ViGEm/ViGEmBus/releases)
2. Include the GamepadAPI library in your project

## Usage

### Initialization

Before using any controller functions, initialize the library:

```c
#include "GamepadAPI.h"

int main() {
    Gamepad_Result result = gamepadapi::initialize();
    if (result.status == 0) {
        // Handle error
        return 1;
    }
    
    // Use the library...
    
    gamepadapi::release();
    return 0;
}
```

### Creating and Using an Xbox 360 Controller

```c
int controllerId;
result = gamepadapi::create_xbox_controller(controllerId);
if (result.status != 0) {
    // Press the A button
    gamepadapi::xbox_input_a(controllerId, true);
    
    // Move the left stick
    gamepadapi::xbox_input_left_stick(controllerId, 16384, 0); // Half-right
    
    // Release the A button
    gamepadapi::xbox_input_a(controllerId, false);
}
```

### Creating and Using a DualShock 4 Controller

```c
int controllerId;
result = gamepadapi::create_dualshock4_controller(controllerId);
if (result.status != 0) {
    // Press the Cross button
    gamepadapi::ds4_input_cross(controllerId, true);
    
    // Move the right stick
    gamepadapi::ds4_input_right_stick(controllerId, 0, -16384); // Half-up
    
    // Press the L2 trigger halfway
    gamepadapi::ds4_input_l2(controllerId, 128);
    
    // Release the Cross button
    gamepadapi::ds4_input_cross(controllerId, false);
}
```

## API Reference

### Core Functions

- `initialize()` - Initialize the GamepadAPI library
- `release()` - Clean up and release resources

### Xbox 360 Controller Functions

- `create_xbox_controller(int& id)` - Create a new Xbox 360 controller
- `xbox_input_up/down/left/right(int id, bool keydown)` - D-pad controls
- `xbox_input_a/b/x/y(int id, bool keydown)` - Face buttons
- `xbox_input_left_stick/right_stick(int id, SHORT x, SHORT y)` - Analog sticks
- `xbox_input_lb/rb(int id, bool keydown)` - Bumper buttons
- `xbox_input_lt/rt(int id, int val)` - Trigger buttons (0-255)
- `xbox_input_left_analog_button/right_analog_button(int id, bool keydown)` - Stick clicks
- `xbox_input_start/back/guide(int id, bool keydown)` - Menu buttons

### DualShock 4 Controller Functions

- `create_dualshock4_controller(int& id)` - Create a new DualShock 4 controller
- `ds4_input_up/down/left/right(int id, bool keydown)` - D-pad controls
- `ds4_input_up_left/up_right/down_left/down_right(int id, bool keydown)` - Diagonal D-pad
- `ds4_input_square/triangle/circle/cross(int id, bool keydown)` - Face buttons
- `ds4_input_left_stick/right_stick(int id, SHORT x, SHORT y)` - Analog sticks
- `ds4_input_l1/r1(int id, bool keydown)` - Bumper buttons
- `ds4_input_l2/r2(int id, int val)` - Trigger buttons (0-255)
- `ds4_input_l3/r3(int id, bool keydown)` - Stick clicks
- `ds4_input_share/options/touchpad/ps(int id, bool keydown)` - Special buttons

## Error Handling

All functions return a `Gamepad_Result` struct to indicate success or failure:

```c
typedef struct {
    int status;         // 0 = error, other = success
    VIGEM_ERROR error;  // Original ViGEm error code
} Gamepad_Result;
```

Check the `status` field to determine if the operation was successful (non-zero) or failed (zero). The `error` field contains the original ViGEm error code for more detailed error information.

## Language Bindings

Check this file for a real ffi-binding example.

## Known Issues

- Number Overflow: Lack of error handling with values for analog sticks causing overflow.
- Error Code Compatibility: VIGEM_ERROR in Gamepad_Result struct is not accessible through FFI.

## Acknowledgments

- [ViGEm](https://github.com/ViGEm) - The virtual gamepad emulation framework that powers this library
