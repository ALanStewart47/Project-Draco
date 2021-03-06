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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ili9341.h"
#include "lcd.h"

#include "board_config.h"
#include "sleep.h"

lcd_ctl_t lcd_ctl;

void lcd_polling_enable(void) { lcd_ctl.mode = 0; }

void lcd_interrupt_enable(void) { lcd_ctl.mode = 1; }

void lcd_ili9341_init(void) {
  uint8_t data = 0;

#if 0
	tft_write_command(ILI9341_PWCTRB);
	data = 0x00;
	tft_write_byte(&data, 1);
	data = 0xc1;
	tft_write_byte(&data, 1);
	data = 0x30;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_TIMCTRA);
	data = 0x85;
	tft_write_byte(&data, 1);
	data = 0x00;
	tft_write_byte(&data, 1);
	data = 0x78;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_PWCTRSEQ);
	data = 0x39;
	tft_write_byte(&data, 1);
	data = 0x2c;
	tft_write_byte(&data, 1);
	data = 0x00;
	tft_write_byte(&data, 1);
	data = 0x34;
	tft_write_byte(&data, 1);
	data = 0x02;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_PUMP);
	data = 0x20;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_TIMCTRB);
	data = 0x00;
	tft_write_byte(&data, 1);
	data = 0x00;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_PWCTR1);
	data = 0x23;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_PWCTR2);
	data = 0x10;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_VMCTR1);
	data = 0x3e;
	tft_write_byte(&data, 1);
	data = 0x28;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_VMCTR2);
	data = 0x86;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_MADCTL);
	data = 0x48;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_FRMCTR1);
	data = 0x00;
	tft_write_byte(&data, 1);
	data = 0x18;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_DFUNCTR);
	data = 0x08;
	tft_write_byte(&data, 1);
	data = 0x82;
	tft_write_byte(&data, 1);
	data = 0x27;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_ENGMCTR);
	data = 0x00;
	tft_write_byte(&data, 1);
#endif

  tft_write_command(ILI9341_GAMMASET);
  data = 0x01;
  tft_write_byte(&data, 1);

#if 0
	tft_write_command(ILI9341_GMCTRP1);
	data = 0x0F;
	tft_write_byte(&data, 1);
	data = 0x31;
	tft_write_byte(&data, 1);
	data = 0x2B;
	tft_write_byte(&data, 1);
	data = 0x0C;
	tft_write_byte(&data, 1);
	data = 0x0E;
	tft_write_byte(&data, 1);
	data = 0x08;
	tft_write_byte(&data, 1);
	data = 0x4E;
	tft_write_byte(&data, 1);
	data = 0xF1;
	tft_write_byte(&data, 1);
	data = 0x37;
	tft_write_byte(&data, 1);
	data = 0x07;
	tft_write_byte(&data, 1);
	data = 0x10;
	tft_write_byte(&data, 1);
	data = 0x03;
	tft_write_byte(&data, 1);
	data = 0x0E;
	tft_write_byte(&data, 1);
	data = 0x09;
	tft_write_byte(&data, 1);
	data = 0x00;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_GMCTRN1);
	data = 0x00;
	tft_write_byte(&data, 1);
	data = 0x0E;
	tft_write_byte(&data, 1);
	data = 0x14;
	tft_write_byte(&data, 1);
	data = 0x03;
	tft_write_byte(&data, 1);
	data = 0x11;
	tft_write_byte(&data, 1);
	data = 0x07;
	tft_write_byte(&data, 1);
	data = 0x31;
	tft_write_byte(&data, 1);
	data = 0xC1;
	tft_write_byte(&data, 1);
	data = 0x48;
	tft_write_byte(&data, 1);
	data = 0x08;
	tft_write_byte(&data, 1);
	data = 0x0F;
	tft_write_byte(&data, 1);
	data = 0x0C;
	tft_write_byte(&data, 1);
	data = 0x31;
	tft_write_byte(&data, 1);
	data = 0x36;
	tft_write_byte(&data, 1);
	data = 0x0F;
	tft_write_byte(&data, 1);

	tft_write_command(ILI9341_SLPOUT);
#endif
}

void lcd_init(void) {
  uint8_t data = 0;

  tft_hard_init();  //???????????????
  /*soft reset*/
  tft_write_command(SOFTWARE_RESET);  //?????????
  usleep(100000);
  /*exit sleep*/
  tft_write_command(SLEEP_OFF);  //????????????
  usleep(100000);
  /*pixel format*/
  tft_write_command(PIXEL_FORMAT_SET);  //????????????
  data = 0x55;
  tft_write_byte(&data, 1);

  lcd_set_direction(DIR_YX_RLUD);  //??????????????????RX-24B8120????????????

  /*display on*/
  tft_write_command(ILI9341_INVON);
  tft_write_command(DISPALY_ON);
  lcd_polling_enable();

  printf("lcd init ok\r\n");
}

void lcd_set_direction(lcd_dir_t dir) {
  // #if BOARD_LICHEEDAN
  // #else
  //     dir |= 0x08;
  // #endif
  lcd_ctl.dir = dir;
  if (dir & DIR_XY_MASK) {
#if (BOARD_KQ_V1D9 == 1)
    lcd_ctl.width = LCD_X_MAX - 1;
    lcd_ctl.height = LCD_Y_MAX - 1;
#else
    lcd_ctl.width = LCD_Y_MAX - 1;
    lcd_ctl.height = LCD_X_MAX - 1;
#endif
  } else {
#if (BOARD_KQ_V1D9 == 1)
    lcd_ctl.width = LCD_Y_MAX - 1;
    lcd_ctl.height = LCD_X_MAX - 1;
#else
    lcd_ctl.width = LCD_X_MAX - 1;
    lcd_ctl.height = LCD_Y_MAX - 1;
#endif
  }

  tft_write_command(MEMORY_ACCESS_CTL);
  tft_write_byte((uint8_t *)&dir, 1);
}

void lcd_set_direction_ex(lcd_dir_t dir) {
  for (int i = 0; i < 3; i++) {
    lcd_set_direction(dir);
    msleep(10);
  }
}

/*????????????*/
void lcd_set_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  uint8_t data[4] = {0};

  data[0] = (uint8_t)(x1 >> 8);
  data[1] = (uint8_t)(x1);
  data[2] = (uint8_t)(x2 >> 8);
  data[3] = (uint8_t)(x2);
  tft_write_command(HORIZONTAL_ADDRESS_SET);
  tft_write_byte(data, 4);

  data[0] = (uint8_t)(y1 >> 8);
  data[1] = (uint8_t)(y1);
  data[2] = (uint8_t)(y2 >> 8);
  data[3] = (uint8_t)(y2);
  tft_write_command(VERTICAL_ADDRESS_SET);
  tft_write_byte(data, 4);

  tft_write_command(MEMORY_WRITE);
}

/*??????*/
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color) {
  // tft_write_half(&color, 1);

  uint32_t data = ((uint32_t)color << 16) | (uint32_t)color;

  lcd_set_area(x, y, x, y);
  tft_fill_data(&data, 2);
}

#if 0 			//????????????ascii0816????????????????????????ASCII0816??????
/*???????????????*/
void lcd_draw_char(uint16_t x, uint16_t y, char c, uint16_t color)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t data = 0;

	for (i = 0; i < 16; i++)
	{
		data = ascii0816[c * 16 + i];
		for (j = 0; j < 8; j++)
		{
			if (data & 0x80)
				lcd_draw_point(x + j, y, color);
			data <<= 1;
		}
		y++;
	}
}

/*????????????*/
void lcd_draw_string(uint16_t x, uint16_t y, char *str, uint16_t color)
{
	while (*str)
	{
		lcd_draw_char(x, y, *str, color);
		str++;
		x += 8;
	}
}

/*????????????*/
void lcd_ram_draw_string(char *str, uint32_t *ptr, uint16_t font_color, uint16_t bg_color)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t data = 0;
	uint8_t *pdata = NULL;
	uint16_t width = 0;
	uint32_t *pixel = NULL;

	width = 4 * strlen(str);
	while (*str)
	{
		pdata = (uint8_t *)&ascii0816[(*str) * 16];
		for (i = 0; i < 16; i++)
		{
			data = *pdata++;
			pixel = ptr + i * width;
			for (j = 0; j < 4; j++)
			{
				switch (data >> 6)
				{
				   case 0:
					   *pixel = ((uint32_t)bg_color << 16) | bg_color;
					   break;
				   case 1:
					   *pixel = ((uint32_t)bg_color << 16) | font_color;
					   break;
				   case 2:
					   *pixel = ((uint32_t)font_color << 16) | bg_color;
					   break;
				   case 3:
					   *pixel = ((uint32_t)font_color << 16) | font_color;
					   break;
				   default:
					   *pixel = 0;
					   break;
				}
				data <<= 2;
				pixel++;
			}
		}
		str++;
		ptr += 4;
	}
}
#endif

/*??????*/
void lcd_clear(uint16_t color) {
  uint32_t data = ((uint32_t)color << 16) | (uint32_t)color;

  lcd_set_area(0, 0, lcd_ctl.width, lcd_ctl.height);
  tft_fill_data(&data, LCD_X_MAX * LCD_Y_MAX / 2);
}

/*????????????*/
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                        uint16_t width, uint16_t color) {
  uint32_t data_buf[640] = {0};
  uint32_t *p = data_buf;
  uint32_t data = color;
  uint32_t index = 0;

  data = (data << 16) | data;
  for (index = 0; index < 160 * width; index++) *p++ = data;

  lcd_set_area(x1, y1, x2, y1 + width - 1);
  tft_write_word(data_buf, ((x2 - x1 + 1) * width + 1) / 2, 0);
  lcd_set_area(x1, y2 - width + 1, x2, y2);
  tft_write_word(data_buf, ((x2 - x1 + 1) * width + 1) / 2, 0);
  lcd_set_area(x1, y1, x1 + width - 1, y2);
  tft_write_word(data_buf, ((y2 - y1 + 1) * width + 1) / 2, 0);
  lcd_set_area(x2 - width + 1, y1, x2, y2);
  tft_write_word(data_buf, ((y2 - y1 + 1) * width + 1) / 2, 0);
}

/*??????????????????*/
void lcd_draw_picture(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,
                      uint32_t *ptr) {
  lcd_set_area(x1, y1, x1 + width - 1, y1 + height - 1);
  tft_write_word(ptr, width * height / 2, lcd_ctl.mode ? 2 : 0);
}

/*??????????????????*/
void lcd_draw_picture_half(uint16_t x1, uint16_t y1, uint16_t width,
                           uint16_t height, uint16_t *ptr) {
  lcd_set_area(x1, y1, x1 + width - 1, y1 + height - 1);
  tft_write_half(ptr, width * height);
}

//??????
// x1,y1:????????????
// x2,y2:????????????
void lcd_drawline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                  uint16_t color) {
  uint16_t t;
  int xerr = 0, yerr = 0, delta_x, delta_y, distance;
  int incx, incy, uRow, uCol;
  delta_x = x2 - x1;  //??????????????????
  delta_y = y2 - y1;
  uRow = x1;
  uCol = y1;
  if (delta_x > 0)
    incx = 1;  //??????????????????
  else if (delta_x == 0)
    incx = 0;  //?????????
  else {
    incx = -1;
    delta_x = -delta_x;
  }
  if (delta_y > 0)
    incy = 1;
  else if (delta_y == 0)
    incy = 0;  //?????????
  else {
    incy = -1;
    delta_y = -delta_y;
  }
  if (delta_x > delta_y)
    distance = delta_x;  //???????????????????????????
  else
    distance = delta_y;
  for (t = 0; t <= distance + 1; t++)  //????????????
  {
    lcd_draw_point(uRow, uCol, color);  //??????
    xerr += delta_x;
    yerr += delta_y;
    if (xerr > distance) {
      xerr -= distance;
      uRow += incx;
    }
    if (yerr > distance) {
      yerr -= distance;
      uCol += incy;
    }
  }
}

//??????????????????????????????????????????
//(x,y):?????????
// r    :??????
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color) {
  int a, b;
  int di;
  a = 0;
  b = r;
  di = 3 - (r << 1);  //?????????????????????????????????
  while (a <= b) {
    lcd_draw_point(x0 + a, y0 - b, color);  // 5
    lcd_draw_point(x0 + b, y0 - a, color);  // 0
    lcd_draw_point(x0 + b, y0 + a, color);  // 4
    lcd_draw_point(x0 + a, y0 + b, color);  // 6
    lcd_draw_point(x0 - a, y0 + b, color);  // 1
    lcd_draw_point(x0 - b, y0 + a, color);
    lcd_draw_point(x0 - a, y0 - b, color);  // 2
    lcd_draw_point(x0 - b, y0 - a, color);  // 7
    a++;
    //??????Bresenham????????????
    if (di < 0)
      di += 4 * a + 6;
    else {
      di += 10 + 4 * (a - b);
      b--;
    }
  }
}
