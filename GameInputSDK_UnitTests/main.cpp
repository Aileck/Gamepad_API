#include "main.h"
#include "GamepadInputManager.h"

#include <iostream>
#include <conio.h>  

int main() {
	int gamepadid =-1;
    std::cout << "Press 1 to init Xbox controller." << std::endl;
    std::cout << "Press 2 to create Xbox controller." << std::endl;
    std::cout << "Press 3 to close Xbox controller." << std::endl;
    std::cout << "Press D to simulate D pad down." << std::endl;

    while (true) {
        if (_kbhit()) { 
            char ch = _getch();  

            switch (ch) {
            case '1':
                std::cout << "Initializing Xbox Controller..." << std::endl;
                gamepadmanager::initialize();

                break;

            case '2':
                std::cout << "Creating Xbox Controller..." << std::endl;
                gamepadmanager::create_xbox_controller(gamepadid);
				std::cout << "Xbox Controller created with ID: " << gamepadid << std::endl;
                break;

            case '3':
                std::cout << "Closing Xbox Controller..." << std::endl;
                gamepadmanager::release();
                break;

            case 'D':
                while (true) {
                    std::cout << "D pad left" << std::endl;
                gamepadmanager::xbox_down_dpad_controller(gamepadid);


					std::cout << "Press any key to stop D pad left simulation..." << std::endl;
					if (_kbhit()) {
						char stop = _getch();
						if (stop == 'q') {
							std::cout << "Stopping D pad down simulation..." << std::endl;
							break;
						}
					}
                }

                break;

            default:
                std::cout << "Invalid input! Press 1, 2, or 3." << std::endl;
                break;
            }
        }
    }

    return 0;
}
