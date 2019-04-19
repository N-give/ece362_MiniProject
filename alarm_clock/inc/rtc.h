#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdio.h>
#include <string.h>

#define ADDR_SECONDS 0x00
#define ADDR_MINUTES 0x01
#define ADDR_HOURS   0x02
#define ADDR_DAY     0x03
#define ADDR_DATE    0x04
#define ADDR_MONTH   0x05
#define ADDR_YEAR    0x06
#define ADDR_ALARM2MINS 0x0B

#define ADDR_CONTROL 0x0E
#define ADDR_STATUS  0x0F

#define ADDR_TEMP    0x11

#define ADDR_RTC_I2C 0x68
 //or 0xD0?

struct Time{
    uint8_t secs;
    uint8_t mins;
    uint8_t hours;

};

struct Date{
    uint8_t day;
    uint8_t month;
    uint8_t year;
};
