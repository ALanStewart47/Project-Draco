/*
*Copyright 2018 Canaan Inc.**Licensed under the Apache License,
    Version 2.0(the "License");
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
#include <unistd.h>

#include "fpioa.h"
#include "gpio.h"

void led_init(uint8_t x, uint8_t y) {
  fpioa_set_function(
      x, (FUNC_GPIO0 + y));  //设置30引脚的复用功能为GPIO，并分配为GPIO0
  gpio_init();               //初始化GPIO
  gpio_set_drive_mode(0, GPIO_DM_OUTPUT);  //设置GPIO0的驱动模式为输出
}

int main(void) {
  led_init(30, 0);
  gpio_pin_value_t value = GPIO_PV_HIGH;  // value为枚举变量 ， HIGH为1
  gpio_set_pin(0, value);  //设置GPIO引脚为高电平，即灯灭
  while (1) {
    sleep(1);
    gpio_set_pin(0, value = !value);
  }
  return 0;
}
