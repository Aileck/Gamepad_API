#include "pch.h"
#include "HelloWorld.h"

using namespace gamepadsdk;

const std::string HelloWorld::getHelloMessage() const {
    return "hello from c++";
}

extern "C" GAMEPADSDK_API const char* say_hello() {
    static HelloWorld instance;
    static std::string message = instance.getHelloMessage();
    return message.c_str();  
}
