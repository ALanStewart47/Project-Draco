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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board_config.h"
#include "bsp.h"
#include "camera.h"
#include "debug_log.h"
#include "display.h"
#include "dmac.h"
#include "dvp.h"
#include "fpioa.h"
#include "gc0308.h"
#include "gpiohs.h"
#include "ili9341.h"
#include "image.h"
#include "lcd.h"
#include "pwm.h"
#include "sleep.h"
#include "sysctl.h"
#include "syslog.h"
#include "timer.h"
#include "uarths.h"

static uint8_t display_camera_buffer[DVP_CAM_WIDTH * DVP_CAM_HEIGHT * 2];

/******************************************************************************
 * (2021/9/9)
 * @brief 初始化IO功能
 *
 * @param void:
 *
 *****************************************************************************/
void io_mux_init(void) {
  // DVP config
  fpioa_set_function(CMOS_PCLK_PIN_NUM, FUNC_CMOS_PCLK);
  fpioa_set_function(CMOS_XCLK_PIN_NUM, FUNC_CMOS_XCLK);
  fpioa_set_function(CMOS_HREF_PIN_NUM, FUNC_CMOS_HREF);
  fpioa_set_function(CMOS_VSYNC_PIN_NUM, FUNC_CMOS_VSYNC);

  fpioa_set_function(
      CMOS_RST_PIN_NUM,
      FUNC_GPIOHS0 + CMOS_RST_FUNC_GPIOHS_NUM);  //摄像头的 reset引脚
  gpiohs_set_drive_mode(CMOS_RST_FUNC_GPIOHS_NUM, GPIO_DM_OUTPUT);
  gpiohs_set_pin(CMOS_RST_FUNC_GPIOHS_NUM, 1);

  fpioa_set_function(CMOS_PWDN_PIN_NUM,
                     FUNC_GPIOHS0 + CMOS_PWDN_FUNC_GPIOHS_NUM);
  gpiohs_set_drive_mode(CMOS_PWDN_FUNC_GPIOHS_NUM, GPIO_DM_OUTPUT);
  gpiohs_set_pin(CMOS_PWDN_FUNC_GPIOHS_NUM, 0);
  //显示屏接口设置
  /* Init SPI IO map and function settings */
  fpioa_set_function(LCD_RST_PIN_NUM, FUNC_GPIOHS0 + LCD_RST_FUNC_GPIOHS_NUM);
  fpioa_set_function(LCD_DCX_PIN_NUM, FUNC_GPIOHS0 + LCD_DCX_FUNC_GPIOHS_NUM);
  fpioa_set_function(LCD_CS_PIN_NUM, FUNC_SPI0_SS3);
  fpioa_set_function(LCD_WR_PIN_NUM, FUNC_SPI0_SCLK);

  fpioa_set_function(LCD_BL_PIN_NUM, FUNC_GPIOHS0 + LCD_BL_FUNC_GPIOHS_NUM);
  gpiohs_set_drive_mode(LCD_BL_FUNC_GPIOHS_NUM, GPIO_DM_OUTPUT);
  gpiohs_set_pin(LCD_BL_FUNC_GPIOHS_NUM, 1);

  //显示屏数据线设置
  sysctl_set_spi0_dvp_data(1);
}

static void io_set_power(void) {
  /* Set dvp and spi pin to 3.3V */
  sysctl_set_power_mode(SYSCTL_POWER_BANK6, SYSCTL_POWER_V33);
  sysctl_set_power_mode(SYSCTL_POWER_BANK7, SYSCTL_POWER_V33);
}

static void check_reboot_reason(void) {
  sysctl_reset_enum_status_t v_reset_status = sysctl_get_reset_status();
  if (v_reset_status == SYSCTL_RESET_STATUS_WDT0) {
    printf("wdt0 reboot!\r\n");
  } else if (v_reset_status == SYSCTL_RESET_STATUS_WDT1) {
    printf("wdt1 reboot!\r\n");
  } else if (v_reset_status == SYSCTL_RESET_STATUS_HARD) {
    printf("hard reboot!\r\n");
  } else if (v_reset_status == SYSCTL_RESET_STATUS_SOFT) {
    printf("soft reboot!\r\n");
  }
}

/******************************************************************************
 * (2021/9/9)
 * @brief 把摄像头数据刷新到屏幕
 *
 * @param void:
 *
 *****************************************************************************/
static void refresh_screen(void) {
  if (1 == camera_get_finish_flag()) {
    camera_clear_finish_flag();
    memcpy(display_camera_buffer, camera_get_disp_buf(RgbCameraChan),
           DVP_CAM_WIDTH * DVP_CAM_HEIGHT * 2);

    uint16_t *lcd_ram_buf = (uint16_t *)lcd_get_ram_buffer();

    copy_image2lcd_ram(display_camera_buffer, lcd_ram_buf);

    lcd_show_camera_image(0, 0, 320, 240, lcd_ram_buf);
  }
}

int main() {
  sysctl_pll_set_freq(SYSCTL_PLL0, 400000000UL);
  sysctl_pll_set_freq(SYSCTL_PLL1, 300000000UL);
  sysctl_pll_set_freq(SYSCTL_PLL2, 45158400UL);
  sysctl_clock_enable(SYSCTL_CLOCK_AI);

  // uarths_init();

  check_reboot_reason();  //检查复位原因

  io_mux_init();  //配置IO口
  io_set_power();

  plic_init();  //初始化中断

  camera_init();
  sysctl_enable_irq();
  camera_clear();

  lcd_init();  //初始化LCD

  lcd_clear(RED);
  msleep(500);
  lcd_clear(GREEN);
  msleep(500);
  lcd_clear(BLUE);
  msleep(500);
  lcd_draw_picture(0, 0, 320, 240, rgb_image);
  msleep(1000);

  while (1) {
    refresh_screen();
  }
}
