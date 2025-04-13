#include "main.h"
#include "HelloWorld.h"
#include <iostream>
#include <conio.h>  

int main() {
    using namespace gamepadmanager;

    HelloWorld hw;

    std::cout << "Class says: " << hw.getHelloMessage() << std::endl;
    std::cout << "Function says: " << say_hello() << std::endl;

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
                hw.initXboxController();
                break;

            case '2':
                std::cout << "Creating Xbox Controller..." << std::endl;
                hw.createXboxController();
                break;

            case '3':
                std::cout << "Closing Xbox Controller..." << std::endl;
                hw.closeXboxController();
                break;

            case 'D':
                while (true) {
                    std::cout << "D pad left" << std::endl;
                    hw.xbox_down_dpad_controller();


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
