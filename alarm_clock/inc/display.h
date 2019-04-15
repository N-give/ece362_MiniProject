#ifndef DISPLAY
#define DISPLAY

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdint.h>

#define OE 12
#define CLK 11
#define LAT 10
#define SE3 9
#define SE2 8
#define SE1 7
#define SE0 6
#define R2 5
#define G2 4
#define B2 3
#define R1 2
#define G1 1
#define B1 0

#define COLS 64
#define ROWS 32 / 2

void setup_gpio(void);
void draw(void);
void set_pixel (int, int, uint8_t);
void display_char(char, int, int);

// turns all colors all the way on
uint8_t test_image[ROWS][COLS] = {
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
};

/*
 * //// example half display numbers ////
 * 15 columns x 16 rows
 * - This is so we can fit 4 numbers on the display at once
 * ............... ............... ............... ...............
 * .....00000..... .......00...... ....000000..... ....0000000....
 * ...00.....00... ......000...... ..00......00... ..00.......00..
 * ..00.......00.. .....0000...... .00........00.. .00.........00.
 * .00.........00. ....00.00...... .00........00.. ............00.
 * .00.........00. ...00..00...... ..00.......00.. ..........00...
 * .00.........00. .......00...... ..........00... ........00.....
 * .00.........00. .......00...... .........00.... ......0000.....
 * .00.........00. .......00...... ........00..... ..........00...
 * .00.........00. .......00...... .......00...... ...........00..
 * .00.........00. .......00...... ......00....... ............00.
 * .00.........00. .......00...... .....00........ .00.........00.
 * ..00.......00.. .......00...... ....00......... .00.........00.
 * ...00.....00... .......00...... ...00.......... ...00.....00...
 * .....00000..... ...00000000000. ..000000000000. .....00000.....
 * ............... ............... ............... ...............
 * 
 * ............... ............... ............... ...............
 * ..........00... .000000000000.. .....00000..... .0000000000000.
 * .........000... .00............ ...00.....00... ............00.
 * ........0000... .00............ ..00.......00.. ...........00..
 * .......00.00... .00............ .00............ ..........00...
 * ......00..00... .00............ .00............ .........00....
 * .....00...00... .00..0000000... .00............ ........00.....
 * ....00....00... .00000.....00.. .00...00000.... .......00......
 * ...00.....00... .00.........00. .00.00.....00.. ......00.......
 * ..00......00... ............00. .000........00. ......00.......
 * .0000000000000. ............00. .00.........00. ......00.......
 * ..........00... .00.........00. .00.........00. ......00.......
 * ..........00... .00.........00. .00.........00. ......00.......
 * ..........00... ..00.......00.. ...00......00.. ......00.......
 * .........0000.. ....0000000.... .....000000.... ......00.......
 * ............... ............... ............... ...............
 * 
 * ............... ............... ............... ...............
 * ....0000000.... ....0000000.... ............... ...............
 * ..00.......00.. ..00.......00.. ............... ...............
 * .00.........00. .00.........00. ............... ...............
 * .00.........00. .00.........00. ............... ...............
 * .00.........00. .00.........00. ............... ...............
 * ..00.......00.. .00.........00. ............... ...............
 * ....0000000.... ..00.......000. ............... ...............
 * ..00.......00.. ....0000000.00. ............... ...............
 * .00.........00. ............00. ............... ...............
 * .00.........00. ............00. ............... ...............
 * .00.........00. ............00. ............... ...............
 * .00.........00. ..00.......00.. ............... ...............
 * ..00.......00.. ...00.....00... ............... ...............
 * ....0000000.... .....00000..... ............... ...............
 * ............... ............... ............... ...............
 */

/*
 */

uint8_t half_number_masks[10][16][15] = {
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0}, 
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0}, 
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }
};

/*
 * //// example half display letters ////
 * 15 columns x 16 rows
 * only the ones needed... may expand later
 * - set time
 * - set date
 *   - SETIMDA
 * 
 * ............... ............... ............... ...............
 * ....0000000.... .0000000000000. .0000000000000. .0000000000000.
 * ..00.......00.. .00............ .......0....... .......0.......
 * .00........00.. .00............ .......0....... .......0.......
 * .00........00.. .00............ .......0....... .......0.......
 * ...00.......... .00............ .......0....... .......0.......
 * .....00........ .00............ .......0....... .......0.......
 * .......00...... .00000000...... .......0....... .......0.......
 * .........00.... .00............ .......0....... .......0.......
 * ..........00... .00............ .......0....... .......0.......
 * .00........00.. .00............ .......0....... .......0.......
 * .00.........00. .00............ .......0....... .......0.......
 * .00.........00. .00............ .......0....... .......0.......
 * ..00.......00.. .00............ .......0....... .......0.......
 * ....0000000.... .0000000000000. .......0....... .0000000000000.
 * ............... ............... ............... ...............
 * 
 * ............... ............... ............... ...............
 * .00.........00. .0000000....... .......0....... ......000......
 * .000.......000. .00.....00..... ......000...... ....0000000....
 * .0000.....0000. .00.......00... .....00.00..... ..000.....000..
 * .00.00...00.00. .00........00.. ....00...00.... ..00.......00..
 * .00..00000..00. .00.........00. ....00...00.... ..00.......00..
 * .00...000...00. .00.........00. ...00.....00... ..00.......00..
 * .00.........00. .00.........00. ...00.....00... ..00000000000..
 * .00.........00. .00.........00. ...000000000... .0000000000000.
 * .00.........00. .00.........00. ..00......00... .00.........00.
 * .00.........00. .00.........00. ..00......00... .00.........00.
 * .00.........00. .00.........00. ..00.......00.. .00.........00.
 * .00.........00. .00........00.. .00........00.. .00.........00.
 * .00.........00. .00.......00... .00........00.. .00.........00.
 * .00.........00. .000000000..... .00........00.. .00.........00.
 * ............... ............... ............... ...............
 */

// TODO: add the reast of the letters later
uint8_t half_letter_masks[7][16][15] = {
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0b111, 0b111, 0, 0, 0, 0b111, 0b111, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0b111, 0b111, 0b111, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0},
        {0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0},
        {0, 0, 0, 0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }
};

/*
 * //// example half display numbers ////
 * 15 columns x 16 rows
 * - This is so we can fit 4 numbers on the display at once
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * .......00...... ............... ............... ...............
 * .......00...... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * .......00...... ............... ............... ...............
 * .......00...... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 * ............... ............... ............... ...............
 */

uint8_t half_character_masks[][16][15] = {
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0b111, 0b111, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }
}

/*
 * color data stored as follows:
 * bit:     7   6   5   4   3   2   1   0
 * data:    NA  NA  R2  G2  B2  R1  G1  B1
 * init to 0
 */
// uint8_t image[ROWS][COLS] = {0};

uint8_t image[ROWS][COLS] = {
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
};


#endif