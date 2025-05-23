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

#ifndef _RK_AIQ_TYPES_PRIV_H_
#define _RK_AIQ_TYPES_PRIV_H_
#include <string>
#include <vector>
#include "rk_aiq_types.h"
#include "algo_types_priv.h"
#include "rk-camera-module.h"
#include "MessageBus.h"
#include "common/rkisp2-config.h"
#include "common/rkisp21-config.h"
#include "common/rkisp3-config.h"
#include "common/rkisp32-config.h"
#include "common/rk-isp39-config.h"
#include "buffer_pool.h"
#if USE_NEWSTRUCT
#include "isp/rk_aiq_isp_trans10.h"
#include "algos/rk_aiq_api_types_trans.h"
#endif

#define RKAIQ_ISP_LDCH_ID           (1 << 0)

template<class T>
struct rk_aiq_isp_params_t : public XCam::BufferData {
    /* should be the first member */
    union {
        struct {
            bool is_update;
            bool en;
            bool bypass;
        } __attribute__ ((packed));
        char aligned[4]; // for aligned to 4 
    };
    T   result;
    uint32_t frame_id;
    uint32_t sync_flag;
    rk_aiq_isp_params_t() {
        is_update = false;
        sync_flag = (uint32_t)(-2); // initial value should be different with handler's
    }
};

//common
typedef rk_aiq_isp_params_t<rk_aiq_isp_stats_t>      rk_aiq_isp_stats_wrapper_t;
typedef rk_aiq_isp_params_t<rk_aiq_focus_params_t>      rk_aiq_focus_params_wrapper_t;

// Same part of different versions
typedef rk_aiq_isp_params_t<rk_aiq_isp_aec_meas_t>      rk_aiq_isp_aec_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_hist_meas_t>     rk_aiq_isp_hist_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_dpcc_t>          rk_aiq_isp_dpcc_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_tmo_t>           rk_aiq_isp_tmo_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_lsc_t>           rk_aiq_isp_lsc_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_rawnr_t>         rk_aiq_isp_rawnr_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_gic_t>           rk_aiq_isp_gic_params_t;
#endif
#if USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<lut3d_param_t>              rk_aiq_isp_lut3d_params_t;
#else
typedef rk_aiq_isp_params_t<rk_aiq_isp_lut3d_t>         rk_aiq_isp_lut3d_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_degamma_t>       rk_aiq_isp_adegamma_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_wdr_t>           rk_aiq_isp_wdr_params_t;
#if USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<csm_param_t>                rk_aiq_isp_csm_params_t;
#else
typedef rk_aiq_isp_params_t<rk_aiq_isp_csm_t>           rk_aiq_isp_csm_params_t;
#endif
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_cgc_t>           rk_aiq_isp_cgc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_acp_t>           rk_aiq_isp_cp_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ie_t>            rk_aiq_isp_ie_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_conv422_t>       rk_aiq_isp_conv422_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_yuvconv_t>       rk_aiq_isp_yuvconv_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_motion_t>        rk_aiq_isp_motion_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_amd_t>           rk_aiq_isp_md_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_uvnr_t>          rk_aiq_isp_uvnr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_edgeflt_t>       rk_aiq_isp_edgeflt_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_fec_t>           rk_aiq_isp_fec_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_orb_t>           rk_aiq_isp_orb_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_afd_t>           rk_aiq_isp_afd_params_t;


// Different parts of different versions. Some parameters may be duplicated
#ifdef ISP_HW_V20
typedef rk_aiq_isp_params_t<rk_aiq_isp_awb_meas_cfg_t>  rk_aiq_isp_awb_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_wb_gain_t>       rk_aiq_isp_awb_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_af_meas_t>       rk_aiq_isp_af_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_merge_t>         rk_aiq_isp_merge_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ccm_t>           rk_aiq_isp_ccm_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_blc_t>           rk_aiq_isp_blc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_debayer_t>       rk_aiq_isp_debayer_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ldch_t>          rk_aiq_isp_ldch_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_dehaze_t>        rk_aiq_isp_dehaze_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gamma_t>         rk_aiq_isp_agamma_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gain_t>          rk_aiq_isp_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_tnr_t>           rk_aiq_isp_tnr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ynr_t>           rk_aiq_isp_ynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_sharpen_t>       rk_aiq_isp_sharpen_params_t;

#endif

#ifdef ISP_HW_V21
typedef rk_aiq_isp_params_t<rk_aiq_isp_awb_meas_cfg_v21_t>    rk_aiq_isp_awb_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_wb_gain_t>             rk_aiq_isp_awb_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_af_meas_t>             rk_aiq_isp_af_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_merge_t>               rk_aiq_isp_merge_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ccm_t>                 rk_aiq_isp_ccm_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_blc_v21_t>             rk_aiq_isp_blc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_debayer_t>             rk_aiq_isp_debayer_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ldch_t>                rk_aiq_isp_ldch_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_dehaze_t>              rk_aiq_isp_dehaze_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gamma_t>               rk_aiq_isp_agamma_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gain_t>                rk_aiq_isp_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_tnr_t>                 rk_aiq_isp_tnr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ynr_v21_t>             rk_aiq_isp_ynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_sharp_v21_t>           rk_aiq_isp_sharpen_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_drc_v21_t>             rk_aiq_isp_drc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_baynr_v21_t>           rk_aiq_isp_baynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_bay3d_v21_t>           rk_aiq_isp_bay3d_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_cnr_v21_t>             rk_aiq_isp_cnr_params_t;

#endif

#ifdef ISP_HW_V30
typedef rk_aiq_isp_params_t<rk_aiq_isp_awb_meas_cfg_v3x_t>    rk_aiq_isp_awb_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_wb_gain_t>             rk_aiq_isp_awb_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_af_meas_v3x_t>         rk_aiq_isp_af_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_merge_t>               rk_aiq_isp_merge_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ccm_t>                 rk_aiq_isp_ccm_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_blc_v21_t>             rk_aiq_isp_blc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_debayer_t>             rk_aiq_isp_debayer_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ldch_t>                rk_aiq_isp_ldch_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_dehaze_v3x_t>          rk_aiq_isp_dehaze_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_goc_v3x_t>             rk_aiq_isp_agamma_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gain_v3x_t>            rk_aiq_isp_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_tnr_v3x_t>             rk_aiq_isp_tnr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ynr_v3x_t>             rk_aiq_isp_ynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_sharp_v3x_t>           rk_aiq_isp_sharpen_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_drc_v3x_t>             rk_aiq_isp_drc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_baynr_v3x_t>           rk_aiq_isp_baynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_bay3d_v3x_t>           rk_aiq_isp_bay3d_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_cnr_v3x_t>             rk_aiq_isp_cnr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_cac_v3x_t>             rk_aiq_isp_cac_params_t;
#endif

#ifdef ISP_HW_V32
typedef rk_aiq_isp_params_t<rk_aiq_isp_awb_meas_cfg_v32_t>    rk_aiq_isp_awb_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_wb_gain_v32_t>         rk_aiq_isp_awb_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_af_v31_t>              rk_aiq_isp_af_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_merge_t>               rk_aiq_isp_merge_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_ccm_v32_t>             rk_aiq_isp_ccm_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_blc_v32_t>             rk_aiq_isp_blc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_debayer_v32_t>         rk_aiq_isp_debayer_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_ldch_v21_t>            rk_aiq_isp_ldch_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_dehaze_v32_t>          rk_aiq_isp_dehaze_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_goc_v3x_t>             rk_aiq_isp_agamma_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gain_v3x_t>            rk_aiq_isp_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_tnr_v32_t>             rk_aiq_isp_tnr_params_t;
#if (USE_NEWSTRUCT == 0)
typedef rk_aiq_isp_params_t<rk_aiq_isp_ynr_v32_t>             rk_aiq_isp_ynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_cnr_v32_t>             rk_aiq_isp_cnr_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_sharp_v32_t>           rk_aiq_isp_sharpen_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_drc_v3x_t>             rk_aiq_isp_drc_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_baynr_v32_t>           rk_aiq_isp_baynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_bay3d_v32_t>           rk_aiq_isp_bay3d_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_cac_v32_t>             rk_aiq_isp_cac_params_t;
#endif
#endif

#ifdef ISP_HW_V32_LITE
typedef rk_aiq_isp_params_t<rk_aiq_isp_awb_meas_cfg_v32_t>    rk_aiq_isp_awb_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_wb_gain_v32_t>         rk_aiq_isp_awb_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_af_v32_t>              rk_aiq_isp_af_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_merge_v3x_t>           rk_aiq_isp_merge_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ccm_v32_t>             rk_aiq_isp_ccm_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_blc_v32_t>             rk_aiq_isp_blc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_debayer_v32_t>         rk_aiq_isp_debayer_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ldch_v21_t>            rk_aiq_isp_ldch_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_dehaze_v32_t>          rk_aiq_isp_dehaze_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_goc_v3x_t>             rk_aiq_isp_agamma_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gain_v3x_t>            rk_aiq_isp_gain_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_tnr_v32_t>             rk_aiq_isp_tnr_params_t;
#if (USE_NEWSTRUCT == 0)
typedef rk_aiq_isp_params_t<rk_aiq_isp_ynr_v32_t>             rk_aiq_isp_ynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_cnr_v32_t>             rk_aiq_isp_cnr_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_sharp_v32_t>           rk_aiq_isp_sharpen_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_drc_v3x_t>             rk_aiq_isp_drc_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_baynr_v32_t>           rk_aiq_isp_baynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_bay3d_v32_t>           rk_aiq_isp_bay3d_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_cac_v32_t>             rk_aiq_isp_cac_params_t;
#endif

#ifdef ISP_HW_V39
//typedef rk_aiq_isp_params_t<rk_aiq_isp_awb_meas_cfg_v39_t>    rk_aiq_isp_awb_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_wb_gain_v32_t>         rk_aiq_isp_awb_gain_params_t;
#if USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<afStats_cfg_t>                    rk_aiq_isp_af_params_t;
#else
typedef rk_aiq_isp_params_t<rk_aiq_isp_af_v33_t>              rk_aiq_isp_af_params_t;
#endif
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_merge_t>               rk_aiq_isp_merge_params_t;
#endif
#if USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<ccm_param_t>                      rk_aiq_isp_ccm_params_t;
typedef rk_aiq_isp_params_t<blc_param_t>                      rk_aiq_isp_blc_params_t;
#else
typedef rk_aiq_isp_params_t<rk_aiq_isp_ccm_v32_t>             rk_aiq_isp_ccm_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_blc_v32_t>             rk_aiq_isp_blc_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_debayer_v39_t>         rk_aiq_isp_debayer_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_ldch_v21_t>            rk_aiq_isp_ldch_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_dehaze_v32_t>          rk_aiq_isp_dehaze_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_gain_v3x_t>            rk_aiq_isp_gain_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_goc_v3x_t>             rk_aiq_isp_agamma_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_tnr_v39_t>             rk_aiq_isp_tnr_params_t;
#if (USE_NEWSTRUCT == 0)
typedef rk_aiq_isp_params_t<rk_aiq_isp_ynr_v39_t>             rk_aiq_isp_ynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_cnr_v39_t>             rk_aiq_isp_cnr_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_sharp_v39_t>           rk_aiq_isp_sharpen_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_drc_v39_t>             rk_aiq_isp_drc_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_baynr_v32_t>           rk_aiq_isp_baynr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_bay3d_v32_t>           rk_aiq_isp_bay3d_params_t;
#ifndef USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<rk_aiq_isp_cac_v32_t>             rk_aiq_isp_cac_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_rgbir_v39_t>           rk_aiq_isp_rgbir_params_t;
#endif
typedef rk_aiq_isp_params_t<rk_aiq_isp_yuvme_v39_t>           rk_aiq_isp_yuvme_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_ldc_t> rk_aiq_isp_ldc_params_t;
#endif

// new struct
// dm for v32, TODO: how to distinguish hw version ?
#if USE_NEWSTRUCT
typedef rk_aiq_isp_params_t<aeStats_cfg_t>      rk_aiq_isp_ae_stats_cfg_t;
typedef rk_aiq_isp_params_t<dm_param_t>         rk_aiq_isp_dm_params_t;
typedef rk_aiq_isp_params_t<btnr_param_t>       rk_aiq_isp_btnr_params_t;
typedef rk_aiq_isp_params_t<gamma_param_t>      rk_aiq_isp_gamma_params_t;
typedef rk_aiq_isp_params_t<ynr_param_t>        rk_aiq_isp_ynr_params_t;
typedef rk_aiq_isp_params_t<sharp_param_t>      rk_aiq_isp_sharp_params_t;
typedef rk_aiq_isp_params_t<cnr_param_t>        rk_aiq_isp_cnr_params_t;
typedef rk_aiq_isp_params_t<rk_aiq_isp_drc_v39_t>      rk_aiq_isp_drc_params_t;
// typedef rk_aiq_isp_params_t<rk_aiq_isp_dehaze_v39_t>      rk_aiq_isp_dehaze_params_t;
typedef rk_aiq_isp_params_t<dpc_param_t>          rk_aiq_isp_dpcc_params_t;
typedef rk_aiq_isp_params_t<gic_param_t>         rk_aiq_isp_gic_params_t;
typedef rk_aiq_isp_params_t<yme_param_t>         rk_aiq_isp_yme_params_t;
typedef rk_aiq_isp_params_t<cac_param_t>      rk_aiq_isp_cac_params_t;
typedef rk_aiq_isp_params_t<mge_param_t>      rk_aiq_isp_merge_params_t;
typedef rk_aiq_isp_params_t<lsc_param_t>      rk_aiq_isp_lsc_params_t;
typedef rk_aiq_isp_params_t<rgbir_param_t>         rk_aiq_isp_rgbir_params_t;
typedef rk_aiq_isp_params_t<cgc_param_t>      rk_aiq_isp_cgc_params_t;
typedef rk_aiq_isp_params_t<cp_param_t>      rk_aiq_isp_cp_params_t;
typedef rk_aiq_isp_params_t<ie_param_t>      rk_aiq_isp_ie_params_t;
typedef rk_aiq_isp_params_t<gain_param_t>      rk_aiq_isp_gain_params_t;
#endif

#ifdef ISP_HW_V20
typedef struct rkisp_effect_params_s {
    struct isp2x_isp_params_cfg isp_params;
    rk_aiq_awb_stat_cfg_v200_t  awb_cfg;
} rkisp_effect_params_v20;
#elif ISP_HW_V21
typedef struct rkisp_effect_params_s {
    struct isp21_isp_params_cfg isp_params_v21;
    rk_aiq_awb_stat_cfg_v201_t  awb_cfg_v201;
    rk_aiq_isp_blc_v21_t blc_cfg;
} rkisp_effect_params_v20;
#elif ISP_HW_V30
typedef struct rkisp_effect_params_s {
    struct isp3x_isp_params_cfg isp_params_v3x[3];
    rk_aiq_isp_awb_meas_cfg_v3x_t awb_cfg_v3x;
    rk_aiq_isp_blc_v21_t blc_cfg;
} rkisp_effect_params_v20;
#elif defined(ISP_HW_V32) || defined(ISP_HW_V32_LITE)
typedef struct rkisp_effect_params_s {
#if defined(RKAIQ_HAVE_MULTIISP)
    struct isp32_isp_params_cfg isp_params_v32[4];
#endif
    struct isp32_isp_meas_cfg meas;
    struct isp32_bls_cfg bls_cfg;
    struct isp32_awb_gain_cfg awb_gain_cfg;
    rk_aiq_awb_stat_cfg_v32_t awb_cfg_v32;
} rkisp_effect_params_v20;
#elif defined(ISP_HW_V39)
typedef struct rkisp_effect_params_s {
#if defined(RKAIQ_HAVE_MULTIISP)
    struct isp39_isp_params_cfg isp_params_v39[2];
#endif
    struct isp39_isp_meas_cfg meas;
    struct isp32_bls_cfg bls_cfg;
    struct isp32_awb_gain_cfg awb_gain_cfg;
    awbStats_cfg_priv_t awb_cfg_v39;
#if defined(USE_NEWSTRUCT)
    aeStats_cfg_t ae_cfg_v39;
#endif
} rkisp_effect_params_v20;
#else
typedef struct rkisp_effect_params_s {
    union {
        struct isp2x_isp_params_cfg isp_params;
        struct isp21_isp_params_cfg isp_params_v21;
        struct isp3x_isp_params_cfg isp_params_v3x[3];
        struct isp32_isp_params_cfg isp_params_v32;
    };
    union {
        rk_aiq_awb_stat_cfg_v200_t  awb_cfg;
        rk_aiq_awb_stat_cfg_v201_t  awb_cfg_v201;
        rk_aiq_isp_awb_meas_cfg_v3x_t awb_cfg_v3x;
        rk_aiq_awb_stat_cfg_v32_t awb_cfg_v32;

    };
    rk_aiq_isp_blc_v21_t blc_cfg;
} rkisp_effect_params_v20;
#endif

typedef rk_aiq_isp_params_t<rkisp_effect_params_v20>  rkisp_effect_params;

#define RKAIQ_ISPP_TNR_ID           (1 << 0)
#define RKAIQ_ISPP_NR_ID            (1 << 1)
#define RKAIQ_ISPP_SHARP_ID         (1 << 2)
#define RKAIQ_ISPP_FEC_ID           (1 << 3)
#define RKAIQ_ISPP_ORB_ID           (1 << 4)
#define RKAIQ_ISPP_FEC_ST_ID        (1<< 17 | RKAIQ_ISPP_FEC_ID)

typedef enum rk_aiq_drv_share_mem_type_e {
    MEM_TYPE_LDCH,
    MEM_TYPE_FEC,
    MEM_TYPE_CAC,
    MEM_TYPE_DBG_INFO,
    MEM_TYPE_LDCV,
} rk_aiq_drv_share_mem_type_t;

typedef void (*alloc_mem_t)(uint8_t id, void* ops_ctx, void* cfg, void** mem_ctx);
typedef void (*release_mem_t)(uint8_t id, void* mem_ctx);
typedef void* (*get_free_item_t)(uint8_t id, void* mem_ctx);
typedef struct isp_drv_share_mem_ops_s {
    alloc_mem_t alloc_mem;
    release_mem_t release_mem;
    get_free_item_t get_free_item;
} isp_drv_share_mem_ops_t;

typedef struct rk_aiq_lut_share_mem_info_s {
    int size{ -1 };
    void* map_addr{ nullptr };
    void* addr{ nullptr };
    int fd{ -1 };
    char* state{ nullptr };
} rk_aiq_lut_share_mem_info_t;

typedef rk_aiq_lut_share_mem_info_t rk_aiq_ldch_share_mem_info_t;
typedef rk_aiq_lut_share_mem_info_t rk_aiq_ldcv_share_mem_info_t;
typedef rk_aiq_lut_share_mem_info_t rk_aiq_cac_share_mem_info_t;
typedef rk_aiq_lut_share_mem_info_t rk_aiq_dbg_share_mem_info_t;

typedef struct rk_aiq_fec_share_mem_info_s {
    int size;
    int fd;
    void* map_addr;
    unsigned char* meshxf;
    unsigned char* meshyf;
    unsigned short* meshxi;
    unsigned short* meshyi;
    char* state;
} rk_aiq_fec_share_mem_info_t;

typedef struct rk_aiq_share_mem_alloc_param_s {
    int width;
    int height;
    char reserved[8];
} rk_aiq_share_mem_alloc_param_t;

typedef struct rk_aiq_share_mem_config_s {
    rk_aiq_drv_share_mem_type_t mem_type;
    rk_aiq_share_mem_alloc_param_t alloc_param;
} rk_aiq_share_mem_config_t;

struct rk_aiq_vbuf_info {
    uint32_t frame_id;
    uint32_t timestamp;
    float    exp_time;
    float    exp_gain;
    uint32_t exp_time_reg;
    uint32_t exp_gain_reg;
    uint32_t data_fd;
    uint8_t* data_addr;
    uint32_t data_length;
    rk_aiq_rawbuf_type_t buf_type;
    bool valid;
};

struct rk_aiq_vbuf {
    void* base_addr;
    uint32_t frame_width;
    uint32_t frame_height;
    struct rk_aiq_vbuf_info buf_info[3];/*index: 0-short,1-medium,2-long*/
};

typedef struct rk_aiq_tx_info_s {
    uint32_t            width;
    uint32_t            height;
    uint8_t             bpp;
    uint8_t             bayer_fmt;
    uint32_t            stridePerLine;
    uint32_t            bytesPerLine;
    bool                storage_type;
    uint32_t            id;
    //get from AE
    bool                IsAeConverged;
    bool                envChange;
    void* data_addr;
    RKAiqAecExpInfo_t* aecExpInfo;
} rk_aiq_tx_info_t;

enum cam_thread_type_e {
    ISP_POLL_LUMA,
    ISP_POLL_3A_STATS,
    ISP_POLL_PARAMS,
    ISPP_POLL_FEC_PARAMS,
    ISPP_POLL_TNR_PARAMS,
    ISPP_POLL_NR_PARAMS,
    ISPP_POLL_TNR_STATS,
    ISPP_POLL_NR_STATS,
    ISP_POLL_SOF,
    ISP_POLL_TX,
    ISP_POLL_RX,
    ISP_POLL_SP,
    ISP_POLL_PDAF_STATS,
    ISP_GAIN,
    ISP_NR_IMG,
    ISPP_GAIN_KG,
    ISPP_GAIN_WR,
    ISP_POLL_ISPSTREAMSYNC,
    VICAP_STREAM_ON_EVT,
    VICAP_RESET_EVT,
    VICAP_WITH_RK1608_RESET_EVT,
    VICAP_POLL_SCL,
    ISP_POLL_AIISP,
    ISP_POLL_POST_MAX,
};

/*
 * enum cam_result_type_e {
 *     RESULT_TYPE_INVALID,
 *     RESULT_TYPE_EXPOSURE,
 *     RESULT_TYPE_ISP_OTHER,
 *     RESULT_TYPE_ISPP_OTHER,
 *     RESULT_TYPE_ISP_MEAS,
 *     RESULT_TYPE_ISPP_MEAS,
 *     RESULT_TYPE_AF_PARAM,
 *     RESULT_TYPE_IRIS_PARAM,
 *     RESULT_TYPE_CPSL_PARAM,
 *     RESULT_TYPE_FLASH_PARAM
 * };
 */

#define MAX_MEDIA_INDEX               16
#define DEV_PATH_LEN                  32
#define SENSOR_ATTACHED_FLASH_MAX_NUM 2
#define MAX_CAM_NUM                   8

#define MAX_ISP_LINKED_VICAP_CNT      4

#define ISP_TX_BUF_NUM 4
#define VIPCAP_TX_BUF_NUM      4
#define VIPCAP_TX_BUF_NUM_1608 6    // For mount 3 sensor, is mount 4 sensor, is 7

typedef struct {
    int  model_idx;
    int  logic_id;
    int  phy_id; // physical isp id
    int  linked_sensor;
    bool is_multi_isp_mode; // isp-unit mode, 2 isp to 1
    bool isMultiplex;      // muliplex mode, virtually sed by more than one sensor
    bool linked_dvp;
    bool valid;
    char media_dev_path[DEV_PATH_LEN];
    char isp_dev_path[DEV_PATH_LEN];
    char csi_dev_path[DEV_PATH_LEN];
    char mpfbc_dev_path[DEV_PATH_LEN];
    char main_path[DEV_PATH_LEN];
    char self_path[DEV_PATH_LEN];
    char ldc_path[DEV_PATH_LEN];
    char rawwr0_path[DEV_PATH_LEN];
    char rawwr1_path[DEV_PATH_LEN];
    char rawwr2_path[DEV_PATH_LEN];
    char rawwr3_path[DEV_PATH_LEN];
    char dma_path[DEV_PATH_LEN];
    char rawrd0_m_path[DEV_PATH_LEN];
    char rawrd1_l_path[DEV_PATH_LEN];
    char rawrd2_s_path[DEV_PATH_LEN];
    char stats_path[DEV_PATH_LEN];
    char input_params_path[DEV_PATH_LEN];
    char mipi_luma_path[DEV_PATH_LEN];
    char mipi_dphy_rx_path[DEV_PATH_LEN];
    char linked_vicap[MAX_ISP_LINKED_VICAP_CNT][DEV_PATH_LEN];
    char linked_vicap_sd_path[DEV_PATH_LEN];
    char pdaf_path[DEV_PATH_LEN];
} rk_aiq_isp_t;

typedef struct {
    int  model_idx;
    bool valid;
    char media_dev_path[DEV_PATH_LEN];
    char pp_input_image_path[DEV_PATH_LEN];
    char pp_m_bypass_path[DEV_PATH_LEN];
    char pp_scale0_path[DEV_PATH_LEN];
    char pp_scale1_path[DEV_PATH_LEN];
    char pp_scale2_path[DEV_PATH_LEN];
#if defined(ISP_HW_V20)
    char pp_input_params_path[DEV_PATH_LEN];
    char pp_stats_path[DEV_PATH_LEN];
    char pp_tnr_params_path[DEV_PATH_LEN];
    char pp_tnr_stats_path[DEV_PATH_LEN];
    char pp_nr_params_path[DEV_PATH_LEN];
    char pp_nr_stats_path[DEV_PATH_LEN];
#endif
    char pp_fec_params_path[DEV_PATH_LEN];
    char pp_dev_path[DEV_PATH_LEN];
} rk_aiq_ispp_t;

typedef struct {
    int isp_ver;
    int awb_ver;
    int aec_ver;
    int afc_ver;
    int ahdr_ver;
    int blc_ver;
    int dpcc_ver;
    int anr_ver;
    int debayer_ver;
    int lsc_ver;
    int ccm_ver;
    int gamma_ver;
    int gic_ver;
    int sharp_ver;
    int dehaze_ver;
} rk_aiq_hw_ver_t;

typedef struct {
    rk_aiq_isp_t isp_info[MAX_CAM_NUM];
    rk_aiq_ispp_t ispp_info[MAX_CAM_NUM];
    rk_aiq_hw_ver_t hw_ver_info;
} rk_aiq_isp_hw_info_t;

typedef struct {
    int  model_idx;
    char media_dev_path[DEV_PATH_LEN];
    char mipi_id0[DEV_PATH_LEN];
    char mipi_id1[DEV_PATH_LEN];
    char mipi_id2[DEV_PATH_LEN];
    char mipi_id3[DEV_PATH_LEN];
    char mipi_scl0[DEV_PATH_LEN];
    char mipi_scl1[DEV_PATH_LEN];
    char mipi_scl2[DEV_PATH_LEN];
    char mipi_scl3[DEV_PATH_LEN];
    char dvp_id0[DEV_PATH_LEN];
    char dvp_id1[DEV_PATH_LEN];
    char dvp_id2[DEV_PATH_LEN];
    char dvp_id3[DEV_PATH_LEN];
    char mipi_dphy_rx_path[DEV_PATH_LEN];
    char mipi_csi2_sd_path[DEV_PATH_LEN];
    char lvds_sd_path[DEV_PATH_LEN];
    char mipi_luma_path[DEV_PATH_LEN];
    char stream_cif_path[DEV_PATH_LEN];
    char dvp_sof_sd_path[DEV_PATH_LEN];
    char model_str[DEV_PATH_LEN];
} rk_aiq_cif_info_t;

typedef struct {
    rk_aiq_cif_info_t cif_info[MAX_CAM_NUM];
    rk_aiq_hw_ver_t hw_ver_info;
} rk_aiq_cif_hw_info_t;

typedef struct {
    char sns_name[32];
    PdafSensorType_t pdaf_type;
    bool pdaf_support;
    uint32_t pdaf_vc;
    uint32_t pdaf_width;
    uint32_t pdaf_height;
    uint32_t pdaf_pixelformat;
    uint32_t pdaf_code;
    uint8_t pdaf_lrdiffline;
    char pdaf_vdev[DEV_PATH_LEN];
} rk_sensor_pdaf_info_t;

typedef struct {
    /* sensor entity name format:
     * m01_b_ov13850 1-0010, where 'm01' means module index number
     * 'b' meansback or front, 'ov13850' is real sensor name
     * '1-0010' means the i2c bus and sensor i2c slave address
     */
    std::string sensor_name;
    std::string device_name;
    std::string len_name;
    std::string parent_media_dev;
    int media_node_index;
    int csi_port;
    std::string module_lens_dev_name; // matched using mPhyModuleIndex
    std::string module_ircut_dev_name;
    int flash_num;
    std::string module_flash_dev_name[SENSOR_ATTACHED_FLASH_MAX_NUM]; // matched using mPhyModuleIndex
    bool fl_strth_adj_sup;
    int flash_ir_num;
    std::string module_flash_ir_dev_name[SENSOR_ATTACHED_FLASH_MAX_NUM];
    bool fl_ir_strth_adj_sup;
    std::string module_real_sensor_name; //parsed frome sensor entity name
    std::string module_index_str; // parsed from sensor entity name
    char phy_module_orient; // parsed from sensor entity name
    std::vector<rk_frame_fmt_t>  frame_size;
    rk_aiq_isp_t* isp_info;
    rk_aiq_cif_info_t* cif_info;
    rk_aiq_ispp_t* ispp_info;
    bool linked_to_isp;
    bool linked_to_1608;
    bool linked_to_serdes;
    bool dvp_itf;
    struct rkmodule_inf mod_info;
} rk_sensor_full_info_t;

typedef void (*ref_t)(void* ops_ctx, void* cfg);
typedef void (*unref_t)(void* ops_ctx, void* cfg);
typedef struct rk_aiq_share_ptr_ops_s {
    ref_t ref;
    unref_t unref;
} rk_aiq_share_ptr_ops_t;

typedef struct rk_aiq_share_ptr_config_s {
    RkAiqAlgoType_t algo_type;
    uint32_t frame_id;
} rk_aiq_share_ptr_config_t;


class RkAiqAecStats : public XCam::BufferData {
public:
    explicit RkAiqAecStats() {
        xcam_mem_clear(aec_stats);
        xcam_mem_clear(aec_stats_v25);
        aec_stats_valid = false;
        frame_id = -1;
        af_prior = 0;
    };
    virtual ~RkAiqAecStats() {};
    union {
        rk_aiq_isp_aec_stats_t aec_stats;
        RKAiqAecStatsV25_t     aec_stats_v25;
    };
    bool aec_stats_valid;
    bool af_prior;
    uint32_t frame_id;
private:
    XCAM_DEAD_COPY(RkAiqAecStats);
};

class RkAiqAwbStats : public XCam::BufferData {
public:
    explicit RkAiqAwbStats() {
        xcam_mem_clear(awb_stats);
        xcam_mem_clear(awb_stats_v201);
        xcam_mem_clear(awb_stats_v3x);
        xcam_mem_clear(blc_cfg_effect);
        awb_stats_valid = false;
        awb_cfg_effect_valid = false;
        frame_id = -1;
    };
    virtual ~RkAiqAwbStats() {};
    union {
        rk_aiq_awb_stat_res_v200_t awb_stats;
        rk_aiq_awb_stat_res_v201_t awb_stats_v201;
        rk_aiq_isp_awb_stats_v3x_t awb_stats_v3x;
        rk_aiq_isp_awb_stats_v32_t awb_stats_v32;
        awbStats_stats_priv_t awb_stats_v39;
    };
    bool awb_stats_valid;
    bool awb_cfg_effect_valid;
    uint32_t frame_id;
    rk_aiq_isp_blc_t blc_cfg_effect;
private:
    XCAM_DEAD_COPY(RkAiqAwbStats);
};

class RkAiqAtmoStats : public XCam::BufferData {
public:
    explicit RkAiqAtmoStats() {
        xcam_mem_clear(atmo_stats);
        atmo_stats_valid = false;
        frame_id = -1;
    };
    virtual ~RkAiqAtmoStats() {};
    rkisp_atmo_stats_t atmo_stats;
    bool atmo_stats_valid;
    uint32_t frame_id;
private:
    XCAM_DEAD_COPY(RkAiqAtmoStats);
};

class RkAiqAdehazeStats : public XCam::BufferData {
public:
    explicit RkAiqAdehazeStats() {
        xcam_mem_clear(adehaze_stats);
        adehaze_stats_valid = false;
        frame_id = -1;
    };
    virtual ~RkAiqAdehazeStats() {};
    rkisp_adehaze_stats_t adehaze_stats;
    bool adehaze_stats_valid;
    uint32_t frame_id;
private:
    XCAM_DEAD_COPY(RkAiqAdehazeStats);
};

class RkAiqAgainStats : public XCam::BufferData {
public:
    explicit RkAiqAgainStats() {
        xcam_mem_clear(again_stats);
        again_stats_valid = false;
        frame_id = -1;
    };

    rk_aiq_again_stat_t again_stats;
    bool again_stats_valid;
    uint32_t frame_id;
private:
    XCAM_DEAD_COPY(RkAiqAgainStats);
};

class RkAiqAfStats : public XCam::BufferData {
public:
    explicit RkAiqAfStats() {
        xcam_mem_clear(af_stats);
        xcam_mem_clear(af_stats_v3x);
#ifdef USE_NEWSTRUCT
        xcam_mem_clear(afStats_stats);
#endif
        xcam_mem_clear(stat_motor);
        xcam_mem_clear(aecExpInfo);
        af_stats_valid = false;
        frame_id = -1;
    };
    virtual ~RkAiqAfStats() {};
    union {
        rk_aiq_isp_af_stats_t af_stats;
        rk_aiq_isp_af_stats_v3x_t af_stats_v3x;
#ifdef USE_NEWSTRUCT
        afStats_stats_t afStats_stats;
#endif
    };
    rk_aiq_af_algo_motor_stat_t stat_motor;
    RKAiqAecExpInfo_t aecExpInfo;
    bool af_stats_valid;
    uint32_t frame_id;
private:
    XCAM_DEAD_COPY(RkAiqAfStats);
};

class RkAiqOrbStats : public XCam::BufferData {
public:
    explicit RkAiqOrbStats() {
        xcam_mem_clear(orb_stats);
        orb_stats_valid = false;
        frame_id = -1;
        orb_stats.frame_id = -1;
        orb_stats.img_buf_index = -1;
    };
    virtual ~RkAiqOrbStats() {};
    rk_aiq_isp_orb_stats_t orb_stats;
    bool orb_stats_valid;
    uint32_t frame_id;
private:
    XCAM_DEAD_COPY(RkAiqOrbStats);
};

class RkAiqPdafStats : public XCam::BufferData {
public:
    explicit RkAiqPdafStats() {
        xcam_mem_clear(pdaf_stats);
        pdaf_stats_valid = false;
        frame_id = -1;
    };
    virtual ~RkAiqPdafStats() {};
    rk_aiq_isp_pdaf_stats_t pdaf_stats;
    bool pdaf_stats_valid;
    uint32_t frame_id;
private:
    XCAM_DEAD_COPY(RkAiqPdafStats);
};

typedef struct rk_aiq_scale_raw_info_s {
    uint8_t             bpp;
    XCamVideoBuffer* raw_s;
    XCamVideoBuffer* raw_m;
    XCamVideoBuffer* raw_l;
} rk_aiq_scale_raw_info_t;

typedef struct RkAiqVicapRawBufInfo_s {
    uint32_t frame_id;
    bool ready;
    uint8_t flags;
    int bpp;
    SmartPtr<VideoBuffer> raw_s;
    SmartPtr<VideoBuffer> raw_m;
    SmartPtr<VideoBuffer> raw_l;
    void reset() {
        frame_id = -1;
        ready = false;
        flags = 0;
        bpp = 0;
        if (raw_s.ptr())
            raw_s.release();
        if (raw_m.ptr())
            raw_m.release();
        if (raw_l.ptr())
            raw_l.release();
    }
} RkAiqVicapRawBufInfo_t;

typedef struct RkAiqVicapRawBuf_s : public BufferData {
    RkAiqVicapRawBufInfo_t info;
    virtual uint8_t* map() override {
        return (uint8_t*)(&info);
    }
    RkAiqVicapRawBuf_s() {
        info.reset();
    }
    ~RkAiqVicapRawBuf_s() {
        info.reset();
    }
} RkAiqVicapRawBuf_t;

typedef enum RkAiqVicapRawBufFlag_e {
    RK_AIQ_VICAP_SCALE_HDR_MODE_NORMAL = 0x1,
    RK_AIQ_VICAP_SCALE_HDR_MODE_2_HDR = 0x3,
    RK_AIQ_VICAP_SCALE_HDR_MODE_3_HDR = 0x7,
} RkAiqVicapRawBufFlag_t;

enum rk_aiq_core_analyze_type_e {
    RK_AIQ_CORE_ANALYZE_MEAS,
    RK_AIQ_CORE_ANALYZE_OTHER,
    RK_AIQ_CORE_ANALYZE_AMD,
    RK_AIQ_CORE_ANALYZE_THUMBNAILS,
    RK_AIQ_CORE_ANALYZE_LSC,
    RK_AIQ_CORE_ANALYZE_AE,
    RK_AIQ_CORE_ANALYZE_AMFNR,
    RK_AIQ_CORE_ANALYZE_AYNR,
    RK_AIQ_CORE_ANALYZE_AWB,
    RK_AIQ_CORE_ANALYZE_DHAZ,
    RK_AIQ_CORE_ANALYZE_GRP0,
    RK_AIQ_CORE_ANALYZE_GRP1,
    RK_AIQ_CORE_ANALYZE_AF,
    RK_AIQ_CORE_ANALYZE_EIS,
    RK_AIQ_CORE_ANALYZE_ORB,
    RK_AIQ_CORE_ANALYZE_AFD,
    RK_AIQ_CORE_ANALYZE_MAX,
    RK_AIQ_CORE_ANALYZE_ALL = 0xffffffff,
};

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif
static const char* AnalyzerGroupType2Str[32] = {
    [RK_AIQ_CORE_ANALYZE_MEAS] = "GRP_MEAS", [RK_AIQ_CORE_ANALYZE_OTHER] = "GRP_OTHER",
    [RK_AIQ_CORE_ANALYZE_AMD] = "GRP_AMD", [RK_AIQ_CORE_ANALYZE_THUMBNAILS] = "GRP_THUMBNAILS",
    [RK_AIQ_CORE_ANALYZE_LSC] = "GRP_LSC", [RK_AIQ_CORE_ANALYZE_AE] = "GRP_AE",
    [RK_AIQ_CORE_ANALYZE_AMFNR] = "GRP_AMFNR", [RK_AIQ_CORE_ANALYZE_AYNR] = "GRP_AYNR",
    [RK_AIQ_CORE_ANALYZE_AWB] = "GRP_AWB", [RK_AIQ_CORE_ANALYZE_DHAZ] = "DHAZ",
    [RK_AIQ_CORE_ANALYZE_GRP0] = "GRP0", [RK_AIQ_CORE_ANALYZE_GRP1] = "GRP1",
    [RK_AIQ_CORE_ANALYZE_AF] = "AF", [RK_AIQ_CORE_ANALYZE_EIS] = "EIS",
    [RK_AIQ_CORE_ANALYZE_ORB] = "ORB", [RK_AIQ_CORE_ANALYZE_AFD] = "AFD",
};
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

typedef enum _RkAiqSharedDataType {
    RK_AIQ_SHARED_TYPE_INVALID,
    RK_AIQ_SHARED_TYPE_SOF_INFO,
    RK_AIQ_SHARED_TYPE_3A_STATS,
    RK_AIQ_SHARED_TYPE_AEC_STATS,
    RK_AIQ_SHARED_TYPE_ORB_STATS,
} RkAiqSharedDataType;

typedef struct _RkAiqBay3dStat {
    bool is_valid;

    uint32_t frame_id;
    struct isp39_bay3d_stat stat;
} RkAiqBay3dStat;

typedef enum _RkAiqIspUnitedMode {
    RK_AIQ_ISP_UNITE_MODE_NORMAL = 0,
    RK_AIQ_ISP_UNITE_MODE_TWO_GRID,
    RK_AIQ_ISP_UNITE_MODE_FOUR_GRID,
} RkAiqIspUniteMode;

#if defined(ISP_HW_V32_LITE)
#define RK_AIQ_ISP_CIF_INPUT_MAX_SIZE 4224 * 3136
#elif defined(ISP_HW_V32)
#define RK_AIQ_ISP_CIF_INPUT_MAX_SIZE 3072 * 1728
#elif defined(ISP_HW_V30)
#define RK_AIQ_ISP_CIF_INPUT_MAX_SIZE 3840 * 2160
#else
#define RK_AIQ_ISP_CIF_INPUT_MAX_SIZE 3840 * 2160
#endif

typedef struct _RkAiqTbInfo_s {
    bool is_fastboot;
} RkAiqTbInfo_t;

#endif
