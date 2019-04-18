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

// #ifndef DISPLAY
#include "i2c.h"
#include "display.h"
#include "stdlib.h"
// #include "rtc.h"
// #endif

// #include "display.c"

int cnt = 0;
int redraw = 0;
uint8_t global_time[3] = {0,0,0};

int main (void) {
	uint8_t local_time[3] = {0,0,0};

  init_I2C1();
  setup_gpio();
  // init_DS3231();

  // for(;;){
  //   clear_swirl();
  //   set_swirl();
  // }
  // clear_diamond();
  // clear_swirl();
  // display_dash();
  // display_number(1, 0, 0);

  // for(int i= 0; i<1000; i++);

  // set_time();

  set_time();
  // for(int i= 0; i<1000; i++);
  read_time(global_time);
  set_display_time(global_time[2], global_time[1]);

  // test();

  display_colon();
  draw();
  // set_display_time(local_time[2], local_time[1]);
  // display5_character('A', 0, 0);

  for (;;) {
    if (redraw) {

      // for(int j = 0; j<3; j++){
      //   local_time[j] = global_time[j];
      // }
      set_display_time(global_time[2], global_time[1]);
      redraw = 0;
    }
    draw();
    // display_character('S', 0, 0);
    // display_character('E', 0, 15);
    // display_character('T', 0, 30);

    // display_character('T', 16, 0);
    // display_character('I', 16, 15);
    // display_character('M', 16, 30);
    // display_character('E', 16, 45);

    // draw();
  }
}


void EXTI4_15_IRQHandler() {
  cnt++;
  // display_character('A', 0, 0);
  if (cnt == 32000) {
    cnt = 0;
    read_time(global_time);
    // display_character('A', 0, 0);
    // uint8_t * local_time = read_time();
    set_display_time(global_time[2], global_time[1]);
    redraw = 1;
    // draw();
    // free(local_time);
    // draw();
  }
  EXTI->PR |= EXTI_PR_PR4;
}
