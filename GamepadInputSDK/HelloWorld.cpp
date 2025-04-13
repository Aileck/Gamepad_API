#include "pch.h"
#include "HelloWorld.h"
#include <Xinput.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace gamepadmanager;

const std::string HelloWorld::getHelloMessage() const {
    return "hello from c++";
}

const int gamepadmanager::HelloWorld::initXboxController()
{
    client = vigem_alloc();

    if (client == nullptr) {
        std::cerr << "Uh, not enough memory to do that?!" << std::endl;
        return -1;
    }

    retval = vigem_connect(client);

    if (!VIGEM_SUCCESS(retval))
    {
        std::cerr << "ViGEm Bus connection failed with error code: 0x" << std::hex << retval << std::endl;
        return -1;
    }

    return 0;
}

const int gamepadmanager::HelloWorld::createXboxController()
{
    pad = vigem_target_x360_alloc();
    const auto pir = vigem_target_add(client, pad);

    if (!VIGEM_SUCCESS(pir))
    {
        std::cerr << "Target plugin failed with error code: 0x" << std::hex << pir << std::endl;
        return -1;
    }

    XINPUT_STATE state;
    XInputGetState(0, &state);
    vigem_target_x360_update(client, pad, *reinterpret_cast<XUSB_REPORT*>(&state.Gamepad));

    ULONG index;
    vigem_target_x360_get_user_index(client, pad, &index);
    std::cout << "Virtual controller assigned to user index: " << index << std::endl;

	return 0;
}

const int gamepadmanager::HelloWorld::xbox_down_dpad_controller()
{
    XUSB_REPORT report;
    ZeroMemory(&report, sizeof(report));

    report.wButtons = XUSB_GAMEPAD_DPAD_DOWN;
    vigem_target_x360_update(client, pad, report);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    report.wButtons = 0;
    vigem_target_x360_update(client, pad, report);


    return 0;
}

const int gamepadmanager::HelloWorld::closeXboxController()
{
    vigem_target_remove(client, pad);
    vigem_target_free(pad);

    return 0;
}

// C interface functions to expose the methods

extern "C" GAMEPADSDK_API const char* say_hello() {
    static HelloWorld instance;
    static std::string message = instance.getHelloMessage();
    return message.c_str();
}

extern "C" GAMEPADSDK_API int init_xbox_controller() {
    static HelloWorld instance;
    return instance.initXboxController();
}

extern "C" GAMEPADSDK_API int create_xbox_controller() {
    static HelloWorld instance;
    return instance.createXboxController();
}

extern "C" GAMEPADSDK_API int close_xbox_controller() {
    static HelloWorld instance;
    return instance.closeXboxController();
}

extern "C" GAMEPADSDK_API int xbox_down_dpad_controller() {
    static HelloWorld instance;
    return instance.xbox_down_dpad_controller();
}