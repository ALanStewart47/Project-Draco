#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "board_config.h"

uint8_t *lcd_get_ram_buffer(void);

void copy_image2lcd_ram(const void *cam_image, void *lcd_ram);
void lcd_show_camera_image(uint16_t x1, uint16_t y1, uint16_t width,
                           uint16_t height, uint32_t *ptr);
void lcd_draw_face_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                        uint16_t color);
void lcd_draw_cn_str_h_center(uint16_t y, const char *cn_str, uint16_t color,
                              uint8_t haveBackColor);

#endif
