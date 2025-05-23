/*
 * Copyright 2018 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MPP_DEC_VPROC_H__
#define __MPP_DEC_VPROC_H__

#include "mpp_dec_cfg.h"
#include "hal_dec_task.h"

typedef struct MppDecVprocCfg_t {
    void            *mpp;
    HalTaskGroup    task_group;
} MppDecVprocCfg;

typedef void* MppDecVprocCtx;

#ifdef __cplusplus

extern "C" {
#endif

/*
 * Functions usage:
 * dec_vproc_init   - get context with cfg
 * dec_vproc_deinit - stop thread and destory context
 * dec_vproc_start  - start thread processing
 * dec_vproc_signal - signal thread that one frame has be pushed for process
 * dec_vproc_reset  - reset process thread and discard all input
 */

MPP_RET dec_vproc_init(MppDecVprocCtx *ctx, MppDecVprocCfg *cfg);
MPP_RET dec_vproc_deinit(MppDecVprocCtx ctx);

MPP_RET dec_vproc_start(MppDecVprocCtx ctx);
MPP_RET dec_vproc_stop(MppDecVprocCtx ctx);
MPP_RET dec_vproc_signal(MppDecVprocCtx ctx);
MPP_RET dec_vproc_reset(MppDecVprocCtx ctx);
RK_U32 dec_vproc_get_version(MppDecVprocCtx ctx);
void dec_vproc_enable_detect(MppDecVprocCtx ctx);
MPP_RET dec_vproc_set_mode(MppDecVprocCtx ctx, MppVprocMode mode);

#ifdef __cplusplus
}
#endif

#endif /* __MPP_DEC_VPROC_H__ */
