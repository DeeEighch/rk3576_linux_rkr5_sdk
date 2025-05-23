#ifndef _RK_AIQ_UAPI_ADEBAYER_INT_H_
#define _RK_AIQ_UAPI_ADEBAYER_INT_H_

#include "xcore/base/xcam_common.h"
#include "algos/rk_aiq_algo_des.h"
#include "algos/adebayer/rk_aiq_types_adebayer_algo_int.h"
//#include "xcam_log.h"

typedef struct rk_aiq_uapi_sync_s rk_aiq_uapi_sync_t;

//auto params, change with iso
typedef struct adebayer_attrib_auto_s {
    uint8_t     sharp_strength[9];
    uint8_t     low_freq_thresh;
    uint8_t     high_freq_thresh;
} adebayer_attrib_auto_t;

typedef AdebayerSeletedParamV1_t adebayer_attrib_manual_t;

typedef struct adebayer_attrib_s {
    rk_aiq_uapi_sync_t          sync;
    rk_aiq_debayer_op_mode_t    mode;

    uint8_t                     enable;
    adebayer_attrib_manual_t    stManual;
    adebayer_attrib_auto_t      stAuto;

} adebayer_attrib_t;

typedef AdebayerSeletedParamV2_t adebayer_attrib_v2_manual_t;
typedef CalibDbV2_Debayer_Tuning_t adebayer_attrib_v2_auto_t;

typedef struct adebayer_v2_attrib_s {
    rk_aiq_uapi_sync_t          sync;
    rk_aiq_debayer_op_mode_t    mode;

    adebayer_attrib_v2_manual_t    stManual;
    adebayer_attrib_v2_auto_t      stAuto;

} adebayer_v2_attrib_t;

typedef AdebayerSeletedParamV2Lite_t adebayer_attrib_v2lite_manual_t;
typedef CalibDbV2_Debayer_Tuning_Lite_t adebayer_attrib_v2lite_auto_t;

typedef struct adebayer_v2lite_attrib_s {
    rk_aiq_uapi_sync_t          sync;
    rk_aiq_debayer_op_mode_t    mode;

    adebayer_attrib_v2lite_manual_t    stManual;
    adebayer_attrib_v2lite_auto_t      stAuto;

} adebayer_v2lite_attrib_t;

typedef AdebayerSeletedParamV3_t adebayer_attrib_v3_manual_t;
typedef CalibDbV2_Debayer_Tuning_V3_t adebayer_attrib_v3_auto_t;

typedef struct adebayer_v3_attrib_s {
    rk_aiq_uapi_sync_t          sync;
    rk_aiq_debayer_op_mode_t    mode;

    adebayer_attrib_v3_manual_t    stManual;
    adebayer_attrib_v3_auto_t      stAuto;

} adebayer_v3_attrib_t;

// need_sync means the implementation should consider
// the thread synchronization
// if called by RkAiqAdebayerHandleInt, the sync has been done
// in framework. And if called by user app directly,
// sync should be done in inner. now we just need implement
// the case of need_sync == false; need_sync is for future usage.

XCamReturn
rk_aiq_uapi_adebayer_SetAttrib
(
    RkAiqAlgoContext* ctx,
    adebayer_attrib_t attr,
    bool need_sync
);

XCamReturn
rk_aiq_uapi_adebayer_GetAttrib
(
    RkAiqAlgoContext*  ctx,
    adebayer_attrib_t* attr
);

XCamReturn
rk_aiq_uapi_adebayer_v2_SetAttrib
(
    RkAiqAlgoContext* ctx,
    adebayer_v2_attrib_t attr,
    bool need_sync
);

XCamReturn
rk_aiq_uapi_adebayer_v2_GetAttrib
(
    RkAiqAlgoContext*  ctx,
    adebayer_v2_attrib_t* attr
);

XCamReturn
rk_aiq_uapi_adebayer_v2lite_SetAttrib
(
    RkAiqAlgoContext* ctx,
    adebayer_v2lite_attrib_t attr,
    bool need_sync
);

XCamReturn
rk_aiq_uapi_adebayer_v2lite_GetAttrib
(
    RkAiqAlgoContext*  ctx,
    adebayer_v2lite_attrib_t* attr
);

XCamReturn
rk_aiq_uapi_adebayer_v3_SetAttrib
(
    RkAiqAlgoContext* ctx,
    adebayer_v3_attrib_t attr,
    bool need_sync
);

XCamReturn
rk_aiq_uapi_adebayer_v3_GetAttrib
(
    RkAiqAlgoContext*  ctx,
    adebayer_v3_attrib_t* attr
);

#endif//_RK_AIQ_UAPI_ADEBAYER_INT_H_
