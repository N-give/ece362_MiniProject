#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "rtc.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define FAIL -1
#define SUCCESS 0
#define WR 0
#define RD 1


void I2C1_waitidle(void);
void init_I2C1();
void I2C1_start(uint8_t addr, uint32_t dir);
void I2C1_stop();
int I2C1_senddata(uint8_t* data, uint32_t size);
int I2C1_readdata(uint8_t* data, uint32_t size);
void read_time(uint8_t *);
void set_time(uint8_t *);
void init_DS3231();
void set_date(uint8_t *);
void read_date(uint8_t *);

/*
inline uint8_t dec_to_bcd(uint8_t dec) {
  return ((((dec / 10) & 0xF) << 4) |
           ((dec % 10) & 0xF));
}
*/

inline uint8_t bcd_to_dec(uint8_t bcd){
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}
