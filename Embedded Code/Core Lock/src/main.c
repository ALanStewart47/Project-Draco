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
#include <unistd.h>
#include "bsp.h"
#include "sysctl.h"

corelock_t lock;

uint64_t get_time(void) {
  uint64_t v_cycle = read_cycle();  //获取CPU开机至今的时钟数
  return v_cycle * 1000000 /
         sysctl_clock_get_freq(SYSCTL_CLOCK_CPU);  //得出运行的时间
}

int core1_function(void *ctx) {
  uint64_t core = current_coreid();  //获取当前CPU核编号
  printf("Core %ld was Registered \n", core);
  while (1) {
    uint64_t start = get_time();  //获取运行时间
    corelock_lock(&lock);         //
    printf("Core %ld locked\n", core);
    sleep(1);
    corelock_unlock(&lock);
    printf("Core %ld unlocked\n", core);
    uint64_t stop = get_time();
    printf("Core %ld lock time is %ld us\n", core, stop - start);
    usleep(10);
  }
}

int main(void) {
  uint64_t core = current_coreid();  //获取当前CPU核编号
  printf("Core %ld is default!\n", core);
  register_core1(core1_function, NULL);
  while (1) {
    corelock_lock(&lock);
    sleep(1);
    printf("1> Core %ld sleep 1\n", core);
    corelock_lock(&lock);
    sleep(2);
    printf("2> Core %ld sleep 2\n", core);
    printf("2> Core unlock\n");
    corelock_unlock(&lock);
    sleep(1);
    printf("1> Core unlock\n");
    corelock_unlock(&lock);
    usleep(10);
  }
}
