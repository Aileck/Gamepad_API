#include "main.h"
#include "GamepadAPI.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <unordered_map>
#include <windows.h>

// Display keyboard mapping help
void showControlHelp() {
    std::cout << "=== Controller Keyboard Mapping ===" << std::endl;
    std::cout << "Initialization:" << std::endl;
    std::cout << "  1 - Initialize controller" << std::endl;
    std::cout << "  2 - Create Xbox controller" << std::endl;
    std::cout << "  3 - Create DualShock 4 controller" << std::endl;
    std::cout << "  4 - Close controller" << std::endl;
    std::cout << "Xbox Button Mapping:" << std::endl;
    std::cout << "  Q - D-pad Up" << std::endl;
    std::cout << "  W - D-pad Down" << std::endl;
    std::cout << "  E - Xbox A button" << std::endl;
    std::cout << "  R - Xbox Y button" << std::endl;
    std::cout << "  T - Guide button" << std::endl;
    std::cout << "  Y - Left Shoulder (LB)" << std::endl;
    std::cout << "  U - Right Shoulder (RB)" << std::endl;
    std::cout << "  I - Left Trigger (half)" << std::endl;
    std::cout << "  O - Analog stick (Up-Left)" << std::endl;
    std::cout << "DualShock 4 Button Mapping:" << std::endl;
    std::cout << "  A - D-pad Up-Left" << std::endl;
    std::cout << "  S - D-pad Up-Right" << std::endl;
    std::cout << "  D - D-pad Down-Left" << std::endl;
    std::cout << "  F - D-pad Down-Right" << std::endl;
    std::cout << "  G - Cross button (X)" << std::endl;
    std::cout << "  H - Share button" << std::endl;
    std::cout << "  J - L1 button" << std::endl;
    std::cout << "  K - L2 trigger (half)" << std::endl;
    std::cout << "  L - L3 button (Left stick press)" << std::endl;
    std::cout << "  Z - Left analog stick (Up-Left)" << std::endl;
    std::cout << "Other Controls:" << std::endl;
    std::cout << "  P - Display this help menu" << std::endl;
    std::cout << "  Esc - Exit program" << std::endl;
    std::cout << "===============================" << std::endl;
}

std::unordered_map<char, bool> keyStates;

bool toggleKeyState(char key) {
    keyStates[key] = !keyStates[key];
    return keyStates[key];
}

int main() {
    int xboxId = -1;
    int ds4Id = -1;

    const int STICK_MAX = 32767;
    const int TRIGGER_HALF = 128; // Half of the trigger max value

    showControlHelp();

    while (true) {
        if (_kbhit()) {
            char ch = _getch();

            if (ch == 27) { // Esc key
                std::cout << "Exiting program..." << std::endl;
                gamepadapi::release();
                break;
            }

            if (ch == 'p' || ch == 'P') {
                showControlHelp();
                continue;
            }

            bool keydown = toggleKeyState(ch);

            switch (ch) {
            case '1':
                std::cout << "Initializing controller..." << std::endl;
                gamepadapi::initialize();
                break;
            case '2':
                std::cout << "Creating Xbox controller..." << std::endl;
                gamepadapi::create_xbox_controller(xboxId);
                std::cout << "Xbox controller created with ID: " << xboxId << std::endl;
                break;
            case '3':
                std::cout << "Creating DualShock 4 controller..." << std::endl;
                gamepadapi::create_dualshock4_controller(ds4Id);
                std::cout << "DualShock 4 controller created with ID: " << ds4Id << std::endl;
                break;
            case '4':
                std::cout << "Closing controllers..." << std::endl;
                gamepadapi::release();
                break;

                // Xbox controller mappings
            case 'q': // D-pad Up
                std::cout << (keydown ? "Pressed: Xbox D-pad Up" : "Released: Xbox D-pad Up") << std::endl;
                gamepadapi::xbox_input_up(xboxId, keydown);
                break;
            case 'w': // D-pad Down
                std::cout << (keydown ? "Pressed: Xbox D-pad Down" : "Released: Xbox D-pad Down") << std::endl;
                gamepadapi::xbox_input_down(xboxId, keydown);
                break;
            case 'e': // Button A
                std::cout << (keydown ? "Pressed: Xbox A button" : "Released: Xbox A button") << std::endl;
                gamepadapi::xbox_input_a(xboxId, keydown);
                break;
            case 'r': // Button Y
                std::cout << (keydown ? "Pressed: Xbox Y button" : "Released: Xbox Y button") << std::endl;
                gamepadapi::xbox_input_y(xboxId, keydown);
                break;
            case 't': // Guide button
                std::cout << (keydown ? "Pressed: Xbox Guide button" : "Released: Xbox Guide button") << std::endl;
                gamepadapi::xbox_input_guide(xboxId, keydown);
                break;
            case 'y': // Left Shoulder (LB)
                std::cout << (keydown ? "Pressed: Xbox Left Shoulder" : "Released: Xbox Left Shoulder") << std::endl;
                gamepadapi::xbox_input_lb(xboxId, keydown);
                break;
            case 'u': // Right Shoulder (RB)
                std::cout << (keydown ? "Pressed: Xbox Right Shoulder" : "Released: Xbox Right Shoulder") << std::endl;
                gamepadapi::xbox_input_rb(xboxId, keydown);
                break;
            case 'i': // Left Trigger (half)
                std::cout << "Xbox Left Trigger set to half value: " << TRIGGER_HALF << std::endl;
                gamepadapi::xbox_input_lt(xboxId, TRIGGER_HALF);
                break;
            case 'o': // Analog stick up-left
                std::cout << "Xbox Analog stick moved to Up-Left" << std::endl;
                gamepadapi::xbox_input_left_stick(xboxId, -STICK_MAX, -STICK_MAX);
                break;

                // DualShock 4 controller mappings
            case 'a': // D-pad Up-Left
                std::cout << (keydown ? "Pressed: DS4 D-pad Up-Left" : "Released: DS4 D-pad Up-Left") << std::endl;
                gamepadapi::ds4_input_up_left(ds4Id, keydown);
                break;
            case 's': // D-pad Up-Right
                std::cout << (keydown ? "Pressed: DS4 D-pad Up-Right" : "Released: DS4 D-pad Up-Right") << std::endl;
                gamepadapi::ds4_input_up_right(ds4Id, keydown);
                break;
            case 'd': // D-pad Down-Left
                std::cout << (keydown ? "Pressed: DS4 D-pad Down-Left" : "Released: DS4 D-pad Down-Left") << std::endl;
                gamepadapi::ds4_input_down_left(ds4Id, keydown);
                break;
            case 'f': // D-pad Down-Right
                std::cout << (keydown ? "Pressed: DS4 D-pad Down-Right" : "Released: DS4 D-pad Down-Right") << std::endl;
                gamepadapi::ds4_input_down_right(ds4Id, keydown);
                break;
            case 'g': // Cross button (X)
                std::cout << (keydown ? "Pressed: DS4 Cross button" : "Released: DS4 Cross button") << std::endl;
                gamepadapi::ds4_input_cross(ds4Id, keydown);
                break;
            case 'h': // Share button
                std::cout << (keydown ? "Pressed: DS4 Share button" : "Released: DS4 Share button") << std::endl;
                gamepadapi::ds4_input_share(ds4Id, keydown);
                break;
            case 'j': // L1 button
                std::cout << (keydown ? "Pressed: DS4 L1 button" : "Released: DS4 L1 button") << std::endl;
                gamepadapi::ds4_input_l1(ds4Id, keydown);
                break;
            case 'k': // L2 trigger (half)
                std::cout << "DS4 L2 Trigger set to half value: " << TRIGGER_HALF << std::endl;
                gamepadapi::ds4_input_l2(ds4Id, TRIGGER_HALF);
                break;
            case 'l': // L3 button
                std::cout << (keydown ? "Pressed: DS4 L3 button" : "Released: DS4 L3 button") << std::endl;
                gamepadapi::ds4_input_l3(ds4Id, keydown);
                break;
            case 'z': // Left analog stick up-left
                std::cout << "DS4 Left analog stick moved to Up-Left" << std::endl;
                gamepadapi::ds4_input_left_stick(ds4Id, -STICK_MAX, -STICK_MAX);
                break;
            default:
                break;
            }
        }
    }

    return 0;
}