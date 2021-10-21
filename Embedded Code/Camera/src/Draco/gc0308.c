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
#include "gc0308.h"
#include "dvp.h"
#include "fpioa.h"
#include "i2c.h"
#include "stdio.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "debug_log.h"
#include "syslog.h"
#include "board_config.h"

#define GC0308_ADDR                     0X42

void gc0308_read_all_reg_setting(uint8_t num);


static const uint8_t gc0308_config[][2] =
{
	{ 0xfe, 0x80 },
	{ 0xfe, 0x01 },
	{ 0x54, 0x22 },
	{ 0xfe, 0x00 },
	{ 0xd2, 0x10 },     // close AEC
	{ 0x22, 0x55 },     // close AWB
	{ 0x5a, 0x56 },
	{ 0x5b, 0x40 },
	{ 0x5c, 0x4a },
	{ 0x22, 0x57 },    // Open AWB
	{ 0x01, 0xfa },
	{ 0x02, 0x70 },
	{ 0x0f, 0x00 },
	{ 0x03, 0x01 },
	{ 0x04, 0x2c },
	{ 0xe2, 0x00 },      //anti-flicker step [11:8]
	{ 0xe3, 0x96 },     //anti-flicker step [7:0]
	{ 0xe4, 0x01 },     //exp level 0  16.67fps
	{ 0xe5, 0xc2 },
	{ 0xe6, 0x02 },     //exp level 1  12.5fps
	{ 0xe7, 0x58 },
	{ 0xe8, 0x02 },     //exp level 2  8.33fps
	{ 0xe9, 0xee },
	{ 0xea, 0x05 },     //exp level 3  4.00fps
	{ 0xeb, 0xdc },
	{ 0x05, 0x00 },
	{ 0x06, 0x00 },
	{ 0x07, 0x00 },
	{ 0x08, 0x00 },
	{ 0x09, 0x01 },
	{ 0x0a, 0xe8 },
	{ 0x0b, 0x02 },
	{ 0x0c, 0x88 },
	{ 0x0d, 0x02 },
	{ 0x0e, 0x02 },
	{ 0x10, 0x22 },
	{ 0x11, 0xfd },
	{ 0x12, 0x2a },
	{ 0x13, 0x00 },
	{ 0x14, 0x10 },
	{ 0x15, 0x0a },
	{ 0x16, 0x05 },
	{ 0x17, 0x01 },
	{ 0x18, 0x44 },
	{ 0x19, 0x44 },
	{ 0x1a, 0x1e },
	{ 0x1b, 0x00 },
	{ 0x1c, 0xc1 },
	{ 0x1d, 0x08 },
	{ 0x1e, 0x60 },
	{ 0x1f, 0x16 },
	{ 0x20, 0xff },
	{ 0x21, 0xf8 },
	{ 0x22, 0x57 },
	{ 0x24, 0xa6 },
	{ 0x25, 0x0f },
//output sync_mode
	{ 0x26, 0x02 },
	{ 0x2f, 0x01 },
	{ 0x30, 0xf7 },
	{ 0x31, 0x50 },
	{ 0x32, 0x00 },
	{ 0x39, 0x04 },
	{ 0x3a, 0x18 },
	{ 0x3b, 0x20 },
	{ 0x3c, 0x00 },
	{ 0x3d, 0x00 },
	{ 0x3e, 0x00 },
	{ 0x3f, 0x00 },
	{ 0x50, 0x12 },//
	{ 0x53, 0x82 },
	{ 0x54, 0x80 },
	{ 0x55, 0x80 },
	{ 0x56, 0x82 },
	{ 0x8b, 0x40 },
	{ 0x8c, 0x40 },
	{ 0x8d, 0x40 },
	{ 0x8e, 0x2e },
	{ 0x8f, 0x2e },
	{ 0x90, 0x2e },
	{ 0x91, 0x3c },
	{ 0x92, 0x50 },
	{ 0x5d, 0x12 },
	{ 0x5e, 0x1a },
	{ 0x5f, 0x24 },
	{ 0x60, 0x07 },
	{ 0x61, 0x15 },
	{ 0x62, 0x08 },
	{ 0x64, 0x03 },
	{ 0x66, 0xe8 },
	{ 0x67, 0x86 },
	{ 0x68, 0xa2 },
	{ 0x69, 0x18 },
	{ 0x6a, 0x0f },
	{ 0x6b, 0x00 },
	{ 0x6c, 0x5f },
	{ 0x6d, 0x8f },
	{ 0x6e, 0x55 },
	{ 0x6f, 0x38 },
	{ 0x70, 0x15 },
	{ 0x71, 0x33 },
	{ 0x72, 0xdc },
	{ 0x73, 0x80 },
	{ 0x74, 0x02 },
	{ 0x75, 0x3f },
	{ 0x76, 0x02 },
	{ 0x77, 0x36 },
	{ 0x78, 0x88 },
	{ 0x79, 0x81 },
	{ 0x7a, 0x81 },
	{ 0x7b, 0x22 },
	{ 0x7c, 0xff },
	{ 0x93, 0x48 },
	{ 0x94, 0x00 },
	{ 0x95, 0x05 },
	{ 0x96, 0xe8 },
	{ 0x97, 0x40 },
	{ 0x98, 0xf0 },
	{ 0xb1, 0x38 },
	{ 0xb2, 0x38 },
	{ 0xbd, 0x38 },
	{ 0xbe, 0x36 },
	{ 0xd0, 0xc9 },
	{ 0xd1, 0x10 },
	{ 0xd2, 0x90 },
	{ 0xd3, 0x80 },
	{ 0xd5, 0xf2 },
	{ 0xd6, 0x16 },
	{ 0xdb, 0x92 },
	{ 0xdc, 0xa5 },
	{ 0xdf, 0x23 },
	{ 0xd9, 0x00 },
	{ 0xda, 0x00 },
	{ 0xe0, 0x09 },
	{ 0xec, 0x20 },
	{ 0xed, 0x04 },
	{ 0xee, 0xa0 },
	{ 0xef, 0x40 },
	{ 0x80, 0x03 },
	{ 0x80, 0x03 },
	{ 0x9F, 0x10 },
	{ 0xA0, 0x20 },
	{ 0xA1, 0x38 },
	{ 0xA2, 0x4E },
	{ 0xA3, 0x63 },
	{ 0xA4, 0x76 },
	{ 0xA5, 0x87 },
	{ 0xA6, 0xA2 },
	{ 0xA7, 0xB8 },
	{ 0xA8, 0xCA },
	{ 0xA9, 0xD8 },
	{ 0xAA, 0xE3 },
	{ 0xAB, 0xEB },
	{ 0xAC, 0xF0 },
	{ 0xAD, 0xF8 },
	{ 0xAE, 0xFD },
	{ 0xAF, 0xFF },
	{ 0xc0, 0x00 },
	{ 0xc1, 0x10 },
	{ 0xc2, 0x1C },
	{ 0xc3, 0x30 },
	{ 0xc4, 0x43 },
	{ 0xc5, 0x54 },
	{ 0xc6, 0x65 },
	{ 0xc7, 0x75 },
	{ 0xc8, 0x93 },
	{ 0xc9, 0xB0 },
	{ 0xca, 0xCB },
	{ 0xcb, 0xE6 },
	{ 0xcc, 0xFF },
	{ 0xf0, 0x02 },
	{ 0xf1, 0x01 },
	{ 0xf2, 0x01 },
	{ 0xf3, 0x30 },
	{ 0xf9, 0x9f },
	{ 0xfa, 0x78 },
	{ 0xfe, 0x01 },
	{ 0x00, 0xf5 },
	{ 0x02, 0x1a },
	{ 0x0a, 0xa0 },
	{ 0x0b, 0x60 },
	{ 0x0c, 0x08 },
	{ 0x0e, 0x4c },
	{ 0x0f, 0x39 },
	{ 0x11, 0x3f },
	{ 0x12, 0x72 },
	{ 0x13, 0x13 },
	{ 0x14, 0x42 },
	{ 0x15, 0x43 },
	{ 0x16, 0xc2 },
	{ 0x17, 0xa8 },
	{ 0x18, 0x18 },
	{ 0x19, 0x40 },
	{ 0x1a, 0xd0 },
	{ 0x1b, 0xf5 },
	{ 0x70, 0x40 },
	{ 0x71, 0x58 },
	{ 0x72, 0x30 },
	{ 0x73, 0x48 },
	{ 0x74, 0x20 },
	{ 0x75, 0x60 },
	{ 0x77, 0x20 },
	{ 0x78, 0x32 },
	{ 0x30, 0x03 },
	{ 0x31, 0x40 },
	{ 0x32, 0xe0 },
	{ 0x33, 0xe0 },
	{ 0x34, 0xe0 },
	{ 0x35, 0xb0 },
	{ 0x36, 0xc0 },
	{ 0x37, 0xc0 },
	{ 0x38, 0x04 },
	{ 0x39, 0x09 },
	{ 0x3a, 0x12 },
	{ 0x3b, 0x1C },
	{ 0x3c, 0x28 },
	{ 0x3d, 0x31 },
	{ 0x3e, 0x44 },
	{ 0x3f, 0x57 },
	{ 0x40, 0x6C },
	{ 0x41, 0x81 },
	{ 0x42, 0x94 },
	{ 0x43, 0xA7 },
	{ 0x44, 0xB8 },
	{ 0x45, 0xD6 },
	{ 0x46, 0xEE },
	{ 0x47, 0x0d },
	{ 0xfe, 0x00 },
	{ 0xd2, 0x90 },    // Open AEC at last.
	{ 0x10, 0x26 },
	{ 0x11, 0x0d },      // fdmodified by mormo 2010/07/06
	{ 0x1a, 0x2a },      // 1emodified by mormo 2010/07/06
	{ 0x1c, 0x49 },  // c1modified by mormo 2010/07/06
	{ 0x1d, 0x9a },  // 08modified by mormo 2010/07/06
	{ 0x1e, 0x61 },  // 60modified by mormo 2010/07/06
	{ 0x3a, 0x20 },
	{ 0x50, 0x14 },      // 10modified by mormo 2010/07/06
	{ 0x53, 0x80 },
	{ 0x56, 0x80 },
	{ 0x8b, 0x20 },  //LSC
	{ 0x8c, 0x20 },
	{ 0x8d, 0x20 },
	{ 0x8e, 0x14 },
	{ 0x8f, 0x10 },
	{ 0x90, 0x14 },
	{ 0x94, 0x02 },
	{ 0x95, 0x07 },
	{ 0x96, 0xe0 },
	{ 0xb1, 0x40 }, // YCPT
	{ 0xb2, 0x40 },
	{ 0xb3, 0x40 },
	{ 0xb6, 0xe0 },
	{ 0xd0, 0xcb }, // AECT  c9modifed by mormo 2010/07/06
	{ 0xd3, 0x48 }, // 80modified by mormor 2010/07/06
	{ 0xf2, 0x02 },
	{ 0xf7, 0x12 },
	{ 0xf8, 0x0a },
	{ 0xfe, 0x01 },
	{ 0x02, 0x20 },
	{ 0x04, 0x10 },
	{ 0x05, 0x08 },
	{ 0x06, 0x20 },
	{ 0x08, 0x0a },
	{ 0x0e, 0x44 },
	{ 0x0f, 0x32 },
	{ 0x10, 0x41 },
	{ 0x11, 0x37 },
	{ 0x12, 0x22 },
	{ 0x13, 0x19 },
	{ 0x14, 0x44 },
	{ 0x15, 0x44 },
	{ 0x19, 0x50 },
	{ 0x1a, 0xd8 },
	{ 0x32, 0x10 },
	{ 0x35, 0x00 },
	{ 0x36, 0x80 },
	{ 0x37, 0x00 },
};

void i2c_master_init(uint8_t num)
{
	fpioa_set_function(CMOS_I2C_SDA2_PIN_NUM, FUNC_I2C1_SDA);
	fpioa_set_function(CMOS_I2C_SCLK_PIN_NUM, FUNC_I2C1_SCLK);

	i2c_init(num, GC0308_ADDR >> 1, 7, 100000);

}

static void gc0308_wr_reg(uint8_t num, uint8_t reg, uint8_t data)
{
	uint8_t buf[2];

	buf[0] = reg & 0xff;
	buf[1] = data;
	i2c_send_data(num, buf, 2);
}

static uint8_t gc0308_rd_reg(uint8_t num, uint8_t reg)
{
	uint8_t reg_buf[1];
	uint8_t data_buf;

	reg_buf[0] = reg & 0xff;
	i2c_recv_data(num, reg_buf, 1, &data_buf, 1);
	return data_buf;
}

#define GC0308_SET_PAGE0(n)     gc0308_wr_reg(n,0xfe,0x00)
#define GC0308_SET_PAGE1(n)     gc0308_wr_reg(n,0xfe,0x01)

void open_gc0308(CAM_TYPE type)
{
	i2c_master_init(1);
	GC0308_SET_PAGE0(1);
	gc0308_wr_reg(1, 0x25, 0x0F); //enable visible light data output
}

int gc0308_read_id(uint8_t num, uint8_t *id)
{
	*id = gc0308_rd_reg(num, 0x00);
	return 0;
}

static void gc0308_AWB_enable(uint8_t num, uint8_t AWB_enable)
{
	uint16_t temp_AWB_reg = 0;
	usleep(1 * 1000);
	i2c_master_init(num);
	usleep(1 * 1000);

	temp_AWB_reg = gc0308_rd_reg(num, 0x22);

	if (AWB_enable == cam_true)
	{
		gc0308_wr_reg(num, 0x22, (temp_AWB_reg | 0x02));
	}
	else
	{
		gc0308_wr_reg(num, 0x22, (temp_AWB_reg & (~0x02)));
	}
}

static void  gc0308_set_AE_mode(uint8_t num, cam_bool_type AE_enable)
{
	uint8_t temp_AE_reg = 0;
	usleep(1 * 1000);
	i2c_master_init(num);
	usleep(1 * 1000);

	temp_AE_reg = gc0308_rd_reg(num, 0xd2);

	if (AE_enable == cam_true)
	{

		gc0308_wr_reg(num, 0xd2, (temp_AE_reg | 0x80));
	}
	else
	{
		gc0308_wr_reg(num, 0xd2, (temp_AE_reg & (~0x80)));
	}

}


/*************************************************************************
 * FUNCTION
 *  GC0308_NightMode
 *
 * DESCRIPTION
 *  This function night mode of GC0308.
 *
 * PARAMETERS
 *  bEnable: KAL_TRUE -> enable night mode, otherwise, disable night mode
 *
 * RETURNS
 *  None
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
/*void gc0308_night_mode(bool enable)
{
	if (enable)
	{

		if(GC0308_MPEG4_encode_mode == KAL_TRUE)
			GC0308_write_cmos_sensor(0xec, 0x00);
		else
			GC0308_write_cmos_sensor(0xec, 0x30);
		GC0308_NIGHT_MODE = KAL_TRUE;
	}
	else
	{
		if(GC0308_MPEG4_encode_mode == KAL_TRUE)
			GC0308_write_cmos_sensor(0xec, 0x00);
		else
			GC0308_write_cmos_sensor(0xec, 0x20);
		GC0308_NIGHT_MODE = KAL_FALSE;
	}
}
*/

/*************************************************************************
* FUNCTION
*   gc0308_gamma_select
*
* DESCRIPTION
*   This function is served for FAE to select the appropriate GAMMA curve.
*
* PARAMETERS
*   num
*   glvl
*
* RETURNS
*   None
*
* GLOBALS AFFECTED
*
*
*************************************************************************/
void gc0308_gamma_select(uint8_t num, GAMMALVL_TYPE glvl)
{
	usleep(1 * 1000);
	i2c_master_init(num);
	usleep(1 * 1000);

	switch (glvl)
	{
	case GammaLvl_01:                            //smallest gamma curve
		gc0308_wr_reg(num, 0x9F, 0x0B);
		gc0308_wr_reg(num, 0xA0, 0x16);
		gc0308_wr_reg(num, 0xA1, 0x29);
		gc0308_wr_reg(num, 0xA2, 0x3C);
		gc0308_wr_reg(num, 0xA3, 0x4F);
		gc0308_wr_reg(num, 0xA4, 0x5F);
		gc0308_wr_reg(num, 0xA5, 0x6F);
		gc0308_wr_reg(num, 0xA6, 0x8A);
		gc0308_wr_reg(num, 0xA7, 0x9F);
		gc0308_wr_reg(num, 0xA8, 0xB4);
		gc0308_wr_reg(num, 0xA9, 0xC6);
		gc0308_wr_reg(num, 0xAA, 0xD3);
		gc0308_wr_reg(num, 0xAB, 0xDD);
		gc0308_wr_reg(num, 0xAC, 0xE5);
		gc0308_wr_reg(num, 0xAD, 0xF1);
		gc0308_wr_reg(num, 0xAE, 0xFA);
		gc0308_wr_reg(num, 0xAF, 0xFF);
		break;

	case GammaLvl_02:
		gc0308_wr_reg(num, 0x9F, 0x0E);
		gc0308_wr_reg(num, 0xA0, 0x1C);
		gc0308_wr_reg(num, 0xA1, 0x34);
		gc0308_wr_reg(num, 0xA2, 0x48);
		gc0308_wr_reg(num, 0xA3, 0x5A);
		gc0308_wr_reg(num, 0xA4, 0x6B);
		gc0308_wr_reg(num, 0xA5, 0x7B);
		gc0308_wr_reg(num, 0xA6, 0x95);
		gc0308_wr_reg(num, 0xA7, 0xAB);
		gc0308_wr_reg(num, 0xA8, 0xBF);
		gc0308_wr_reg(num, 0xA9, 0xCE);
		gc0308_wr_reg(num, 0xAA, 0xD9);
		gc0308_wr_reg(num, 0xAB, 0xE4);
		gc0308_wr_reg(num, 0xAC, 0xEC);
		gc0308_wr_reg(num, 0xAD, 0xF7);
		gc0308_wr_reg(num, 0xAE, 0xFD);
		gc0308_wr_reg(num, 0xAF, 0xFF);
		break;

	case GammaLvl_03:
		gc0308_wr_reg(num, 0x9F, 0x10);
		gc0308_wr_reg(num, 0xA0, 0x20);
		gc0308_wr_reg(num, 0xA1, 0x38);
		gc0308_wr_reg(num, 0xA2, 0x4E);
		gc0308_wr_reg(num, 0xA3, 0x63);
		gc0308_wr_reg(num, 0xA4, 0x76);
		gc0308_wr_reg(num, 0xA5, 0x87);
		gc0308_wr_reg(num, 0xA6, 0xA2);
		gc0308_wr_reg(num, 0xA7, 0xB8);
		gc0308_wr_reg(num, 0xA8, 0xCA);
		gc0308_wr_reg(num, 0xA9, 0xD8);
		gc0308_wr_reg(num, 0xAA, 0xE3);
		gc0308_wr_reg(num, 0xAB, 0xEB);
		gc0308_wr_reg(num, 0xAC, 0xF0);
		gc0308_wr_reg(num, 0xAD, 0xF8);
		gc0308_wr_reg(num, 0xAE, 0xFD);
		gc0308_wr_reg(num, 0xAF, 0xFF);
		break;

	case GammaLvl_04:
		gc0308_wr_reg(num, 0x9F, 0x14);
		gc0308_wr_reg(num, 0xA0, 0x28);
		gc0308_wr_reg(num, 0xA1, 0x44);
		gc0308_wr_reg(num, 0xA2, 0x5D);
		gc0308_wr_reg(num, 0xA3, 0x72);
		gc0308_wr_reg(num, 0xA4, 0x86);
		gc0308_wr_reg(num, 0xA5, 0x95);
		gc0308_wr_reg(num, 0xA6, 0xB1);
		gc0308_wr_reg(num, 0xA7, 0xC6);
		gc0308_wr_reg(num, 0xA8, 0xD5);
		gc0308_wr_reg(num, 0xA9, 0xE1);
		gc0308_wr_reg(num, 0xAA, 0xEA);
		gc0308_wr_reg(num, 0xAB, 0xF1);
		gc0308_wr_reg(num, 0xAC, 0xF5);
		gc0308_wr_reg(num, 0xAD, 0xFB);
		gc0308_wr_reg(num, 0xAE, 0xFE);
		gc0308_wr_reg(num, 0xAF, 0xFF);
		break;

	case GammaLvl_05:                               // largest gamma curve
		gc0308_wr_reg(num, 0x9F, 0x15);
		gc0308_wr_reg(num, 0xA0, 0x2A);
		gc0308_wr_reg(num, 0xA1, 0x4A);
		gc0308_wr_reg(num, 0xA2, 0x67);
		gc0308_wr_reg(num, 0xA3, 0x79);
		gc0308_wr_reg(num, 0xA4, 0x8C);
		gc0308_wr_reg(num, 0xA5, 0x9A);
		gc0308_wr_reg(num, 0xA6, 0xB3);
		gc0308_wr_reg(num, 0xA7, 0xC5);
		gc0308_wr_reg(num, 0xA8, 0xD5);
		gc0308_wr_reg(num, 0xA9, 0xDF);
		gc0308_wr_reg(num, 0xAA, 0xE8);
		gc0308_wr_reg(num, 0xAB, 0xEE);
		gc0308_wr_reg(num, 0xAC, 0xF3);
		gc0308_wr_reg(num, 0xAD, 0xFA);
		gc0308_wr_reg(num, 0xAE, 0xFD);
		gc0308_wr_reg(num, 0xAF, 0xFF);
		break;

	default:
		break;
	}
}

///
/// \brief 设置白平�?
/// \param num
/// \param para
/// \return
///
cam_bool_type gc0308_set_param_wb(uint8_t num, AWB_MODE_TYPE para)
{
	usleep(1 * 1000);
	i2c_master_init(num);
	usleep(1 * 1000);

	switch (para)
	{
	case AWB_MODE_OFF:
		gc0308_AWB_enable(num, false);
		break;

	case AWB_MODE_AUTO: //for AWB can adjust back
		gc0308_wr_reg(num, 0x5a, 0x56);
		gc0308_wr_reg(num, 0x5b, 0x40);
		gc0308_wr_reg(num, 0x5c, 0x4a);
		gc0308_AWB_enable(num, true);
		break;

	case AWB_MODE_CLOUDY_DAYLIGHT: //cloudy
		gc0308_AWB_enable(num, false);
		gc0308_wr_reg(num, 0x5a, 0x8c); //WB_manual_gain
		gc0308_wr_reg(num, 0x5b, 0x50);
		gc0308_wr_reg(num, 0x5c, 0x40);
		break;

	case AWB_MODE_DAYLIGHT: //sunny
		gc0308_AWB_enable(num, false);
		gc0308_wr_reg(num, 0x5a, 0x74);
		gc0308_wr_reg(num, 0x5b, 0x52);
		gc0308_wr_reg(num, 0x5c, 0x40);
		break;

	case AWB_MODE_INCANDESCENT: //office
		gc0308_AWB_enable(num, false);
		gc0308_wr_reg(num, 0x5a, 0x48);
		gc0308_wr_reg(num, 0x5b, 0x40);
		gc0308_wr_reg(num, 0x5c, 0x5c);
		break;

	case AWB_MODE_TUNGSTEN: //home
		gc0308_AWB_enable(num, false);
		gc0308_wr_reg(num, 0x5a, 0x40);
		gc0308_wr_reg(num, 0x5b, 0x54);
		gc0308_wr_reg(num, 0x5c, 0x70);
		break;

	case AWB_MODE_FLUORESCENT:
		gc0308_AWB_enable(num, false);
		gc0308_wr_reg(num, 0x5a, 0x40);
		gc0308_wr_reg(num, 0x5b, 0x54);
		gc0308_wr_reg(num, 0x5c, 0x70);
		break;

	default:
		return cam_false;
	}

	return cam_true;

} /* GC0308_set_param_wb */

cam_bool_type gc0308_set_param_effect(uint8_t num, MEFFECT_MODE_TYPE para)
{
	bool  ret = cam_true;
	usleep(1 * 1000);
	i2c_master_init(num);
	usleep(1 * 1000);

	switch (para)
	{
	case MEFFECT_OFF:
		gc0308_wr_reg(num, 0x23, 0x00);
		gc0308_wr_reg(num, 0x2d, 0x0a);
		gc0308_wr_reg(num, 0x20, 0xff);
		gc0308_wr_reg(num, 0xd2, 0x90);
		gc0308_wr_reg(num, 0x73, 0x00);
		gc0308_wr_reg(num, 0x77, 0x54);

		gc0308_wr_reg(num, 0xb3, 0x40);
		gc0308_wr_reg(num, 0xb4, 0x80);
		gc0308_wr_reg(num, 0xba, 0x00);
		gc0308_wr_reg(num, 0xbb, 0x00);
		break;

	case MEFFECT_SEPIA:
		gc0308_wr_reg(num, 0x23, 0x02);
		gc0308_wr_reg(num, 0x2d, 0x0a); // 0x08
		gc0308_wr_reg(num, 0x20, 0xff);
		gc0308_wr_reg(num, 0xd2, 0x90);
		gc0308_wr_reg(num, 0x73, 0x00);

		gc0308_wr_reg(num, 0xb3, 0x40);
		gc0308_wr_reg(num, 0xb4, 0x80);
		gc0308_wr_reg(num, 0xba, 0xd0);
		gc0308_wr_reg(num, 0xbb, 0x28);
		break;

	case MEFFECT_NEGATIVE:
		gc0308_wr_reg(num, 0x23, 0x01);
		gc0308_wr_reg(num, 0x2d, 0x0a);
		gc0308_wr_reg(num, 0x20, 0xff);
		gc0308_wr_reg(num, 0xd2, 0x90);
		gc0308_wr_reg(num, 0x73, 0x00);

		gc0308_wr_reg(num, 0xb3, 0x40);
		gc0308_wr_reg(num, 0xb4, 0x80);
		gc0308_wr_reg(num, 0xba, 0x00);
		gc0308_wr_reg(num, 0xbb, 0x00);
		break;

	case MEFFECT_SEPIAGREEN:
		gc0308_wr_reg(num, 0x23, 0x02);
		gc0308_wr_reg(num, 0x2d, 0x0a);
		gc0308_wr_reg(num, 0x20, 0xff);
		gc0308_wr_reg(num, 0xd2, 0x90);
		gc0308_wr_reg(num, 0x77, 0x88);

		gc0308_wr_reg(num, 0xb3, 0x40);
		gc0308_wr_reg(num, 0xb4, 0x80);
		gc0308_wr_reg(num, 0xba, 0xc0);
		gc0308_wr_reg(num, 0xbb, 0xc0);
		break;

	case MEFFECT_SEPIABLUE:
		gc0308_wr_reg(num, 0x23, 0x02);
		gc0308_wr_reg(num, 0x2d, 0x0a);
		gc0308_wr_reg(num, 0x20, 0xff);
		gc0308_wr_reg(num, 0xd2, 0x90);
		gc0308_wr_reg(num, 0x73, 0x00);

		gc0308_wr_reg(num, 0xb3, 0x40);
		gc0308_wr_reg(num, 0xb4, 0x80);
		gc0308_wr_reg(num, 0xba, 0x50);
		gc0308_wr_reg(num, 0xbb, 0xe0);
		break;

	case MEFFECT_MONO:
		gc0308_wr_reg(num, 0x23, 0x02);
		gc0308_wr_reg(num, 0x2d, 0x0a);
		gc0308_wr_reg(num, 0x20, 0xff);
		gc0308_wr_reg(num, 0xd2, 0x90);
		gc0308_wr_reg(num, 0x73, 0x00);

		gc0308_wr_reg(num, 0xb3, 0x40);
		gc0308_wr_reg(num, 0xb4, 0x80);
		gc0308_wr_reg(num, 0xba, 0x00);
		gc0308_wr_reg(num, 0xbb, 0x00);
		break;

	default:
		ret = cam_false;
		break;
	}

	return ret;

} /* GC0308_set_param_effect */


cam_bool_type gc0308_set_param_banding(uint8_t num, AE_FLICKER_MODE_TYPE para)
{
	bool  ret = cam_true;
	usleep(1 * 1000);
	i2c_master_init(num);
	usleep(1 * 1000);

	switch (para)
	{
	case AE_FLICKER_MODE_50HZ:
		gc0308_wr_reg(num, 0x01, 0x26);
		gc0308_wr_reg(num, 0x02, 0x98);
		gc0308_wr_reg(num, 0x0f, 0x03);

		gc0308_wr_reg(num, 0xe2, 0x00);     //anti-flicker step [11:8]
		gc0308_wr_reg(num, 0xe3, 0x50);     //anti-flicker step [7:0]

		gc0308_wr_reg(num, 0xe4, 0x02);     //exp level 0  12.5fps
		gc0308_wr_reg(num, 0xe5, 0x80);
		gc0308_wr_reg(num, 0xe6, 0x03);     //exp level 1  10fps
		gc0308_wr_reg(num, 0xe7, 0x20);
		gc0308_wr_reg(num, 0xe8, 0x04);     //exp level 2  7.69fps
		gc0308_wr_reg(num, 0xe9, 0x10);
		gc0308_wr_reg(num, 0xea, 0x06);     //exp level 3  5.00fps
		gc0308_wr_reg(num, 0xeb, 0x40);
		break;

	case AE_FLICKER_MODE_60HZ:
		gc0308_wr_reg(num, 0x01, 0x97);
		gc0308_wr_reg(num, 0x02, 0x84);
		gc0308_wr_reg(num, 0x0f, 0x03);

		gc0308_wr_reg(num, 0xe2, 0x00);     //anti-flicker step [11:8]
		gc0308_wr_reg(num, 0xe3, 0x3e);   //anti-flicker step [7:0]

		gc0308_wr_reg(num, 0xe4, 0x02);   //exp level 0  12.00fps
		gc0308_wr_reg(num, 0xe5, 0x6c);
		gc0308_wr_reg(num, 0xe6, 0x02);   //exp level 1  10.00fps
		gc0308_wr_reg(num, 0xe7, 0xe8);
		gc0308_wr_reg(num, 0xe8, 0x03);   //exp level 2  7.50fps
		gc0308_wr_reg(num, 0xe9, 0xe0);
		gc0308_wr_reg(num, 0xea, 0x05);   //exp level 3  5.00fps
		gc0308_wr_reg(num, 0xeb, 0xd0);
		break;

	default:
		ret = cam_false;
		break;
	}

	return ret;
} /* GC0308_set_param_banding */

///
/// \brief 设置曝光区域
/// \param num
/// \param para
/// \return
///
cam_bool_type gc0308_set_param_exposure(uint8_t num, AE_EV_COMP_TYPE para)
{
	bool  ret = cam_true;

	gc0308_wr_reg(num, 0xd2, 0x00);
	switch (para)
	{
	case AE_EV_COMP_n13:
		gc0308_wr_reg(num, 0xb5, 0xc0);
		gc0308_wr_reg(num, 0xd3, 0x20);
		break;

	case AE_EV_COMP_n10:
		gc0308_wr_reg(num, 0xb5, 0xd0);
		gc0308_wr_reg(num, 0xd3, 0x25);
		break;

	case AE_EV_COMP_n07:
		gc0308_wr_reg(num, 0xb5, 0xe0);
		gc0308_wr_reg(num, 0xd3, 0x28);
		break;

	case AE_EV_COMP_n03:
		gc0308_wr_reg(num, 0xb5, 0xf0);
		gc0308_wr_reg(num, 0xd3, 0x30);
		break;

	case AE_EV_COMP_00:
		gc0308_wr_reg(num, 0xb5, 0x00);
		gc0308_wr_reg(num, 0xd3, 0x38);
		break;

	case AE_EV_COMP_03:
		gc0308_wr_reg(num, 0xb5, 0x10);
		gc0308_wr_reg(num, 0xd3, 0x60);
		break;

	case AE_EV_COMP_07:
		gc0308_wr_reg(num, 0xb5, 0x20);
		gc0308_wr_reg(num, 0xd3, 0x70);
		break;

	case AE_EV_COMP_10:
		gc0308_wr_reg(num, 0xb5, 0x30);
		gc0308_wr_reg(num, 0xd3, 0x80);
		break;

	case AE_EV_COMP_13:
		gc0308_wr_reg(num, 0xb5, 0x40);
		gc0308_wr_reg(num, 0xd3, 0x90);
		break;
	default:
		ret = cam_false;
	}
	gc0308_wr_reg(num, 0xd2, 0xc0);
	return ret;
} /* GC0308_set_param_exposure */


void gc0308_set_test_patternmode(uint8_t num, cam_bool_type enable)
{
 //LOG_I("test carama num:=%d", num);
 //LOG_I("test pattern enable:=%d", enable);

 usleep(1 * 1000);
 i2c_master_init(num);
 usleep(1 * 1000);

 if (enable)
 {
  gc0308_wr_reg(num, 0xfe, 0x00);
  gc0308_wr_reg(num, 0xfa, 0x32);
  gc0308_wr_reg(num, 0x20, 0x08);
  gc0308_wr_reg(num, 0x21, 0x00);
  gc0308_wr_reg(num, 0x22, 0x00);
  gc0308_wr_reg(num, 0xd2, 0x10);
  gc0308_wr_reg(num, 0x15, 0x06);
  gc0308_wr_reg(num, 0xf4, 0xc0);
  gc0308_wr_reg(num, 0xf5, 0x40);
  gc0308_wr_reg(num, 0x5a, 0x40);
  gc0308_wr_reg(num, 0x5b, 0x40);
  gc0308_wr_reg(num, 0x5c, 0x40);
  gc0308_wr_reg(num, 0xb0, 0x40);
  gc0308_wr_reg(num, 0xbd, 0x00);
  gc0308_wr_reg(num, 0x51, 0x40);
  gc0308_wr_reg(num, 0x52, 0x40);
  gc0308_wr_reg(num, 0x03, 0x00);
  gc0308_wr_reg(num, 0x04, 0x00);
  gc0308_wr_reg(num, 0x2e, 0x01);
 }
 else
 {
  gc0308_wr_reg(num, 0xfe, 0x00);
  gc0308_wr_reg(num, 0x2e, 0x00); //test pattern
 }
}


static void gc0308_more_reg_set(CAM_TYPE type)
{

	GC0308_SET_PAGE0(1);

//	gc0308_wr_reg(1, 0x03, 0x00);
//	gc0308_wr_reg(1, 0x04, 0x3f);

//	gc0308_wr_reg(1, 0xb3, 0x35); //contrast
	gc0308_wr_reg(1, 0xd3, 0x60); //target-y value
//	gc0308_gamma_select(1, GammaLvl_01); //gamma GammaLvl_01
//	gc0308_wr_reg(1, 0xd2, 0x00);             //关闭AEC
//	gc0308_wr_reg(1, 0xd2, 0xe0);
//	gc0308_wr_reg(1, 0xd0, 0xea);
//	gc0308_wr_reg(1, 0xd1, 0x10);
	gc0308_wr_reg(1, 0xd2, 0xf0);            //开启AEC
//	gc0308_wr_reg(1, 0x24, 0xA0);

//	gc0308_set_test_patternmode(1,cam_true);

	GC0308_SET_PAGE0(1);
}

int gc0308_init(void)
{
	uint8_t data;
	uint32_t i;
	uint8_t num = 0;
	{
		num = 1;
		i2c_master_init(num);       //初始化IIC
		gc0308_read_id(num, &data);
		printf("gc0308 read id [0x%x]\r\n", data);

		for (i = 0; gc0308_config[i][0]; i++)
		{
			gc0308_wr_reg(num, gc0308_config[i][0], gc0308_config[i][1]);       //配置寄存器
		}

		/* set more rgb-sensor reg */
		gc0308_more_reg_set(RGB_CAM);		//设置摄像头曝光参数，根据实际情况调整
		usleep(1 * 1000);
	}

	printf("sensor init ok\r\n");

	return 0;
}

void gc0308_read_all_reg_setting(uint8_t num)
{
	uint8_t data;
	uint32_t i;
	i2c_master_init(num);
	GC0308_SET_PAGE0(num);

	for (i = 0; gc0308_config[i][0]; i++)
	{
		if (gc0308_config[i][0] == 0xfe && gc0308_config[i][1] == 0x00)
		{
			GC0308_SET_PAGE0(num);
		}

		if (gc0308_config[i][0] == 0xfe && gc0308_config[i][1] == 0x01)
		{
			GC0308_SET_PAGE1(num);
		}

		data = gc0308_rd_reg(num, gc0308_config[i][0]);
	}
}

