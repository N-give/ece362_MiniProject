// #include "i2c.h"
#include "i2c_test.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdlib.h>

// uint8_t trans_time[4] = {
//   ADDR_SECONDS,
//   ((((35 / 10) & 0xF) << 4) | ((35 % 10) & 0xF)),
//   ((((30 / 10) & 0xF) << 4) | ((30 % 10) & 0xF)),
//   (((((11 / 10) & 0xF) << 4) | 0x40) |((11 % 10) & 0xF))
// };


void init_I2C2 () {
  // set up pb10/11 for i2c
  RCC->AHBENR |= RCC_APB1ENR_I2C2EN;
  GPIOB->MODER &= ~(GPIO_MODER_MODER10 | GPIO_MODER_MODER11);
  GPIOB->MODER |= GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1;
  GPIOB->AFR[1] |= (1<<(4*2)) | (1<<(4*3));

  RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
  I2C2->CR1 &= ~I2C_CR1_PE;
  I2C2->CR1 &= ~(I2C_CR1_ANFOFF | I2C_CR1_ERRIE | I2C_CR1_NOSTRETCH);
  // I2C2->CR1 |= I2C_CR1_TXIE | I2C_CR1_RXIE ;
  I2C2->CR1 |= I2C_CR1_TXDMAEN | I2C_CR1_RXDMAEN;

  I2C2->CR2 &= ~I2C_CR2_ADD10; //7-bit mode
  I2C2->CR2 |= I2C_CR2_NACK | I2C_CR2_AUTOEND;

  I2C2->TIMINGR = 0;
  I2C2->TIMINGR &= ~I2C_TIMINGR_PRESC;// Clear prescaler
  I2C2->TIMINGR |= 1 << 28; // Set prescaler to 0
  I2C2->TIMINGR |= 0x4 << 20; // SCLDEL
  I2C2->TIMINGR |= 0x2 << 16; // SDADEL
  I2C2->TIMINGR |= 0xF << 8; // SCLH
  I2C2->TIMINGR |= 0x13 << 0; // SCLL

  I2C2->OAR1 &= ~I2C_OAR1_OA1EN; // Disable own address 1
  I2C2->OAR2 &= ~I2C_OAR2_OA2EN; // Disable own address 2
  I2C2->OAR1 = I2C_OAR1_OA1EN | 0x2;// Set 7-bit own address 1

  I2C2->CR1 |= I2C_CR1_PE;
}

void config_dma () {
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;

  // transmit number of bytes through i2c
  DMA1_Channel4->CCR &= ~DMA_CCR_EN;
  DMA1_Channel4->CCR &= ~(
    DMA_CCR_MEM2MEM || DMA_CCR_MSIZE || DMA_CCR_PSIZE ||
    DMA_CCR_PINC || DMA_CCR_CIRC || DMA_CCR_TEIE ||
    DMA_CCR_HTIE || DMA_CCR_TCIE
  );
  DMA1_Channel4->CCR |= DMA_CCR_DIR | DMA_CCR_MINC;
  // Need to enable after the number of bytes to transmit is changed
  // DMA1_Channel4->CCR |= DMA_CCR_EN;

  // read number of bytes from i2c
  DMA1_Channel5->CCR &= ~DMA_CCR_EN;
  DMA1_Channel5->CCR &= ~(
    DMA_CCR_MEM2MEM || DMA_CCR_MSIZE || DMA_CCR_PSIZE ||
    DMA_CCR_PINC || DMA_CCR_CIRC || DMA_CCR_TEIE ||
    DMA_CCR_HTIE || DMA_CCR_TCIE || DMA_CCR_DIR
  );
  DMA1_Channel5->CCR |= DMA_CCR_MINC;
  // Need to enable after the number of bytes to transmit is changed
  // DMA1_Channel5->CCR |= DMA_CCR_EN;
}

// handling tranfering data
void init_I2C2_DMA_trans(uint8_t * data, uint8_t size){
  DMA1_Channel4->CCR &= ~DMA_CCR_EN;
  DMA1_Channel4->CMAR = (uint32_t) data;
  DMA1_Channel4->CPAR = (uint32_t) (&(I2C2->TXDR));
  DMA1_Channel4->CNDTR = size;
  DMA1_Channel4->CCR |= DMA_CCR_EN;
}

void start_I2C2(uint8_t addr, uint32_t dir, uint8_t size) {
  I2C2->CR2 &= ~(I2C_CR2_RD_WRN | I2C_CR2_SADD | I2C_CR2_NBYTES);
  I2C2->CR2 |= (addr<<1) | (dir<<10) | (size<<16);
  // DMA must be initialized before start bit set
  // call this function after sending size to dma cntd reg
  I2C2->CR2 |= I2C_CR2_START;
}

void send_data_I2C2(uint8_t * data, uint8_t size) {
  init_I2C2_DMA_trans(data, size);
  start_I2C2(ADDR_RTC_I2C, 0, size);
}

void init_I2C_DMA_read(uint8_t * mem_loc, uint8_t size) {
  DMA1_Channel5->CCR &= ~DMA_CCR_EN;
  DMA1_Channel5->CMAR = (uint32_t) mem_loc;
  DMA1_Channel5->CPAR = (uint32_t) (&(I2C2->RXDR));
  DMA1_Channel5->CNDTR = size;
  DMA1_Channel5->CCR |= DMA_CCR_EN;
}

void receive_data_I2C2(uint8_t * data, uint8_t size) {
  init_I2C_DMA_read(data, size);
  start_I2C2(ADDR_RTC_I2C, 1, size);
}

void set_time2(uint8_t * set_time, uint8_t size) {
  send_data_I2C2(set_time, size);
}

void read_time2(uint8_t * rec_time, uint8_t size) {
  receive_data_I2C2(rec_time, size);
}
