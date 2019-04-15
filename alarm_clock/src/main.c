/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include<time.h>
#include<stdint.h>

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "display.h"
#include "display.c"

int main (void) {
  setup_gpio();
  for (;;){
    draw();
  }
}
