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
#include "display.h"
// #endif

// #include "display.c"

int main (void) {
  char disp = 0;
  setup_gpio();
  for (int i = 0;;i=(i+1)%500){
    if (i == 0) {
      display_number(disp, 32, 0);
      disp = (disp + 1) % 10;
    }
    // display_char('A', 0, 0);
    draw();
  }
}
