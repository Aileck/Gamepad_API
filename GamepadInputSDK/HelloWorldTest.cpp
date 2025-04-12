#include <iostream>
#include "HelloWorld.h" 
#include "pch.h"
using namespace gamepadsdk; 
int main() {
    gamepadsdk::HelloWorld hello;
    std::string message = hello.getHelloMessage();

    std::cout << "HelloWorld says: " << message << std::endl;

    std::string dllMessage = gamepadsdk::say_hello();
    std::cout << "say_hello function says: " << dllMessage << std::endl;

    return 0;
}
