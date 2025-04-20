#include "main.h"
#include "GamepadAPI.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <unordered_map>
#include <windows.h>

// Display keyboard mapping help
void showControlHelp() {
    std::cout << "=== Xbox Controller Keyboard Mapping ===" << std::endl;
    std::cout << "Initialization:" << std::endl;
    std::cout << "  1 - Initialize Xbox controller" << std::endl;
    std::cout << "  2 - Create Xbox controller" << std::endl;
    std::cout << "  3 - Close Xbox controller" << std::endl;
    std::cout << "Button Mapping:" << std::endl;
    std::cout << "  Q - D-pad Up" << std::endl;
    std::cout << "  W - D-pad Down" << std::endl;
    std::cout << "  E - Xbox A button" << std::endl;
    std::cout << "  R - Xbox Y button" << std::endl;
    std::cout << "  T - Guide button" << std::endl;
    std::cout << "  Y - Left Shoulder (LB)" << std::endl;
    std::cout << "  U - Right Shoulder (RB)" << std::endl;
    std::cout << "  I - Left Trigger (half)" << std::endl;
    std::cout << "  O - Analog stick (Up-Left)" << std::endl;
    std::cout << "Other Controls:" << std::endl;
    std::cout << "  H - Display this help menu" << std::endl;
    std::cout << "  Esc - Exit program" << std::endl;
    std::cout << "===============================" << std::endl;
}

std::unordered_map<char, bool> keyStates;

bool toggleKeyState(char key) {
    keyStates[key] = !keyStates[key];
    return keyStates[key];
}

int main() {
    int gamepadid = -1;

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

            bool keydown = toggleKeyState(ch);

            switch (ch) {
            case '1':
                std::cout << "Initializing Xbox controller..." << std::endl;
                gamepadapi::initialize();
                break;
            case '2':
                std::cout << "Creating Xbox controller..." << std::endl;
                gamepadapi::create_xbox_controller(gamepadid);
                std::cout << "Xbox controller created with ID: " << gamepadid << std::endl;
                break;
            case '3':
                std::cout << "Closing Xbox controller..." << std::endl;
                gamepadapi::release();
                break;
            case 'q': // D-pad Up
                std::cout << (keydown ? "Pressed: D-pad Up" : "Released: D-pad Up") << std::endl;
                gamepadapi::xbox_input_up(gamepadid, keydown);
                break;
            case 'w': // D-pad Down
                std::cout << (keydown ? "Pressed: D-pad Down" : "Released: D-pad Down") << std::endl;
                gamepadapi::xbox_input_down(gamepadid, keydown);
                break;
            case 'e': // Button A
                std::cout << (keydown ? "Pressed: Xbox A button" : "Released: Xbox A button") << std::endl;
                gamepadapi::xbox_input_a(gamepadid, keydown);
                break;
            case 'r': // Button Y
                std::cout << (keydown ? "Pressed: Xbox Y button" : "Released: Xbox Y button") << std::endl;
                gamepadapi::xbox_input_y(gamepadid, keydown);
                break;
            case 't': // Guide button
                std::cout << (keydown ? "Pressed: Guide button" : "Released: Guide button") << std::endl;
                gamepadapi::xbox_input_guide(gamepadid, keydown);
                break;
            case 'y': // Left Shoulder (LB)
                std::cout << (keydown ? "Pressed: Left Shoulder" : "Released: Left Shoulder") << std::endl;
                gamepadapi::xbox_input_lb(gamepadid, keydown);
                break;
            case 'u': // Right Shoulder (RB)
                std::cout << (keydown ? "Pressed: Right Shoulder" : "Released: Right Shoulder") << std::endl;
                gamepadapi::xbox_input_rb(gamepadid, keydown);
                break;
            case 'i': // Left Trigger (half)
                std::cout << "Left Trigger set to half value: " << TRIGGER_HALF << std::endl;
                gamepadapi::xbox_input_lt(gamepadid, TRIGGER_HALF);
                break;
            case 'o': // Analog stick up-left
                std::cout << "Analog stick moved to Up-Left" << std::endl;
                gamepadapi::xbox_input_left_stick(gamepadid, -STICK_MAX, -STICK_MAX);
                break;
            default:
                break;
            }
        }
    }

    return 0;
}