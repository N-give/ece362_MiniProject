#ifndef H_DISPLAY
#define H_DISPLAY

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

/*
 * color data stored as follows:
 * bit:     7   6   5   4   3   2   1   0
 * data:    NA  NA  R2  G2  B2  R1  G1  B1
 * init to 0
 */

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
#define ROWS 16

void setup_tim2();
void setup_tim3();
void setup_tim15();
void setup_gpio(void);
void draw(void);
void draw_row(int);
void set_pixel(uint8_t, int, int);
uint8_t get_pixel(int, int);
void display_character(uint8_t, int, int);
void change_number(uint8_t, int, int);
void display_number(uint8_t, int, int);
void clear_char(int, int);
int clear_num_transition(uint8_t, int, int, int);
int set_num_transition(uint8_t, int, int, int);

void set_display_mode(int);
void set_display_time(int, int);
void set_display_date(int, int, int);
void display_colon();
void display_dash(int);

void clear_display();
void clear_row(int);
void clear_col(int);
void clear_diamond();

void clear_row_right(int);
void clear_row_left(int);
void clear_col_down(int);
void clear_col_up(int);

void set_row_right(int);
void set_row_left(int);
void set_col_down(int);
void set_col_up(int);

void flip_row_right(int);
void flip_row_left(int);
void flip_col_down(int);
void flip_col_up(int);

void set_swirl();
void clear_swirl();
void flip_swirl();

uint8_t display_color;

/*
 * //// example half display numbers ////
 * 15 columns x 16 rows
 * - This is so we can fit 4 numbers on the display at once
 * ............... ............... ............... ...............
 * .....00000..... .......00...... ....000000..... ....0000000....
 * ...00.....00... ......000...... ..00......00... ..00.......00..
 * ..00.......00.. .....0000...... .00........00.. .00.........00.
 * .00.........00. ....00.00...... .00........00.. .00.........00.
 * .00.........00. ...00..00...... ..00.......00.. ...........00..
 * .00.........00. .......00...... ..........00... .........00....
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

uint8_t half_number_masks[10][16][15];

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
 * ...00.....00... .00............ .......0....... .......0.......
 * ..00.......00.. .00............ .......0....... .......0.......
 * .00.........00. .00............ .......0....... .......0.......
 * .00.........00. .00............ .......0....... .......0.......
 * .00............ .00............ .......0....... .......0.......
 * .00............ .00000000...... .......0....... .......0.......
 * .00............ .00............ .......0....... .......0.......
 * .00............ .00............ .......0....... .......0.......
 * .00.........00. .00............ .......0....... .......0.......
 * .00.........00. .00............ .......0....... .......0.......
 * ..00.......00.. .00............ .......0....... .......0.......
 * ...00.....00... .00............ .......0....... .......0.......
 * ....0000000.... .0000000000000. .......0....... .0000000000000.
 * ............... ............... ............... ...............
 *
 * ............... ............... ............... ...............
 * .00.........00. .0000000....... .......0....... .00............
 * .000.......000. .00.....00..... ......000...... .00............
 * .0000.....0000. .00.......00... .....00.00..... .00............
 * .00.00...00.00. .00........00.. ....00...00.... .00............
 * .00..00000..00. .00.........00. ....00...00.... .00............
 * .00...000...00. .00.........00. ...00.....00... .00............
 * .00.........00. .00.........00. ...00.....00... .00............
 * .00.........00. .00.........00. ...000000000... .00............
 * .00.........00. .00.........00. ..00......00... .00............
 * .00.........00. .00.........00. ..00......00... .00............
 * .00.........00. .00.........00. ..00.......00.. .00............
 * .00.........00. .00........00.. .00........00.. .00............
 * .00.........00. .00.......00... .00........00.. .0000000000000.
 * .00.........00. .000000000..... .00........00.. .0000000000000.
 * ............... ............... ............... ...............
 *
 * ...............
 * .000000000.....
 * .00......00....
 * .00.......00...
 * .00........00..
 * .00........00..
 * .00.......00...
 * .00......00....
 * .00000000......
 * .00.00.........
 * .00..00........
 * .00...00.......
 * .00....00......
 * .00.....00.....
 * .00......00....
 * ...............
 *
 *
 */

// TODO: add the reast of the letters later
uint8_t half_letter_masks[8][16][15];

/*
 * //// example half display numbers ////
 * 4 columns x 16 rows
 * - This is so we can fit 4 numbers on the display at once
 * .... .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * ..00 .... .... .... .... .... .... ....
 * ..00 .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * .... .000 .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * ..00 .... .... .... .... .... .... ....
 * ..00 .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 * .... .... .... .... .... .... .... ....
 */

uint8_t half_character_masks[2][8][4];

/*
 * color data stored as follows:
 * bit:     7   6   5   4   3   2   1   0
 * data:    NA  NA  R2  G2  B2  R1  G1  B1
 * init to 0
 */
// uint8_t image[ROWS][COLS] = {0};
uint8_t image[ROWS][COLS];

#endif
