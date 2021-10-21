#include "display.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "debug_log.h"
#include "lcd.h"
#include "sleep.h"
#include "syslog.h"

static uint8_t g_lcd_ram_buffer[LCD_X_MAX * LCD_Y_MAX * 2];
uint8_t *lcd_get_ram_buffer(void) { return g_lcd_ram_buffer; }

#ifdef SUPPORT_UART_STR
dis_str_info_t g_dis_str_info = {0};

void dis_str_show(dis_str_info_t *dis_str_info) {
  if (NULL == dis_str_info) return;

  if (dis_str_info->dis_str.is_show) {
    if (dis_str_info->dis_str.utf8_str) {
      gui_draw_string_middle(dis_str_info->dis_str.x, dis_str_info->dis_str.y,
                             dis_str_info->dis_str.utf8_str,
                             dis_str_info->dis_str.rgb565_color, 0);
    }
  }
}
#endif

#ifdef RR_90_DGREEN
// right rotate 90 degreen, and copy to lcd ram buffer
static void image_rotate_90(const void *inbuf, void *outbuf, bool swap) {
  uint32_t *rgb565_buf_in = (uint32_t *)inbuf;
  uint16_t *rgb565_buf_out = (uint16_t *)outbuf;

  uint16_t *ptr_in = NULL;
  uint16_t *ptr_out_1 = NULL;
  uint16_t *ptr_out_2 = NULL;
  uint16_t temp;

  if (NULL == rgb565_buf_in) return;

  for (int x = 0; x < DVP_CAM_WIDTH / 2; x++) {
    for (int y = 0; y < DVP_CAM_HEIGHT; y++) {
      ptr_in = &rgb565_buf_in[x + DVP_CAM_WIDTH / 2 * (DVP_CAM_HEIGHT - 1 - y)];

      ptr_out_1 = &rgb565_buf_out[(x * 2) * DVP_CAM_HEIGHT];
      ptr_out_2 = &rgb565_buf_out[(x * 2 + 1) * DVP_CAM_HEIGHT];

      ptr_out_1[y] = ptr_in[1];
      ptr_out_2[y] = ptr_in[0];

      //是否交换高低16位
      if (swap) {
        if (y % 2) {
          temp = ptr_out_1[y];
          ptr_out_1[y] = ptr_out_1[y - 1];
          ptr_out_1[y - 1] = temp;

          temp = ptr_out_2[y];
          ptr_out_2[y] = ptr_out_2[y - 1];
          ptr_out_2[y - 1] = temp;
        }
      }
    }
  }
}
#endif

void copy_image2lcd_ram(const void *cam_image, void *lcd_ram) {
  uint16_t *src = (uint16_t *)cam_image;
  uint16_t *des = (uint16_t *)lcd_ram;

#ifdef RR_90_DGREEN
  image_rotate_90(src, des, false);
#else
  memcpy(des, src, LCD_X_MAX * LCD_Y_MAX * 2);
#endif
}

void lcd_show_camera_image(uint16_t x1, uint16_t y1, uint16_t width,
                           uint16_t height, uint32_t *ptr) {
#ifdef SUPPORT_UART_STR
  dis_str_show(&g_dis_str_info);
#endif
#ifdef RR_90_DGREEN
  lcd_show_image(0, 0, LCD_X_MAX, LCD_Y_MAX, ptr);
#else
  if (ptr) lcd_draw_picture(x1, y1, width, height, ptr);
#endif
}
