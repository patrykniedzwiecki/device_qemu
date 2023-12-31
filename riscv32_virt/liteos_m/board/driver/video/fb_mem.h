/*
 * Copyright (c) 2021-2021 Huawei Device Co., Ltd. All rights reserved.
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

#ifndef _FBMEM_H
#define _FBMEM_H

#include <stdint.h>
#include <stdlib.h>
#include "sys/types.h"
#include "sys/stat.h"
#ifdef LOSCFG_LIBC_NEWLIB
#include "errno.h"
#else
#include "bits/errno.h"
#endif
#include "los_list.h"
#include "los_interrupt.h"
#include "los_debug.h"
#include "los_task.h"
#include "los_mux.h"

#define PATH_MAX 256
#define V_CREATE     (1 << 0)
#define V_DUMMY      (1 << 2)

#ifndef OK
#define OK 0
#endif

struct fb_mem {
    uint32_t hash;                      /* vnode hash */
    uint uid;                           /* uid for dac */
    void *data;                         /* private data */
};

int FbMemInit(void);
int FbMemHold(void);
int FbMemDrop(void);
int FbMemLookup(const char *key, struct fb_mem **result, uint32_t flags);
int register_driver(const char *key, void *prev);
int unregister_driver(const char *key);

#endif