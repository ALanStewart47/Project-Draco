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

void RGB_init(void) {
  fpioa_set_function(38, FUNC_GPIO1);
  fpioa_set_function(39, FUNC_GPIO2);
  fpioa_set_function(40, FUNC_GPIO3);

  gpio_init();

  gpio_set_drive_mode(1, GPIO_DM_OUTPUT);
  gpio_set_drive_mode(2, GPIO_DM_OUTPUT);
  gpio_set_drive_mode(3, GPIO_DM_OUTPUT);
}

int main(void) {
  RGB_init();
  for (uint8_t i = 1; i < 4; i++) {
    gpio_set_pin(i, GPIO_PV_HIGH);
  }
  while (1) {
    for (int i = 1; i < 4; i++) {
      gpio_set_pin(i, GPIO_PV_LOW);
      sleep(1);
      gpio_set_pin(i, GPIO_PV_HIGH);
      sleep(1);
    }
  }
  return 0;
}
