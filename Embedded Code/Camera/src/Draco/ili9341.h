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
#ifndef _ST7789_H_
#define _ST7789_H_

#include <stdint.h>

/* clang-format off */
#define NO_OPERATION            0x00
#define SOFTWARE_RESET          0x01
// #define READ_ID                 0x04
#define READ_STATUS             0x09
#define READ_POWER_MODE         0x0A
#define READ_MADCTL             0x0B
#define READ_PIXEL_FORMAT       0x0C
#define READ_IMAGE_FORMAT       0x0D
#define READ_SIGNAL_MODE        0x0E
#define READ_SELT_DIAG_RESULT   0x0F
#define SLEEP_ON                0x10
#define SLEEP_OFF               0x11
#define PARTIAL_DISPALY_ON      0x12
#define NORMAL_DISPALY_ON       0x13
#define INVERSION_DISPALY_OFF   0x20
#define INVERSION_DISPALY_ON    0x21
#define GAMMA_SET               0x26
#define DISPALY_OFF             0x28
#define DISPALY_ON              0x29
#define HORIZONTAL_ADDRESS_SET  0x2A
#define VERTICAL_ADDRESS_SET    0x2B
#define MEMORY_WRITE            0x2C
#define COLOR_SET               0x2D
#define MEMORY_READ             0x2E
#define PARTIAL_AREA            0x30
#define VERTICAL_SCROL_DEFINE   0x33
#define TEAR_EFFECT_LINE_OFF    0x34
#define TEAR_EFFECT_LINE_ON     0x35
#define MEMORY_ACCESS_CTL       0x36
#define VERTICAL_SCROL_S_ADD    0x37
#define IDLE_MODE_OFF           0x38
#define IDLE_MODE_ON            0x39
#define PIXEL_FORMAT_SET        0x3A
#define WRITE_MEMORY_CONTINUE   0x3C
#define READ_MEMORY_CONTINUE    0x3E
#define SET_TEAR_SCANLINE       0x44
#define GET_SCANLINE            0x45
#define WRITE_BRIGHTNESS        0x51
#define READ_BRIGHTNESS         0x52
#define WRITE_CTRL_DISPALY      0x53
#define READ_CTRL_DISPALY       0x54
#define WRITE_BRIGHTNESS_CTL    0x55
#define READ_BRIGHTNESS_CTL     0x56
#define WRITE_MIN_BRIGHTNESS    0x5E
#define READ_MIN_BRIGHTNESS     0x5F
#define READ_ID1                0xDA
#define READ_ID2                0xDB
#define READ_ID3                0xDC
#define RGB_IF_SIGNAL_CTL       0xB0
#define NORMAL_FRAME_CTL        0xB1
#define IDLE_FRAME_CTL          0xB2
#define PARTIAL_FRAME_CTL       0xB3
#define INVERSION_CTL           0xB4
#define BLANK_PORCH_CTL         0xB5
#define DISPALY_FUNCTION_CTL    0xB6
#define ENTRY_MODE_SET          0xB7
#define BACKLIGHT_CTL1          0xB8
#define BACKLIGHT_CTL2          0xB9
#define BACKLIGHT_CTL3          0xBA
#define BACKLIGHT_CTL4          0xBB
#define BACKLIGHT_CTL5          0xBC
#define BACKLIGHT_CTL7          0xBE
#define BACKLIGHT_CTL8          0xBF
#define POWER_CTL1              0xC0
#define POWER_CTL2              0xC1
#define VCOM_CTL1               0xC5
#define VCOM_CTL2               0xC7
#define NV_MEMORY_WRITE         0xD0
#define NV_MEMORY_PROTECT_KEY   0xD1
#define NV_MEMORY_STATUS_READ   0xD2
#define READ_ID4                0xD3
#define POSITIVE_GAMMA_CORRECT  0xE0
#define NEGATIVE_GAMMA_CORRECT  0xE1
#define DIGITAL_GAMMA_CTL1      0xE2
#define DIGITAL_GAMMA_CTL2      0xE3
#define INTERFACE_CTL           0xF6

#define DCX_GPIONUM             (2)
#define RST_GPIONUM             (3)

#define SPI_CHANNEL             0
#define SPI_SLAVE_SELECT        3
/* clang-format on */

#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN  0x10
#define ILI9341_SLPOUT 0x11
#define ILI9341_PTLON  0x12
#define ILI9341_NORON  0x13

#define ILI9341_RDMODE     0x0A
#define ILI9341_RDMADCTL   0x0B
#define ILI9341_RDPIXFMT   0x0C
#define ILI9341_RDIMGFMT   0x0D
#define ILI9341_RDSELFDIAG 0x0F

#define ILI9341_INVOFF   0x20
#define ILI9341_INVON    0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF  0x28
#define ILI9341_DISPON   0x29

#define ILI9341_CASET 0x2A
#define ILI9341_PASET 0x2B
#define ILI9341_RAMWR 0x2C
#define ILI9341_RAMRD 0x2E

#define ILI9341_PTLAR  0x30
#define ILI9341_MADCTL 0x36
#define ILI9341_PIXFMT 0x3A

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6

#define ILI9341_PWCTR1   0xC0
#define ILI9341_PWCTR2   0xC1
#define ILI9341_PWCTR3   0xC2
#define ILI9341_PWCTR4   0xC3
#define ILI9341_PWCTR5   0xC4
#define ILI9341_VMCTR1   0xC5
#define ILI9341_VMCTR2   0xC7
#define ILI9341_PWCTRSEQ 0xCB
#define ILI9341_PWCTRA   0xCD
#define ILI9341_PWCTRB   0xCF

#define ILI9341_RDID1 0xDA
#define ILI9341_RDID2 0xDB
#define ILI9341_RDID3 0xDC
#define ILI9341_RDID4 0xDD

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1
#define ILI9341_DGMCTR1 0xE2
#define ILI9341_DGMCTR2 0xE3
#define ILI9341_TIMCTRA 0xE8
#define ILI9341_TIMCTRB 0xEA

#define ILI9341_ENGMCTR 0xF2
#define ILI9341_INCTR   0xF6
#define ILI9341_PUMP    0xF7

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04


void tft_hard_init(void);
void tft_write_command(uint8_t cmd);
void tft_write_byte(uint8_t *data_buf, uint32_t length);
void tft_write_half(uint16_t *data_buf, uint32_t length);
void tft_write_word(uint32_t *data_buf, uint32_t length, uint32_t flag);
void tft_fill_data(uint32_t *data_buf, uint32_t length);

#endif