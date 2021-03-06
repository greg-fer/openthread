/*
 *  Copyright (c) 2019, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file includes the platform-specific initializers.
 *
 */
#include "board.h"
#include "pin_mux.h"
#include "platform-jn5189.h"
#include "openthread/platform/uart.h"

#include <stdbool.h>
#include <stdint.h>

otInstance *sInstance;

void otSysInit(int argc, char *argv[])
{
    bool bHwInit = true;

    if ((argc == 1) && (!strcmp(argv[0], "app")))
    {
        bHwInit = false;
    }

    if (bHwInit)
    {
        /* Security code to allow debug access */
        SYSCON->CODESECURITYPROT = 0x87654320;

        BOARD_BootClockRUN();
        BOARD_InitPins();
    }

    JN5189AlarmInit();
    JN5189RandomInit();
    JN5189RadioInit();
}

bool otSysPseudoResetWasRequested(void)
{
    /* TODO */
    return false;
}

void otSysDeinit(void)
{
    /* TODO */
}

void otSysProcessDrivers(otInstance *aInstance)
{
    JN5189RadioProcess(aInstance);
    JN5189UartProcess();
    JN5189AlarmProcess(aInstance);
}

void otSysEventSignalPending(void)
{
    /* TODO */
}
