#include "main.h"
#include "GamepadInputManager.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <unordered_map>

// Display keyboard mapping help
void showControlHelp() {
    std::cout << "=== Xbox Controller Keyboard Mapping ===" << std::endl;
    std::cout << "Initialization:" << std::endl;
    std::cout << "  1 - Initialize Xbox controller" << std::endl;
    std::cout << "  2 - Create Xbox controller" << std::endl;
    std::cout << "  3 - Close Xbox controller" << std::endl;
    std::cout << "Button Mapping:" << std::endl;
    std::cout << "  Q - Xbox A button" << std::endl;
    std::cout << "  W - Xbox B button" << std::endl;
    std::cout << "  E - Xbox X button" << std::endl;
    std::cout << "  R - Xbox Y button" << std::endl;
    std::cout << "  T - Start button" << std::endl;
    std::cout << "  Y - Back button" << std::endl;
    std::cout << "  F - Left Shoulder button" << std::endl;
    std::cout << "  G - Right Shoulder button" << std::endl;
    std::cout << "  V - Left Thumb button" << std::endl;
    std::cout << "  B - Right Thumb button" << std::endl;
    std::cout << "D-pad Mapping:" << std::endl;
    std::cout << "  I - D-pad Up" << std::endl;
    std::cout << "  K - D-pad Down" << std::endl;
    std::cout << "  J - D-pad Left" << std::endl;
    std::cout << "  L - D-pad Right" << std::endl;
    std::cout << "Analog Controls:" << std::endl;
    std::cout << "  W, A, S, D - Left Stick (Up, Left, Down, Right)" << std::endl;
    std::cout << "  8, 4, 5, 6 - Right Stick (Up, Left, Down, Right)" << std::endl;
    std::cout << "  Z - Left Trigger" << std::endl;
    std::cout << "  X - Right Trigger" << std::endl;
    std::cout << "Other Controls:" << std::endl;
    std::cout << "  Enter - Clear all button states" << std::endl;
    std::cout << "  H - Display this help menu" << std::endl;
    std::cout << "  Esc - Exit program" << std::endl;
    std::cout << "===============================" << std::endl;
}

int main() {
    int gamepadid = -1;
    
    // Define standard values for sticks and triggers
    const int STICK_MAX = 32767;  // Maximum value for SHORT
    const int TRIGGER_MAX = 255;  // Maximum value for BYTE
    
    showControlHelp();
    
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            
            // Handle special keys (Esc)
            if (ch == 27) { // Esc key
                std::cout << "Exiting program..." << std::endl;
                gamepadmanager::release();
                break;
            }
            
            switch (ch) {
                // Initialization functions
                case '1':
                    std::cout << "Initializing Xbox controller..." << std::endl;
                    gamepadmanager::initialize();
                    break;
                case '2':
                    std::cout << "Creating Xbox controller..." << std::endl;
                    gamepadmanager::create_xbox_controller(gamepadid);
                    std::cout << "Xbox controller created with ID: " << gamepadid << std::endl;
                    break;
                case '3':
                    std::cout << "Closing Xbox controller..." << std::endl;
                    gamepadmanager::release();
                    break;
                    
                // Button mapping - using a different layout to avoid conflicts
                case 'q':
                case 'Q':
                    std::cout << "Pressed: Xbox A button" << std::endl;
                    gamepadmanager::xbox_press_a(gamepadid);
                    break;
  
                case 'e':
                case 'E':
                    std::cout << "Pressed: Xbox X button" << std::endl;
                    gamepadmanager::xbox_press_x(gamepadid);
                    break;
                case 'r':
                case 'R':
                    std::cout << "Pressed: Xbox Y button" << std::endl;
                    gamepadmanager::xbox_press_y(gamepadid);
                    break;
                case 't':
                case 'T':
                    std::cout << "Pressed: Start button" << std::endl;
                    gamepadmanager::xbox_press_start(gamepadid);
                    break;
                case 'y':
                case 'Y':
                    std::cout << "Pressed: Back button" << std::endl;
                    gamepadmanager::xbox_press_back(gamepadid);
                    break;
                
                // D-pad mapping (using IJKL)
                case 'i':
                case 'I':
                    std::cout << "Pressed: D-pad Up" << std::endl;
                    gamepadmanager::xbox_press_dpad_up(gamepadid);
                    break;
                case 'k':
                case 'K':
                    std::cout << "Pressed: D-pad Down" << std::endl;
                    gamepadmanager::xbox_press_dpad_down(gamepadid);
                    break;
                case 'j':
                case 'J':
                    std::cout << "Pressed: D-pad Left" << std::endl;
                    gamepadmanager::xbox_press_dpad_left(gamepadid);
                    break;
                case 'l':
                case 'L':
                    std::cout << "Pressed: D-pad Right" << std::endl;
                    gamepadmanager::xbox_press_dpad_right(gamepadid);
                    break;
                
                // Shoulder buttons
                case 'f':
                case 'F':
                    std::cout << "Pressed: Left Shoulder" << std::endl;
                    gamepadmanager::xbox_press_left_shoulder(gamepadid);
                    break;
                case 'g':
                case 'G':
                    std::cout << "Pressed: Right Shoulder" << std::endl;
                    gamepadmanager::xbox_press_right_shoulder(gamepadid);
                    break;
                
                // Thumb stick buttons
                case 'v':
                case 'V':
                    std::cout << "Pressed: Left Thumb" << std::endl;
                    gamepadmanager::xbox_press_left_thumb(gamepadid);
                    break;
                case 'b':
                case 'B':
                    std::cout << "Pressed: Right Thumb" << std::endl;
                    gamepadmanager::xbox_press_right_thumb(gamepadid);
                    break;
                
                // Left stick control (WASD)
                case 'w':
                case 'W':
                    std::cout << "Left Stick: Up" << std::endl;
                    gamepadmanager::xbox_move_stick_left(gamepadid, 0, STICK_MAX);
                    break;
                case 'a':
                case 'A':
                    std::cout << "Left Stick: Left" << std::endl;
                    gamepadmanager::xbox_move_stick_left(gamepadid, -STICK_MAX, 0);
                    break;
                case 's':
                case 'S':
                    std::cout << "Left Stick: Down" << std::endl;
                    gamepadmanager::xbox_move_stick_left(gamepadid, 0, -STICK_MAX);
                    break;
                case 'd':
                case 'D':
                    std::cout << "Left Stick: Right" << std::endl;
                    gamepadmanager::xbox_move_stick_left(gamepadid, STICK_MAX, 0);
                    break;
                
                // Right stick control (numpad 8456)
                case '8':
                    std::cout << "Right Stick: Up" << std::endl;
                    gamepadmanager::xbox_move_stick_right(gamepadid, 0, STICK_MAX);
                    break;
                case '4':
                    std::cout << "Right Stick: Left" << std::endl;
                    gamepadmanager::xbox_move_stick_right(gamepadid, -STICK_MAX, 0);
                    break;
                case '5':
                    std::cout << "Right Stick: Down" << std::endl;
                    gamepadmanager::xbox_move_stick_right(gamepadid, 0, -STICK_MAX);
                    break;
                case '6':
                    std::cout << "Right Stick: Right" << std::endl;
                    gamepadmanager::xbox_move_stick_right(gamepadid, STICK_MAX, 0);
                    break;
                
                // Trigger controls
                case 'z':
                case 'Z':
                    std::cout << "Pressed: Left Trigger" << std::endl;
                    gamepadmanager::xbox_press_trigger_left(gamepadid, TRIGGER_MAX);
                    break;
                case 'x':
                case 'X':
                    std::cout << "Pressed: Right Trigger" << std::endl;
                    gamepadmanager::xbox_press_trigger_right(gamepadid, TRIGGER_MAX);
                    break;
                
                // Clear state (Enter key)
                case 13: // Enter key
                    std::cout << "Clearing all button states..." << std::endl;
                    gamepadmanager::xbox_release_button(gamepadid);
                    gamepadmanager::xbox_move_stick_left(gamepadid, 0, 0);
                    gamepadmanager::xbox_move_stick_right(gamepadid, 0, 0);
                    gamepadmanager::xbox_press_trigger_left(gamepadid, 0);
                    gamepadmanager::xbox_press_trigger_right(gamepadid, 0);
                    break;
                
                // Display help
                case 'h':
                case 'H':
                    showControlHelp();
                    break;
                
                default:
                    // Ignore other keys
                    break;
            }
        }
    }
    
    return 0;
}