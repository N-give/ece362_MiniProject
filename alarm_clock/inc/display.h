#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define OE 12
#define CLK 11
#define LAT 10
#define SE3 9
#define SE2 8
#define SE1 7
#define SE0 6
#define R1 5
#define G1 4
#define B1 3
#define R2 2
#define G2 1
#define B2 0

#define COLS 64
#define ROWS 32 / 2

void setup_gpio(void);
void draw(void);

/*
 * color data stored as follows:
 * bit:     7   6   5   4   3   2   1   0
 * data:    NA  NA  R1  G1  B1  R2  G2  B2
 * init to 0
 */
uint8_t image[ROWS][COLS] = {0};