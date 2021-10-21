/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __GC0308_H__
#define __GC0308_H__

#include <stdint.h>
#include "board_config.h"

typedef enum
{
    AWB_MODE_OFF,
    AWB_MODE_AUTO,
    AWB_MODE_CLOUDY_DAYLIGHT,
    AWB_MODE_DAYLIGHT,
    AWB_MODE_INCANDESCENT,
    AWB_MODE_TUNGSTEN,
    AWB_MODE_FLUORESCENT
} AWB_MODE_TYPE;

typedef enum
{
    MEFFECT_OFF,
    MEFFECT_SEPIA,
    MEFFECT_NEGATIVE,
    MEFFECT_SEPIAGREEN,
    MEFFECT_SEPIABLUE,
    MEFFECT_MONO,
} MEFFECT_MODE_TYPE;

typedef enum
{
    AE_FLICKER_MODE_50HZ,
    AE_FLICKER_MODE_60HZ
} AE_FLICKER_MODE_TYPE;

typedef enum
{
    AE_EV_COMP_n13,
    AE_EV_COMP_n10,
    AE_EV_COMP_n07,
    AE_EV_COMP_n03,
    AE_EV_COMP_00,
    AE_EV_COMP_03,
    AE_EV_COMP_07,
    AE_EV_COMP_10,
    AE_EV_COMP_13
} AE_EV_COMP_TYPE;

typedef enum
{
    GammaLvl_01,
    GammaLvl_02,
    GammaLvl_03,
    GammaLvl_04,
    GammaLvl_05
} GAMMALVL_TYPE;

typedef enum
{
    cam_false,
    cam_true
} cam_bool_type;

typedef enum
{
    NIR_CAM = 0,
    RGB_CAM,
    MAX_CAM
} CAM_TYPE;

void gc0308_gamma_select(uint8_t num, GAMMALVL_TYPE glvl);
cam_bool_type gc0308_set_param_wb(uint8_t num, AWB_MODE_TYPE para);
cam_bool_type gc0308_set_param_effect(uint8_t num, MEFFECT_MODE_TYPE para);
cam_bool_type gc0308_set_param_banding(uint8_t num, AE_FLICKER_MODE_TYPE para);
cam_bool_type gc0308_set_param_exposure(uint8_t num, AE_EV_COMP_TYPE para);
void gc0308_read_all_reg_setting(uint8_t num);

int gc0308_init(void);
void open_gc0308(CAM_TYPE type);

#endif
