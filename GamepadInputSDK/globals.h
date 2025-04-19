#pragma once

namespace gamepadmanager {
    constexpr int MAX_GAMEPADS = 8;

    int session_id = 0;

    inline void incrementSessionId() {
        session_id++; 
    }

} 