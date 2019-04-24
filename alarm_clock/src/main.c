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

int alarm = 0;
int alarmCount = 0;
int increment = 0;
int set = 0;
int pos = 2;
int mode = 0;
uint8_t global_date[2] = {22, 11};
uint8_t local_date[2] = {0, 0};
uint8_t global_time[3] = {55, 59, 23};
uint8_t local_time[3] = {1,1,1};

int main() {
  init_I2C1();
  setup_gpio();
  init_DS3231();
  setup_tim2();
  setup_tim3();

  uint8_t alarm_time[] = {0, 0};
  read_time(global_time);
  memcpy(local_time, global_time, 3);
  set_display_time(local_time[2], local_time[1]);
  read_date(global_date);
  memcpy(local_date, global_date, 2);
  set_display_date(local_date[1], local_date[0], 1);

  display_dash(1);
  display_colon();

  for(;;){
    switch (mode) {
      // set time
      case (1):
        set_display_time(local_time[2], local_time[1]);
        set_display_mode(mode);
        if (increment) {
          increment = 0;
          if (pos == 2) {
            local_time[pos] = (local_time[pos] + 1) % 24;
          } else if (pos == 1) {
            local_time[pos] = (local_time[pos] + 1) % 60;
          }
        }
        if (set) {
          pos--;
          set = 0;
        }
        if (pos == 0) {
          pos = 2;
          mode = 0;
          local_time[0] = 0;
          set_time(local_time);
          clear_display();
          set_display_time(local_time[2], local_time[1]);
          set_display_date(local_date[1], local_date[0], 1);
        }
        break;

      // set date
      case (2):
        // set_display_time(local_time[2], local_time[1]);
        set_display_date(local_date[1], local_date[0], 0);
        set_display_mode(mode);
        if (increment) {
          increment = 0;
          if (pos == 2) {
            local_date[pos - 1] = ((local_date[pos - 1] + 1) % 12);
          } else if (pos == 1) {
            local_date[pos - 1] = ((local_date[pos - 1] + 1) % 30);
          }
        }
        if (set) {
          pos--;
          set = 0;
        }
        if (pos == 0) {
          pos = 2;
          mode = 0;
          set_date(local_date);
          clear_display();
          set_display_time(local_time[2], local_time[1]);
          set_display_date(local_date[1], local_date[0], 1);
        }
        break;

      // set alarm
      case(3):
        // alarm_time[0] = 0;
        // alarm_time[1] = 0;
        set_display_time(alarm_time[1], alarm_time[0]);
        set_display_mode(mode);
        if (increment) {
          increment = 0;
          if (pos == 2) {
            alarm_time[pos - 1] = (alarm_time[pos - 1] + 1) % 24;
          } else if (pos == 1) {
            alarm_time[pos - 1] = (alarm_time[pos - 1] + 1) % 60;
          }
        }
        if (set) {
          pos--;
          set = 0;
        }
        if (pos == 0) {
          pos = 2;
          mode = 0;
          alarm = 1;
          clear_display();
          set_display_time(local_time[2], local_time[1]);
          set_display_date(local_date[1], local_date[0], 1);
        }
        break;


      // choose color
      case (4):
        set_display_time(local_time[1], local_time[0]);
        set_display_mode(mode);
        if (increment) {
          increment = 0;
          display_color++;
          if (display_color == 8) {
            display_color = 1;
          }
        }
        if (set) {
          pos = 0;
          set = 0;
        }
        if (pos == 0) {
          pos = 2;
          mode = 0;
          clear_display();
          set_display_time(local_time[2], local_time[1]);
          set_display_date(local_date[1], local_date[0], 1);
        }
        break;

      case (5):
        clear_display();
        set_display_date(local_date[1], local_date[0], 1);
        mode = 0;

      default:
        read_time(global_time);
        memcpy(local_time, global_time, 3);
        set_display_time(local_time[2], local_time[1]);
        if (local_time[2] == 0 && local_time[1] == 0 && local_time[0] == 0) {
          set_display_date(local_date[1], local_date[0], 1);
          read_date(global_date);
          memcpy(local_date, global_date, 2);
        }
        if (alarm) {
          set_pixel(display_color, 0, 30);
          if (
              alarm_time[1] == local_time[2] &&
              alarm_time[0] == local_time[1]
             ) {
            set_pixel(display_color, 1, 30);
            // TODO enable alarm sound
            // GPIOB->BSRR = 1<<9;
            TIM3->CR1 |= TIM_CR1_CEN;
            if (increment) {
              alarm_time[0] = (alarm_time[0] + 1) % 60;
              set_pixel(0, 1, 30);
              // GPIOB->BRR = 1<<9;
              TIM3->CR1 &= ~TIM_CR1_CEN;
              if (!alarm_time[0]) {
                alarm_time[1] = (alarm_time[1] + 1) % 24;
              }
              increment = 0;
            }
            if (set) {
              alarm = 0;
              set_pixel(0, 0, 30);
              set_pixel(0, 1, 30);
              TIM3->CR1 &= ~TIM_CR1_CEN;
              // GPIOB->BRR = 1<<9;
            }
          }
        }
        if (increment) {
          increment = 0;
        }
        if (set) {
          set = 0;
        }
        if (pos == 0) {
          pos = 2;
        }
        break;
    }
    if (alarm) {
      set_pixel(display_color, 0, 30);
      if (
          alarm_time[1] == local_time[2] &&
          alarm_time[0] == local_time[1]
         ) {
        set_pixel(display_color, 1, 30);
        TIM3->CR1 |= TIM_CR1_CEN;
        // GPIOB->BSRR = 1<<9;
        if (increment) {
          alarm_time[0] = (alarm_time[0] + 1) % 60;
          set_pixel(0, 1, 30);
          TIM3->CR1 &= ~TIM_CR1_CEN;
          // GPIOB->BRR = 1<<9;
          if (!alarm_time[0]) {
            alarm_time[1] = (alarm_time[1] + 1) % 24;
          }
          increment = 0;
        }
      }
    }
    draw();
  }
}

void DMA1_Channel4_5_IRQHandler() {
  display_number(1, 16, 45);
  if (DMA1->ISR & DMA_ISR_TCIF4) {
    // display_character('T', 16, 0);
    DMA1->IFCR = DMA_IFCR_CTCIF4;
  } else if (DMA1->ISR & DMA_ISR_TCIF5) {
    // display_number(0, 16, 15);
    DMA1->IFCR = DMA_IFCR_CTCIF5;
  }
}

void TIM2_IRQHandler() {
  int var __attribute__((unused));

  if (TIM2->SR & TIM_SR_CC4IF) {
    increment = 1;
  }

  if (TIM2->SR & TIM_SR_CC2IF) {
    set = 1;
  }

  if (TIM2->SR & TIM_SR_CC3IF) {
    mode = (mode + 1) % 6;
    // clear_display();
  }

  var = TIM2->CCR2;
  var = TIM2->CCR3;
  var = TIM2->CCR4;
}

void TIM3_IRQHandler () {
  TIM3->SR &= ~TIM_SR_UIF;
  display_color++;
  if (display_color == 8) {
    display_color = 1;
  }
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

