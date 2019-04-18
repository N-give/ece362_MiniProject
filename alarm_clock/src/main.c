/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

// #include<time.h>
#include<stdint.h>

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

// #include "i2c.h"
#include "display.h"
#include "stdlib.h"
#include "i2c_test.h"

int cnt = 0;
// int redraw = 0;
uint8_t global_time[3] = {0,0,0};

int main (void) {
  uint8_t local_time[3] = {0,0,0};

  // init_I2C1();

  config_dma();
  init_I2C2();
  setup_gpio();
  // init_DS3231();

  set_time2(global_time, 4);
  read_time2(global_time, 3);
  memcpy(local_time, global_time, 3);
  set_display_time(local_time[2], local_time[1]);

  display_colon();
  draw();

  for (;;) {
    if (global_time[0] != local_time[0] ||
        global_time[1] != local_time[1] ||
        global_time[2] != local_time[2]) {

      // for(int j = 0; j<3; j++){
      //   local_time[j] = global_time[j];
      // }
      memcpy(local_time, global_time, 3);
      set_display_time(local_time[2], local_time[1]);
      // redraw = 0;
    }
    draw();
  }
}


void EXTI4_15_IRQHandler() {
  cnt++;
  // display_character('A', 0, 0);
  if (cnt == 32000) {
    cnt = 0;
    read_time2(global_time, 3);
  }
  EXTI->PR |= EXTI_PR_PR4;
}
