/**
  ****************************************************************************** * @file    main.c
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

#include "i2c.h"
#include "display.h"
#include "stdlib.h"
// #include "i2c_test.h"

// TODO make clock states
// enum state {};
// enum state clock_state;
int cnt = 0;
int redraw = 0;
int alarmCount = 0;
uint8_t global_time[3] = {0,0,0};
uint8_t local_time[3] = {1,1,1};
uint8_t trans_time[4] = {
  ADDR_SECONDS,
  ((((35 / 10) & 0xF) << 4) | ((35 % 10) & 0xF)),
  ((((30 / 10) & 0xF) << 4) | ((30 % 10) & 0xF)),
  (((((11 / 10) & 0xF) << 4) | 0x40) |((11 % 10) & 0xF))
};

int main() {
  init_I2C1();
  setup_gpio();
  init_DS3231();

  uint8_t desiredTime[] = {0, 59, 21};
  uint8_t alarm_time[] = {0, 22};
  set_time(desiredTime);
  set_alarm(alarm_time);
  read_time(global_time);
  // memcpy(local_time, global_time, 3);
  set_display_time(local_time[2], local_time[1]);
  // set_display_date(1, 2);
  display_dash();
  display_colon();

  for(;;){
    // redraw = 1;
    if (redraw) {
      display_number(3, 16, 0);
      redraw = 0;
      read_time(global_time);
      memcpy(local_time, global_time, 3);
      set_display_time(local_time[2], local_time[1]);
    }
    draw();
  }
}

// int main (void) {
//   init_I2C1();
// 
//   // config_dma();
//   // init_I2C2();
//   setup_gpio();
//   // setup_tim2();
//   // init_DS3231();
// 
//   // test_dma();
//   // set_time2(trans_time, 4);
//   // read_time2(global_time, 3);
//   // memcpy(local_time, global_time, 3);
//   uint8_t desiredTime[] = {35, 59, 21};
//   set_time(desiredTime);
//   read_time(global_time);
//   memcpy(local_time, global_time, 3);
//   set_display_time(local_time[2], local_time[1]);
// 
//   display_number(8, 16, 0);
//   display_number(9, 16, 15);
//   display_number(6, 16, 34);
//   display_number(7, 16, 49);
//   display_dash();
//   display_colon();
//   draw();
// 
//   for (;;) {
//     // draw_row(0);
//     // draw_row(3);
//     // draw();
//     if (redraw) {
// 
//       // for(int j = 0; j<3; j++){
//       //   local_time[j] = global_time[j];
//       // }
//       // memcpy(local_time, global_time, 3);
//       // read_time(global_time);
//       draw();
//       set_display_time(local_time[2], local_time[1]);
//       draw();
//       // display_number(0, 16, 0);
//       draw();
//       // display_number(4, 16, 15);
//       draw();
//       // display_number(1, 16, 34);
//       draw();
//       // display_number(8, 16, 49);
//       draw();
//       // display_dash();
//       draw();
//       // display_colon();
//       redraw = 0;
//     }
//     draw();
//   }
// }

// TODO set timer to count on edge
void EXTI4_15_IRQHandler() {
  cnt++;
  if (cnt == 32000) {
    // display_number(1, 16, 0);
    cnt = 0;
    redraw = 1;
    // read_time2(global_time, 3);
  }
  EXTI->PR |= EXTI_PR_PR4;
}

void DMA1_Channel4_5_IRQHandler() {
  display_number(1, 16, 45);
  redraw = 1;
  if (DMA1->ISR & DMA_ISR_TCIF4) {
    // display_character('T', 16, 0);
    DMA1->IFCR = DMA_IFCR_CTCIF4;
  } else if (DMA1->ISR & DMA_ISR_TCIF5) {
    // display_number(0, 16, 15);
    DMA1->IFCR = DMA_IFCR_CTCIF5;
  }
}

void TIM2_IRQHandler() {
  TIM2->SR &= ~TIM_SR_UIF;
  display_color++;
  if (display_color == 8) {
    display_color = 1;
  }
  redraw = 1;
  // display_number(3, 16, 34);
}

void EXTI0_1_IRQHandler(void){ //connect square wave ~ 1 kHzfrom alarm enable of rtc to PA0
    EXTI->PR |= EXTI_PR_PR0;
    alarmCount ++; //make a global counter
    if (alarmCount == 1000){
        alarmCount = 0;
        GPIOB->ODR ^= 1; //buzzer connected to PB0
    }
    
}

