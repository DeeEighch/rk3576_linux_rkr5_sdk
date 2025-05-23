/*
 * algo_blc.c
 *
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

#include "algo_types_priv.h"
#include "blc_types_prvt.h"

#include "interpolation.h"
#include "c_base/aiq_base.h"

// RKAIQ_BEGIN_DECLARE

static XCamReturn
create_context(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{
    XCamReturn result = XCAM_RETURN_NO_ERROR;
    CamCalibDbV2Context_t *pCalibDbV2 = cfg->calibv2;
    LOG1_ABLC("%s: (enter)\n", __FUNCTION__ );

    BlcContext_t* ctx = aiq_mallocz(sizeof(BlcContext_t));

    ctx->isReCal_ = true;
    ctx->prepare_params = NULL;
    ctx->isAiIsp = false;
    ctx->blc_attrib =
        (blc_api_attrib_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibDbV2, blc));

    *context = (RkAiqAlgoContext *)(ctx);

    LOG1_ABLC("%s: (exit)\n", __FUNCTION__ );
    return result;

}

static XCamReturn
destroy_context(RkAiqAlgoContext *context)
{
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    LOG1_ABLC("%s: (enter)\n", __FUNCTION__ );

#if 1
    BlcContext_t* pBlcCtx = (BlcContext_t*)context;
    aiq_free(pBlcCtx);
#endif

    LOG1_ABLC("%s: (exit)\n", __FUNCTION__ );
    return result;

}

static XCamReturn
prepare(RkAiqAlgoCom* params)
{
    LOG1_ABLC("%s: (enter)\n", __FUNCTION__ );
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    BlcContext_t* pBlcCtx = (BlcContext_t *)params->ctx;
    RkAiqAlgoConfigAblc* pCfgParam = (RkAiqAlgoConfigAblc*)params;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        // just update calib ptr
        if (params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB_PTR) {
            pBlcCtx->blc_attrib =
                (blc_api_attrib_t*)(CALIBDBV2_GET_MODULE_PTR(params->u.prepare.calibv2, blc));
            pBlcCtx->iso_list = params->u.prepare.calibv2->sensor_info->iso_list;
            return XCAM_RETURN_NO_ERROR;
        }
    }

    pBlcCtx->blc_attrib =
        (blc_api_attrib_t*)(CALIBDBV2_GET_MODULE_PTR(params->u.prepare.calibv2, blc));
    pBlcCtx->iso_list = params->u.prepare.calibv2->sensor_info->iso_list;
    pBlcCtx->isReCal_ = true;
    LOG1_ABLC("%s: (exit)\n", __FUNCTION__ );
    return result;
}

static XCamReturn
pre_process(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ABLC("%s: (enter)\n", __FUNCTION__ );
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    LOG1_ABLC("%s: (exit)\n", __FUNCTION__ );
    return result;
}

static XCamReturn
processing(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    XCamReturn result = XCAM_RETURN_NO_ERROR;
    int delta_iso = 0;
    LOG1_ABLC("%s: (enter)\n", __FUNCTION__ );

    blc_param_t* pAblcProcResParams = (blc_param_t*)outparams->algoRes;
    RkAiqAlgoProcBlc* blc_proc_param = (RkAiqAlgoProcBlc*)inparams;
    BlcContext_t* pBlcCtx = (BlcContext_t *)inparams->ctx;
    blc_api_attrib_t* blc_attrib = pBlcCtx->blc_attrib;

    if (inparams->u.proc.is_attrib_update) {
        pBlcCtx->isReCal_ = true;
    }

    int iso = inparams->u.proc.iso;
    bool init = inparams->u.proc.init;
    delta_iso = abs(iso - pBlcCtx->iso);

    if(delta_iso > ABLC_RECALCULATE_DELTE_ISO) {
        pBlcCtx->isReCal_ = true;
    }
#ifdef ISP_HW_V33
    if (!pBlcCtx->aeIsConverged && blc_proc_param->aeIsConverged && !blc_proc_param->ishdr)
        pBlcCtx->isReCal_ = true;
    pBlcCtx->aeIsConverged = blc_proc_param->aeIsConverged;
#endif

    if (pBlcCtx->isReCal_) {
        BlcSelectParam(pBlcCtx, outparams->algoRes, iso);
        outparams->cfg_update = true;
        outparams->en = blc_attrib->en;
        outparams->bypass = blc_attrib->bypass;
#ifdef supportManualOBC
        LOGD_ABLC("old iso %d new %d, blc: %d %d %d %d blc1: %d %d %d %d", pBlcCtx->iso, iso,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obR_val,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obGr_val,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obGb_val,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obB_val,
                  pAblcProcResParams->dyn.obcPostTnr.hw_blcT_manualOBR_val,
                  pAblcProcResParams->dyn.obcPostTnr.hw_blcT_manualOBGr_val,
                  pAblcProcResParams->dyn.obcPostTnr.hw_blcT_manualOBGb_val,
                  pAblcProcResParams->dyn.obcPostTnr.hw_blcT_manualOBB_val);
#else
        LOGD_ABLC("old iso %d new %d, blc: %d %d %d %d", pBlcCtx->iso, iso,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obR_val,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obGr_val,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obGb_val,
                  pAblcProcResParams->dyn.obcPreTnr.hw_blcC_obB_val);
#endif
        LOGD_ABLC("%s:%d processing ABLC recalculate delta_iso:%d \n", __FUNCTION__, __LINE__, delta_iso);
    } else {
        outparams->cfg_update = false;
    }

    pBlcCtx->iso = iso;
    pBlcCtx->isReCal_ = false;

    LOG1_ABLC("%s: (exit)\n", __FUNCTION__ );
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
post_process(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
BlcSelectParam(BlcContext_t *pBlcCtx, blc_param_t* out, int iso)
{
    LOG1_ABLC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (pBlcCtx == NULL) {
        LOGE_ABLC("%s(%d): NULL pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    if (out == NULL) {
        LOGE_ABLC("%s(%d): NULL pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    int i = 0;
    int iso_low = 0, iso_high = 0, ilow = 0, ihigh = 0;
    float ratio = 0.0f;
    uint16_t uratio;
    blc_param_auto_t *paut = &pBlcCtx->blc_attrib->stAuto;

    pre_interp(iso, pBlcCtx->iso_list, 13, &ilow, &ihigh, &ratio);
    uratio = ratio * (1 << RATIO_FIXBIT);

    // TODO: selecct param
    out->dyn.obcPreTnr.hw_blcC_obR_val = interpolation_i16(
            paut->dyn[ilow].obcPreTnr.hw_blcC_obR_val, paut->dyn[ihigh].obcPreTnr.hw_blcC_obR_val, uratio);
    out->dyn.obcPreTnr.hw_blcC_obGr_val = interpolation_i16(
            paut->dyn[ilow].obcPreTnr.hw_blcC_obGr_val, paut->dyn[ihigh].obcPreTnr.hw_blcC_obGr_val, uratio);
    out->dyn.obcPreTnr.hw_blcC_obGb_val = interpolation_i16(
            paut->dyn[ilow].obcPreTnr.hw_blcC_obGb_val, paut->dyn[ihigh].obcPreTnr.hw_blcC_obGb_val, uratio);
    out->dyn.obcPreTnr.hw_blcC_obB_val = interpolation_i16(
            paut->dyn[ilow].obcPreTnr.hw_blcC_obB_val, paut->dyn[ihigh].obcPreTnr.hw_blcC_obB_val, uratio);
    out->dyn.obcPostTnr.sw_blcT_autoOB_offset = interpolation_u16(
                paut->dyn[ilow].obcPostTnr.sw_blcT_autoOB_offset, paut->dyn[ihigh].obcPostTnr.sw_blcT_autoOB_offset, uratio);
    out->dyn.obcPostTnr.sw_blcT_obcPostTnr_en = paut->dyn[ilow].obcPostTnr.sw_blcT_obcPostTnr_en;
#ifdef ISP_HW_V33
    out->sta.autoBlc.sw_blcT_autoBlc_en = paut->sta.autoBlc.sw_blcT_autoBlc_en;
    out->sta.autoBlc.sw_blcT_autoBlcEn_thred = paut->sta.autoBlc.sw_blcT_autoBlcEn_thred;
    out->sta.autoBlc.sw_blcT_damping_val = paut->sta.autoBlc.sw_blcT_damping_val;
    out->dyn.obcPostTnr.autoBlc.sw_blcT_darkArea_thred = interpolation_u16(
        paut->dyn[ilow].obcPostTnr.autoBlc.sw_blcT_darkArea_thred, paut->dyn[ihigh].obcPostTnr.autoBlc.sw_blcT_darkArea_thred, uratio);
    out->dyn.obcPostTnr.autoBlc.sw_blcT_lumaR_wgt = interpolation_u16(
        paut->dyn[ilow].obcPostTnr.autoBlc.sw_blcT_lumaR_wgt, paut->dyn[ihigh].obcPostTnr.autoBlc.sw_blcT_lumaR_wgt, uratio);
    out->dyn.obcPostTnr.autoBlc.sw_blcT_lumaG_wgt = interpolation_u16(
        paut->dyn[ilow].obcPostTnr.autoBlc.sw_blcT_lumaG_wgt, paut->dyn[ihigh].obcPostTnr.autoBlc.sw_blcT_lumaG_wgt, uratio);
    out->dyn.obcPostTnr.autoBlc.sw_blcT_lumaB_wgt = interpolation_u16(
        paut->dyn[ilow].obcPostTnr.autoBlc.sw_blcT_lumaB_wgt, paut->dyn[ihigh].obcPostTnr.autoBlc.sw_blcT_lumaB_wgt, uratio);
#endif
    return XCAM_RETURN_NO_ERROR;
}

#if 0
XCamReturn
algo_blc_SetAttrib
(
    RkAiqAlgoContext* ctx,
    blc_api_attrib_t *attr
) {
    if(ctx == NULL || attr == NULL) {
        LOGE_ABLC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    BlcContext_t* pBlcCtx = (BlcContext_t*)ctx;
    blc_api_attrib_t* blc_attrib = pBlcCtx->blc_attrib;

    if (attr->opMode != RK_AIQ_OP_MODE_AUTO) {
        LOGE_ABLC("not auto mode: %d", attr->opMode);
        return XCAM_RETURN_ERROR_PARAM;
    }

    blc_attrib->opMode = attr->opMode;
    blc_attrib->en = attr->en;
    blc_attrib->bypass = attr->bypass;

    if (attr->opMode == RK_AIQ_OP_MODE_AUTO)
        blc_attrib->stAuto = attr->stAuto;
    else if (attr->opMode == RK_AIQ_OP_MODE_MANUAL)
        blc_attrib->stMan = attr->stMan;
    else {
        LOGW_ABLC("wrong mode: %d\n", attr->opMode);
    }

    pBlcCtx->isReCal_ = true;

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
algo_blc_GetAttrib
(
    RkAiqAlgoContext* ctx,
    blc_api_attrib_t* attr
)
{
    if(ctx == NULL || attr == NULL) {
        LOGE_ABLC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    BlcContext_t* pBlcCtx = (BlcContext_t*)ctx;
    blc_api_attrib_t* blc_attrib = pBlcCtx->blc_attrib;

#if 0
    if (blc_attrib->opMode != RK_AIQ_OP_MODE_AUTO) {
        LOGE_ABLC("not auto mode: %d", blc_attrib->opMode);
        return XCAM_RETURN_ERROR_PARAM;
    }
#endif

    attr->opMode = blc_attrib->opMode;
    attr->en = blc_attrib->en;
    attr->bypass = blc_attrib->bypass;
    memcpy(&attr->stAuto, &blc_attrib->stAuto, sizeof(blc_param_auto_t));

    return XCAM_RETURN_NO_ERROR;
}
#endif

#define RKISP_ALGO_BLC_VERSION     "v0.0.1"
#define RKISP_ALGO_BLC_VENDOR      "Rockchip"
#define RKISP_ALGO_BLC_DESCRIPTION "Rockchip blc algo for ISP2.0"

RkAiqAlgoDescription g_RkIspAlgoDescBlc = {
    .common = {
        .version = RKISP_ALGO_BLC_VERSION,
        .vendor  = RKISP_ALGO_BLC_VENDOR,
        .description = RKISP_ALGO_BLC_DESCRIPTION,
        .type    = RK_AIQ_ALGO_TYPE_ABLC,
        .id      = 0,
        .create_context  = create_context,
        .destroy_context = destroy_context,
    },
    .prepare = prepare,
    .pre_process = pre_process,
    .processing = processing,
    .post_process = post_process,
};

// RKAIQ_END_DECLARE
