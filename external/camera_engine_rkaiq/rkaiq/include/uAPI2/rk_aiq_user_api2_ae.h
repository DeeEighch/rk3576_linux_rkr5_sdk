/*
 *  Copyright (c) 2019 Rockchip Corporation
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
 *
 */

#ifndef __RK_AIQ_USER_API2_AE_H__
#define __RK_AIQ_USER_API2_AE_H__

#include "algos/ae/rk_aiq_uapi_ae_int.h"
#include "isp/rk_aiq_stats_aeStats25.h"

#ifndef RK_AIQ_SYS_CTX_T
#define RK_AIQ_SYS_CTX_T
typedef struct rk_aiq_sys_ctx_s rk_aiq_sys_ctx_t;
#endif

RKAIQ_BEGIN_DECLARE

#if USE_NEWSTRUCT
XCamReturn rk_aiq_user_api2_ae_setExpSwAttr(const rk_aiq_sys_ctx_t* ctx, const ae_api_expSwAttr_t expSwAttr);
XCamReturn rk_aiq_user_api2_ae_getExpSwAttr(const rk_aiq_sys_ctx_t* ctx, ae_api_expSwAttr_t* pExpSwAttr);
XCamReturn rk_aiq_user_api2_ae_setLinExpAttr(const rk_aiq_sys_ctx_t* ctx, const ae_api_linExpAttr_t linExpAttr);
XCamReturn rk_aiq_user_api2_ae_getLinExpAttr(const rk_aiq_sys_ctx_t* ctx, ae_api_linExpAttr_t* pLinExpAttr);
XCamReturn rk_aiq_user_api2_ae_setHdrExpAttr(const rk_aiq_sys_ctx_t* ctx, const ae_api_hdrExpAttr_t hdrExpAttr);
XCamReturn rk_aiq_user_api2_ae_getHdrExpAttr(const rk_aiq_sys_ctx_t* ctx, ae_api_hdrExpAttr_t* pHdrExpAttr);
XCamReturn rk_aiq_user_api2_ae_setIrisAttr(const rk_aiq_sys_ctx_t* ctx, const ae_api_irisAttr_t irisAttr);
XCamReturn rk_aiq_user_api2_ae_getIrisAttr(const rk_aiq_sys_ctx_t* ctx, ae_api_irisAttr_t* pIrisAttr);
XCamReturn rk_aiq_user_api2_ae_setSyncTestAttr(const rk_aiq_sys_ctx_t* ctx, const ae_api_syncTestAttr_t syncTestAttr);
XCamReturn rk_aiq_user_api2_ae_getSyncTestAttr(const rk_aiq_sys_ctx_t* ctx, ae_api_syncTestAttr_t* psyncTestAttr);
XCamReturn rk_aiq_user_api2_ae_queryExpResInfo(const rk_aiq_sys_ctx_t* ctx, ae_api_queryInfo_t* pExpResInfo);
XCamReturn rk_aiq_user_api2_aeMeas_setStatsCfg(const rk_aiq_sys_ctx_t* ctx, rk_aiq_op_mode_t opMode, aeStats_cfg_t* cfg);
XCamReturn rk_aiq_user_api2_ae_getRKAeStats(const rk_aiq_sys_ctx_t* ctx, Uapi_RkAeStats_t* pAeHwStats);
XCamReturn rk_aiq_user_api2_ae_setAttr(const rk_aiq_sys_ctx_t* sys_ctx, ae_param_t attr);
XCamReturn rk_aiq_user_api2_ae_getAttr(const rk_aiq_sys_ctx_t* sys_ctx, ae_param_t* attr);
#else
XCamReturn rk_aiq_user_api2_ae_setExpSwAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_ExpSwAttrV2_t expSwAttr);
XCamReturn rk_aiq_user_api2_ae_getExpSwAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_ExpSwAttrV2_t* pExpSwAttr);
XCamReturn rk_aiq_user_api2_ae_setLinExpAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_LinExpAttrV2_t linExpAttr);
XCamReturn rk_aiq_user_api2_ae_getLinExpAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_LinExpAttrV2_t* pLinExpAttr);
XCamReturn rk_aiq_user_api2_ae_setHdrExpAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_HdrExpAttrV2_t hdrExpAttr);
XCamReturn rk_aiq_user_api2_ae_getHdrExpAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_HdrExpAttrV2_t* pHdrExpAttr);
XCamReturn rk_aiq_user_api2_ae_setLinAeRouteAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_LinAeRouteAttr_t linAeRouteAttr);
XCamReturn rk_aiq_user_api2_ae_getLinAeRouteAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_LinAeRouteAttr_t* pLinAeRouteAttr);
XCamReturn rk_aiq_user_api2_ae_setHdrAeRouteAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_HdrAeRouteAttr_t hdrAeRouteAttr);
XCamReturn rk_aiq_user_api2_ae_getHdrAeRouteAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_HdrAeRouteAttr_t* pHdrAeRouteAttr);
XCamReturn rk_aiq_user_api2_ae_setIrisAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_IrisAttrV2_t irisAttr);
XCamReturn rk_aiq_user_api2_ae_getIrisAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_IrisAttrV2_t* pIrisAttr);
XCamReturn rk_aiq_user_api2_ae_setSyncTestAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_AecSyncTest_t syncTestAttr);
XCamReturn rk_aiq_user_api2_ae_getSyncTestAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_AecSyncTest_t* psyncTestAttr);
XCamReturn rk_aiq_user_api2_ae_queryExpResInfo(const rk_aiq_sys_ctx_t* ctx, Uapi_ExpQueryInfo_t* pExpResInfo);
#endif

XCamReturn rk_aiq_user_api2_ae_setExpWinAttr(const rk_aiq_sys_ctx_t* ctx, const Uapi_ExpWin_t ExpWinAttr);
XCamReturn rk_aiq_user_api2_ae_getExpWinAttr(const rk_aiq_sys_ctx_t* ctx, Uapi_ExpWin_t* pExpWinAttr);
XCamReturn rk_aiq_user_api2_ae_setAecStatsCfg(const rk_aiq_sys_ctx_t* ctx, const Uapi_AecStatsCfg_t AecStatsCfg);
XCamReturn rk_aiq_user_api2_ae_getAecStatsCfg(const rk_aiq_sys_ctx_t* ctx, Uapi_AecStatsCfg_t* pAecStatsCfg);


RKAIQ_END_DECLARE

#endif /*__RK_AIQ_USER_API_AE_H__*/
