#pragma once
#include <ViGEm/Client.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
		int status;               // 0 = error, other = success

		VIGEM_ERROR error;      // TODO: use custom error code 
    } Gamepad_Result;

#ifdef __cplusplus
}
#endif
