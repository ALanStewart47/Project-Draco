#ifndef _FACE_DVP_H
#define _FACE_DVP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dvp.h"
#include "gc0308.h"

typedef enum {
  NirCameraChan = 0,
  RgbCameraChan = 1,
  InvalidCameraChan
} camera_chan_t;

#define DVP_CAM_WIDTH (320)
#define DVP_CAM_HEIGHT (240)

extern volatile uint8_t g_dvp_finish_flag;

// extern uint32_t g_lcd_gram0[38400];
// extern uint8_t g_ai_buf[320 * 240 * 3];

void camera_init(void);
void camera_clear(void);

uint32_t* camera_get_disp_buf(camera_chan_t camera_chan);
uint8_t camera_get_finish_flag(void);
void camera_clear_finish_flag(void);

#endif /* _FACE_DVP_H */
