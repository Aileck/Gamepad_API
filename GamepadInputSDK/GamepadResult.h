#pragma once
#include <ViGEm/Client.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
		int STATUS;               // 0 = error, other = success

		VIGEM_ERROR error;      // error 
    } Gamepad_Result;

#ifdef __cplusplus
}
#endif
