/*
 * Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
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

#include "newStruct/dehaze/include/dehaze_algo_api.h"
#include "uAPI2/rk_aiq_user_api2_dehaze.h"
#include "algo_handlers/newStruct/RkAiqDehazeHandler.h"
#include "include/uAPI2/rk_aiq_user_api2_imgproc.h"
#include "RkAiqGlobalParamsManager.h"

RKAIQ_BEGIN_DECLARE

#ifdef RK_SIMULATOR_HW
#define CHECK_USER_API_ENABLE
#endif

#ifndef USE_IMPLEMENT_C
/*
*****************************
*
* Desc: set/get manual dehaze strength
*     this function is active for dehaze is manual mode
* Argument:
*   level: [0, 100]
*
*****************************
*/
static XCamReturn
_dehaze_SetMDehazeStrth(const rk_aiq_sys_ctx_t* sys_ctx, dehazeStrth ctrl)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqDehazeHandleInt* algo_handle =
        algoHandle<RkAiqDehazeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADHAZ);
    if (algo_handle) {
        algo_handle->setMDehazeStrth(ctrl);
    }
    return ret;
}

static XCamReturn
_dehaze_GetMDehazeStrth(const rk_aiq_sys_ctx_t* sys_ctx, dehazeStrth *ctrl)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqDehazeHandleInt* algo_handle =
        algoHandle<RkAiqDehazeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADHAZ);
    if (algo_handle) {
        algo_handle->getMDehazeStrth(ctrl);
    }
    return ret;
}


XCamReturn rk_aiq_user_api2_setDehazeEnhanceStrth(const rk_aiq_sys_ctx_t* sys_ctx, dehazeStrth ctrl)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
#if USE_NEWSTRUCT
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADHAZ);
    RKAIQ_API_SMART_LOCK(sys_ctx);
    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t*)sys_ctx;
        if (camgroup_ctx->cam_ctxs_array[0])
            return _dehaze_SetMDehazeStrth(camgroup_ctx->cam_ctxs_array[0], ctrl);
        else
            return XCAM_RETURN_ERROR_FAILED;
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        return _dehaze_SetMDehazeStrth(sys_ctx, ctrl);
    }
#else
    return XCAM_RETURN_ERROR_UNKNOWN;
#endif
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn rk_aiq_user_api2_getDehazeEnhanceStrth(const rk_aiq_sys_ctx_t* sys_ctx, dehazeStrth *ctrl)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
#if USE_NEWSTRUCT
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADHAZ);
    RKAIQ_API_SMART_LOCK(sys_ctx);
    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t *)sys_ctx;
        if (camgroup_ctx->cam_ctxs_array[0])
            return _dehaze_GetMDehazeStrth(camgroup_ctx->cam_ctxs_array[0], ctrl);
        else
            return XCAM_RETURN_ERROR_FAILED;
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        return _dehaze_GetMDehazeStrth(sys_ctx, ctrl);
    }
#else
    return XCAM_RETURN_ERROR_UNKNOWN;
#endif
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
_dehaze_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx, dehaze_api_attrib_t* attr)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    /*
    if (!rk_aiq_dehaze_check_attrib(attr)) {
        LOGE_ANR("dehaze wrong attrib!");
        return ret;
    }
    */

    rk_aiq_global_params_wrap_t params;
    params.opMode = attr->opMode;
    params.bypass = attr->bypass;
    params.en = attr->en;
    params.type = RESULT_TYPE_DEHAZE_PARAM;
    params.man_param_size = sizeof(dehaze_param_t);
    params.man_param_ptr = &attr->stMan;
    params.aut_param_size = sizeof(dehaze_param_auto_t);
    params.aut_param_ptr = &attr->stAuto;
    ret = sys_ctx->_rkAiqManager->getGlobalParamsManager()->set(&params);

    return ret;
}

XCamReturn
rk_aiq_user_api2_dehaze_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx, dehaze_api_attrib_t* attr)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
#if USE_NEWSTRUCT
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADHAZ);
    RKAIQ_API_SMART_LOCK(sys_ctx);
    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t *)sys_ctx;
        for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
            if (!camCtx)
                continue;
            ret = _dehaze_SetAttrib(camCtx, attr);
        }
        return ret;
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        return _dehaze_SetAttrib(sys_ctx, attr);
    }
#else
    return XCAM_RETURN_ERROR_UNKNOWN;
#endif
}

static XCamReturn
_dehaze_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx, dehaze_api_attrib_t* attr)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqDehazeHandleInt* algo_handle =
        algoHandle<RkAiqDehazeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADHAZ);

    if (algo_handle) {
        algo_handle->getAttrib(attr);
    }

    // get cur manual params
    rk_aiq_global_params_wrap_t params;
    params.type = RESULT_TYPE_DEHAZE_PARAM;
    params.man_param_size = sizeof(dehaze_param_t);
    params.man_param_ptr = &attr->stMan;
    ret = sys_ctx->_rkAiqManager->getGlobalParamsManager()->get(&params);
    if (ret == XCAM_RETURN_NO_ERROR) {
        attr->en = params.en;
        attr->bypass = params.bypass;
        attr->opMode = (RKAiqOPMode_t)params.opMode;
    }

    return ret;
}

XCamReturn
rk_aiq_user_api2_dehaze_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx, dehaze_api_attrib_t* attr)
{
#if USE_NEWSTRUCT
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADHAZ);
    RKAIQ_API_SMART_LOCK(sys_ctx);
    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t *)sys_ctx;
        for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
            if (!camCtx)
                continue;
            // return the first cam's attrib
            return _dehaze_GetAttrib(camCtx , attr);
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        return _dehaze_GetAttrib(sys_ctx, attr);
    }
#else
    return XCAM_RETURN_ERROR_UNKNOWN;
#endif
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
_dehaze_QueryStatus(const rk_aiq_sys_ctx_t* sys_ctx, dehaze_status_t* status)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (sys_ctx->_rkAiqManager->getGlobalParamsManager()->isManual(RESULT_TYPE_DEHAZE_PARAM)) {
        // get cur manual params
        rk_aiq_global_params_wrap_t params;
        params.type = RESULT_TYPE_DEHAZE_PARAM;
        params.man_param_size = sizeof(dehaze_param_t);
        params.man_param_ptr = &status->stMan;
        ret = sys_ctx->_rkAiqManager->getGlobalParamsManager()->get(&params);
        if (ret == XCAM_RETURN_NO_ERROR) {
            status->en = params.en;
            status->bypass = params.bypass;
            status->opMode = (RKAiqOPMode_t)params.opMode;
        }
    } else {
        RkAiqDehazeHandleInt* algo_handle =
            algoHandle<RkAiqDehazeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADHAZ);

        if (algo_handle) {
            return algo_handle->queryStatus(status);
        }
    }

    return ret;
}

XCamReturn
rk_aiq_user_api2_dehaze_QueryStatus(const rk_aiq_sys_ctx_t* sys_ctx, dehaze_status_t* status)
{
#if USE_NEWSTRUCT
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADHAZ);
    RKAIQ_API_SMART_LOCK(sys_ctx);
    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t *)sys_ctx;
        for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
            if (!camCtx)
                continue;
            // return the first cam's attrib
            return _dehaze_QueryStatus(camCtx , status);
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        return _dehaze_QueryStatus(sys_ctx, status);
    }
#else
    return XCAM_RETURN_ERROR_UNKNOWN;
#endif
   return XCAM_RETURN_NO_ERROR;
}
#endif

RKAIQ_END_DECLARE
