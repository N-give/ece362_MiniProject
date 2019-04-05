/*
 * Display currently using GPIO and constantly redrawing the image
 * This is done this way because I'm hoping that the other parts
 * of the alarm clock will be set up with timers and shouldn't need
 * constant attnetion. I'll need to check how quickly the display has
 * to be refreshed to look good.
 */
#include "display.h"

void setup_gpio (void) {
    // initially using gpioc because it doesn't have a handy table of alternate functions
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER &= ~GPIO_MODER_MODER8;
    GPIOC->MODER |= GPIO_MODER_MODER8_0;
    GPIOC->MODER &= ~GPIO_MODER_MODER9;
    GPIOC->MODER |= GPIO_MODER_MODER9_0;
}

// initially just using PC 0-12
// these can be different, this is just for testing currently
/*
 * bit:     12  11  10  9   8   7   6   5   4   3   2   1   0
 * purpose: OE  CLK LAT SE3 SE2 SE1 SE0 R2  G2  B2  R1  G1  B1
 */
void draw (void) {
    for (int i = 0; i < ROWS / 2; i++) {
        GPIOC->BSRR = 1<<OE;
        for (int j = 0; j < COLS; j++) {
            GPIOC->ODR = image[i][j];
            GPIOC->ODR |= (j<<SE0) & ((1<<SE0) | (1<<SE1) | (1<<SE2) | (1 << SE3));

            GPIOC->BSRR = 1<<CLK;
            GPIOC->BRR = 1<<CLK;
        }
        GPIOC->BSRR = 1<<LAT;
        GPIOC->BRR = 1<<OE;
    }
}

void set_pixel (int row, int column, int color) {
    if ((row > (ROWS * 2)) || (row < 0)) {
        return;
    }
    if ((column > COLS) || (column < 0)) {
        return;
    }
    if (row >= ROWS) {
        color = color << 3;
        image[row][column] &= ~((1<<R2) | (1<<G2) | (1<<B2));
    } else {
        image[row][column] &= ~((1<<R1) | (1<<G1) | (1<<B1));
    }
    image[row][column] |= color;
}