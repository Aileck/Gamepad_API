#include "main.h"
#include "../GamepadInputSDK/HelloWorld.h"
#include <iostream>

int main() {
    using namespace gamepadsdk;

    HelloWorld hw;
    std::cout << "Class says: " << hw.getHelloMessage() << std::endl;

    std::cout << "Function says: " << say_hello() << std::endl;

    return 0;
}