/*
 * Display currently using GPIO and constantly redrawing the image
 * This is done this way because I'm hoping that the other parts
 * of the alarm clock will be set up with timers and shouldn't need
 * constant attnetion. I'll need to check how quickly the display has
 * to be refreshed to look good.
 */
#include <time.h>
#include "display.h"

void setup_gpio (void) {
    // initially using gpioc because it doesn't have a handy table of alternate functions
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    // set pins 0-12 for output
    for (int i = 0; i < 13; i++) {
        GPIOC->MODER &= ~(0b11 << (i * 2));
        GPIOC->MODER |= 0b01 << (i * 2);
    }
}

// initially just using PC 0-12
// these can be different, this is just for testing currently
/*
 * bit:     12  11  10  9   8   7   6   5   4   3   2   1   0
 * purpose: OE  CLK LAT SE3 SE2 SE1 SE0 R2  G2  B2  R1  G1  B1
 */
/*
 * 1. Begin with OE, CLK, and LAT low.
 * 2. Initialize a private row counter N to 0.
 * 3. Set R1,G1,B1 to the desired color for row N, column 0.
 * 4. Set R2,G2,B2 to the desired color for row HEIGHT/2+N, column 0.
 * 5. Set CLK high, then low, to shift in the color bit.
 * 6. Repeat steps 3-5 WIDTH times for the remaining columns.
 * 7. Set OE high to disable the LEDs.
 * 8. Set LAT high, then low, to load the shift register contents into the LED outputs.
 * 9. Set ABC (or ABCD) to the current row number N.
 * 10. Set OE low to re-enable the LEDs.
 * 11. Increment the row counter N.
 * 12. Repeat steps 3-11 HEIGHT/2 times for the remaining rows.
 */

void draw (void) {
    GPIOC->BRR = (0b111111111111); // set all output pins to 0
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            GPIOC->BRR = 0b111111;      // clear all color data before setting new color values
            GPIOC->BSRR = image[i][j];

            GPIOC->BSRR = 1<<CLK;
            nanosleep(5000);
            GPIOC->BRR = 1<<CLK;
            nanosleep(5000);
        }
        // this may need some delay so the display actually has time to latch
        GPIOC->BSRR = 1<<OE;
        GPIOC->BSRR = 1<<LAT;
        GPIOC->BRR = 0b1111<<SE0;
        GPIOC->BSRR = (i<<SE0);
        GPIOC->BRR = 1<<LAT;
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