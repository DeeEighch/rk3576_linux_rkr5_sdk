/*
 *   Copyright (c) 2024 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 */

#ifndef _AIQ_ISP_ACTIVE_PARAMS_INFO_H_
#define _AIQ_ISP_ACTIVE_PARAMS_INFO_H_

#include "st_string.h"

void active_isp_params_dump_by_type(void* dumper, int type, st_string* result);

#endif  //  _AIQ_ISP_ACTIVE_PARAMS_INFO_H_
