#ifndef I2C_RTC
#define I2C_RTC

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdarg.h>

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define ADDR_SECONDS 0x00
#define ADDR_MINUTES 0x01
#define ADDR_HOURS   0x02
#define ADDR_DAY     0x03
#define ADDR_DATE    0x04
#define ADDR_MONTH   0x05
#define ADDR_YEAR    0x06
#define ADDR_RTC_I2C 0x68

void init_I2C2();
void config_dma();
void init_I2C2_DMA_trans(uint8_t *, uint8_t);
void start_I2C2(uint8_t, uint32_t, uint8_t);

void init_I2C_DMA_read(uint8_t *, uint8_t);
void receive_data_I2C2(uint8_t *, uint8_t);
void send_data_I2C2(uint8_t *, uint8_t);

void set_time2(uint8_t *, uint8_t);
void read_time2(uint8_t *, uint8_t);

#endif
