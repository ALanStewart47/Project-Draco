#include "camera.h"
#include "debug_log.h"
#include "lcd.h"
#include "plic.h"
#include "pwm.h"
#include "syslog.h"

volatile uint8_t g_dvp_finish_flag = 0;

uint32_t g_lcd_gram0[DVP_CAM_WIDTH * DVP_CAM_HEIGHT / 2]
    __attribute__((aligned(256)));
uint8_t g_ai_buf[DVP_CAM_WIDTH * DVP_CAM_HEIGHT * 3]
    __attribute__((aligned(256)));

static int on_irq_camera(void* ctx) {
  if (dvp_get_interrupt(DVP_STS_FRAME_FINISH)) {
    // dvp_clear_interrupt(DVP_STS_FRAME_FINISH);
    dvp_clear_interrupt(DVP_STS_FRAME_START | DVP_STS_FRAME_FINISH);
    g_dvp_finish_flag = 1;
  } else {
    if (g_dvp_finish_flag == 0) {
      dvp_start_convert();
    }
    dvp_clear_interrupt(DVP_STS_FRAME_START);
  }

  return 0;
}

uint32_t* camera_get_disp_buf(camera_chan_t camera_chan) {
  return g_lcd_gram0;
  // printf('%x',g_lcd_gram0);
}

uint8_t camera_get_finish_flag(void) { return g_dvp_finish_flag; }

void camera_clear_finish_flag(void) { g_dvp_finish_flag = 0; }

void camera_init(void) {
  dvp_init(8);
  dvp_set_xclk_rate(24000000);  // default：24000000
  dvp_enable_burst();
  //	dvp_set_output_enable(0, 1);
  dvp_set_output_enable(1, 1);
  dvp_set_image_format(DVP_CFG_RGB_FORMAT);
  dvp_set_image_size(DVP_CAM_WIDTH, DVP_CAM_HEIGHT);

  gc0308_init();
  dvp_set_display_addr((uint32_t)g_lcd_gram0);
  dvp_config_interrupt(DVP_CFG_START_INT_ENABLE | DVP_CFG_FINISH_INT_ENABLE, 0);
  dvp_disable_auto();

  /* DVP interrupt config */
  plic_set_priority(IRQN_DVP_INTERRUPT, 1);
  plic_irq_register(IRQN_DVP_INTERRUPT, on_irq_camera, NULL);
  plic_irq_enable(IRQN_DVP_INTERRUPT);

  printf("dvp init ok\r\n");
}

void camera_clear(void) {
  open_gc0308(RGB_CAM);
  g_dvp_finish_flag = 0;

  dvp_clear_interrupt(DVP_STS_FRAME_START | DVP_STS_FRAME_FINISH);
  dvp_config_interrupt(DVP_CFG_START_INT_ENABLE | DVP_CFG_FINISH_INT_ENABLE, 1);
}
