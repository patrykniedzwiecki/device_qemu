/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "los_config.h"
#include "uart.h"

unsigned int LosAppInit(VOID);
unsigned int LosShellInit(void);

// Enable EPU
static void EPUInit(void)
{
#if ((__FPU_PRESENT == 1U) && (__FPU_USED == 1U))
    __asm volatile
    (
        "    .equ CPACR, 0xE000ED88                 \n"
        "                                           \n"
        "    ldr  r0, =CPACR                        \n"
        "    ldr  r1, [r0]                          \n"
        "    orr  r1, r1, #(0xf << 20)              \n"
        "    str  r1, [r0]                          \n"
        "    dsb                                    \n"
        "    isb                                    \n"
        "                                           \n"
        "    .align 4                               \n"
    );
#endif
}

LITE_OS_SEC_TEXT_INIT int main(void)
{
    unsigned int ret;

    EPUInit();
    UartInit();

    ret = LOS_KernelInit();
    if (ret != LOS_OK) {
        printf("LiteOS kernel init failed! ERROR: %u\n", ret);
        goto EXIT;
    }

    Uart0RxIrqRegister();

#if (LOSCFG_USE_SHELL == 1)
    ret = LosShellInit();
    if (ret != LOS_OK) {
        printf("LosAppInit failed! ERROR: %u\n", ret);
    }
#endif

    ret = LosAppInit();
    if (ret != LOS_OK) {
        printf("LosAppInit failed! ERROR: %u\n", ret);
    }

    LOS_Start();

EXIT:
    while (1) {
        __asm volatile("wfi");
    }
}

