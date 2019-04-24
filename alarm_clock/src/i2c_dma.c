#include "i2c.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdlib.h>
#include "display.h"
/*
uint8_t dec_to_bcd(uint8_t dec) {
  return ((((dec / 10) & 0xF) << 4) |
           ((dec % 10) & 0xF));
}
*/

void set_alarm(uint8_t * alarmMinsHrs){
  alarm_setup();
    // write_buf[2] = ((((desiredTime[1] / 10) & 0xF) << 4) |((desiredTime[1] % 10) & 0xF));
    // write_buf[3] = (((((desiredTime[2] / 10) & 0x1) << 4)) | (((desiredTime[2] / 20) & 0x1) << 5) |((desiredTime[2] % 10) & 0xF));
    uint8_t alarmSettings[3];
    alarmSettings[0] = ADDR_ALARM2MINS; //add it in header file
    alarmSettings[1] = ((((alarmMinsHrs[0] / 10) & 0xF) << 4) |((alarmMinsHrs[0] % 10) & 0xF));
    alarmSettings[2] = (((((alarmMinsHrs[1] / 10) & 0x1) << 4)) | (((alarmMinsHrs[1] / 20) & 0x1) << 5) |((alarmMinsHrs[1] % 10) & 0xF));
    I2C1_waitidle();
    I2C1_start(ADDR_RTC_I2C, WR);
    I2C1_senddata(alarmSettings, 3);
    I2C1_stop();
    alarmSettings[0] = ADDR_CONTROL;
    alarmSettings[1] = 128;
    alarmSettings[2] = 0x0E;
    I2C1_waitidle();
        I2C1_start(ADDR_RTC_I2C, WR);
        I2C1_senddata(alarmSettings, 3);
        I2C1_stop();

}

void alarm_setup(){
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER &= ~3;
    GPIOB->MODER |= 1;

    EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->IMR |= EXTI_IMR_MR0;
    NVIC->ISER[0] = 1 << EXTI0_1_IRQn;
}

//===========================================================================
// Check wait for the bus to be idle.
void I2C1_waitidle(void) {
    while ((I2C1->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY){  // while busy, wait.
      draw();
    }
}

//===========================================================================
// Subroutines for step 2.
//===========================================================================
// Initialize I2C1
/*
1.  Enable clock to GPIOB
2.  Configure PB6 and PB7 to alternate functions I2C1_SCL and I2C1_SDA
3.  Enable clock to I2C1
4.  Set I2C1 to 7 bit mode
5.  Enable NACK generation for I2C1
6.  Configure the I2C1 timing register so that PSC is 6, SCLDEL is 3 and SDADEL is 1 and SCLH is 3 and SCLL is 1
7.  Disable own address1 and own address 2 and set the 7 bit own address to 1
8.  Enable I2C1
 */
void init_I2C1() {
  // Student code goes here
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
  GPIOB->MODER &= ~((3<<12) | (3<<14) | (0b11<<(2*1)));
  GPIOB->MODER |= (2<<12) | (2<<14) | (0b10<<(2*1));
  GPIOB->AFR[0] |= (1<<(4*6)) | (1<<(4*7));

  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  I2C1->CR1 &= ~I2C_CR1_PE;
  I2C1->CR1 &= ~I2C_CR1_ANFOFF;
  I2C1->CR1 &= ~I2C_CR1_ERRIE;
  I2C1->CR1 &=  ~(I2C_CR1_NOSTRETCH);
  I2C1->CR1 |= (I2C_CR1_RXDMAEN | I2C_CR1_TXDMAEN);

  I2C1->TIMINGR = 0;
  I2C1->TIMINGR &= ~I2C_TIMINGR_PRESC;// Clear prescaler
  I2C1->TIMINGR |= 1 << 28; // Set prescaler to 0
  I2C1->TIMINGR |= 0x4 << 20; // SCLDEL
  I2C1->TIMINGR |= 0x2 << 16; // SDADEL
  I2C1->TIMINGR |= 0xF << 8; // SCLH
  I2C1->TIMINGR |= 0x13 << 0; // SCLL

  I2C1->OAR1 &= ~I2C_OAR1_OA1EN; // Disable own address 1
  I2C1->OAR2 &= ~I2C_OAR2_OA2EN; // Disable own address 2
  I2C1->OAR1 = I2C_OAR1_OA1EN | 0x2;// Set 7-bit own address 1

  I2C1->CR2 &= ~(I2C_CR2_ADD10); //7-bit mode
  I2C1->CR2 |= I2C_CR2_NACK; //NACK generation
  I2C1->CR2 |= I2C_CR2_AUTOEND; // Enable the auto end

  I2C1->ICR     |=  ( I2C_ICR_ADDRCF     |
                        I2C_ICR_NACKCF   |
                        I2C_ICR_STOPCF   |
                        I2C_ICR_BERRCF   |
                        I2C_ICR_ARLOCF   |
                        I2C_ICR_OVRCF    |
                        I2C_ICR_PECCF    |
                        I2C_ICR_TIMOUTCF |
                        I2C_ICR_ALERTCF  );

  I2C1->CR1 |= I2C_CR1_PE;
  //---------End-----------
}


void config_DMA() {
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;

  // channel 2 for transmit
  DMA1_Channel2->CCR &= ~(
      DMA_CCR_MEM2MEM | DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE |
      DMA_CCR_PINC | DMA_CCR_CIRC);

  DMA1_Channel2->CCR |= (DMA_CCR_DIR | DMA_CCR_MINC);

  // channel 3 for receive
  DMA1_Channel3 &= ~(
      DMA_CCR_MEM2MEM
      | DMA_CCR_PL
      | DMA_CCR_MSIZE
      | DMA_CCR_PSIZE
      | DMA_CCR_PINC
      | DMA_CCR_CIRC
      | DMA_CCR_DIR
      | DMA_CCR_PL
      );

  DMA1_Channel3 |= (DMA_CCR_MINC | DMA_CCR_TCIE);
}

//===========================================================================
// Subroutines for step 3.
//===========================================================================
// See lab document for description
void I2C1_start(uint8_t addr, uint32_t dir) {
    // Student code goes here
    I2C1->CR2 &= ~I2C_CR2_RD_WRN; // possible error correction
    I2C1->CR2 &= ~(I2C_CR2_SADD);
    I2C1->CR2 |= (addr<<1);
    for(int i=0; i<100; i++);
    if(dir == RD)
        I2C1->CR2 |= I2C_CR2_RD_WRN;
    I2C1->CR2 |= I2C_CR2_START;


    //---------End-----------
}

// See lab document for description
void I2C1_stop() {
    // Student code goes here
    if (I2C1->ISR & I2C_ISR_STOPF)
        return;
    // Master: Generate STOP bit after current byte has been transferred.
    I2C1->CR2 |= I2C_CR2_STOP;
    // Wait until STOPF flag is reset
    while( (I2C1->ISR & I2C_ISR_STOPF) == 0){
      draw();
    }
    I2C1->ICR |= I2C_ICR_STOPCF; // Write to clear STOPF flag

    //---------End-----------
}

// See lab document for description
int I2C1_senddata(uint8_t* data, uint32_t size) {
    // Student code goes here
    int i;
    if (size <= 0 || data == 0) return FAIL;
    I2C1->CR2 &= ~(I2C_CR2_NBYTES);
    I2C1->CR2 |= ((size << 16) & I2C_CR2_NBYTES) ;
    for(i=0; i<size; i++) {
    // TXIS bit is set by hardware when the TXDR register is empty and the
    // data to be transmitted must be written in the TXDR register. It is
    // cleared when the next data to be sent is written in the TXDR reg.
    // The TXIS flag is not set when a NACK is received.
        //int timeout = 0;
        while( (I2C1->ISR & I2C_ISR_TXIS) == 0) {
          draw();
        }
               // timeout += 1;
                //if (timeout > 1000000) return FAIL;
        //}
    // TXIS is cleared by writing to the TXDR register.
        I2C1->TXDR = data[i] & I2C_TXDR_TXDATA;
    }
    // Wait until TC flag is set or the NACK flag is set.
    while((I2C1->ISR & I2C_ISR_TC) == 0 && (I2C1->ISR & I2C_ISR_NACKF) == 0){
      draw();
    }
    if ( (I2C1->ISR & I2C_ISR_NACKF) != 0)
        return FAIL;
    //i2c_stop();
    return SUCCESS;

    //---------End-----------
}

// See lab document for description
int I2C1_readdata(uint8_t * data, uint32_t size) {
    // Student code goes here
    I2C1->CR2 &= ~(I2C_CR2_NBYTES);
    I2C1->CR2 |= ((size << 16) & I2C_CR2_NBYTES) ;
    //data[0] = 0;
    //data[1] = 0;
    //data[2] = 0;
    for(int i=0; i<size; i++) {
    // TXIS bit is set by hardware when the TXDR register is empty and the
    // data to be transmitted must be written in the TXDR register. It is
    // cleared when the next data to be sent is written in the TXDR reg.
    // The TXIS flag is not set when a NACK is received.
        int timeout = 0;
        while( (I2C1->ISR & I2C_ISR_RXNE) == 0) {
          draw();
        }
                //timeout += 1;
               // if (timeout > 1000000)
                  //  return FAIL;
       // }
    // TXIS is cleared by writing to the TXDR register.
        data[i] = I2C1->RXDR;
    }
    // Wait until TC flag is set or the NACK flag is set.
    while((I2C1->ISR & I2C_ISR_TC) == 0 && (I2C1->ISR & I2C_ISR_NACKF) == 0){
      draw();
    }

    if ( (I2C1->ISR & I2C_ISR_NACKF) != 0)
        return FAIL;
    //i2c_stop();
    return SUCCESS;

    //---------End-----------
}

//===========================================================================
// Subroutines for step 4.
//===========================================================================
// See lab document for description
void simple_osc(){
    uint8_t  read[1];
    //read = malloc(2*sizeof(uint8_t));
    I2C1_waitidle();
    micro_wait(1);
    I2C1_start(ADDR_RTC_I2C, RD);
    I2C1_readdata(read,1);
    I2C1_stop();
    printf("%u\n", read[0]);
}

void init_DS3231(){
    uint8_t write_buf[3];
    write_buf[0] = ADDR_CONTROL;
    write_buf[1] = 0x00;  // DS3231 EOSC enabled, INTCN enabled, SQW set to 1Hz
    write_buf[2] = 0x08; //clears alarm flags

    I2C1_waitidle();
    I2C1_start(ADDR_RTC_I2C, WR);
    int flag = I2C1_senddata(write_buf, 3);
    I2C1_stop();

}


void read_time(uint8_t * currentTime_buffer){
    // Student code goes here
    //uint8_t currentTime_buffer[3];
    // uint8_t * currentTime_buffer;
    // currentTime_buffer = malloc(3*sizeof(uint8_t));
    // uint8_t currentTime_buffer[3];
    I2C1_waitidle();
    I2C1_start(ADDR_RTC_I2C, WR);
    uint8_t data[1];
    data[0] = ADDR_SECONDS;
    I2C1_senddata(data, 1);
    //I2C1_stop(); //needed?
    I2C1_start(ADDR_RTC_I2C, RD);
    //int temp = -20;
    int flag = I2C1_readdata(currentTime_buffer, 3);
    currentTime_buffer[0] = ((currentTime_buffer[0] >> 4) * 10) + (currentTime_buffer[0] & 0x0F);
    currentTime_buffer[1] = ((currentTime_buffer[1] >> 4) * 10) + (currentTime_buffer[1] & 0x0F);
    currentTime_buffer[2] = (((currentTime_buffer[2] >> 5) & 0x1) * 20) + (((currentTime_buffer[2] >> 4) & 0x1) * 10) + (currentTime_buffer[2] & 0x0F);
    //return -25; for what?
    if(flag == FAIL) printf("We failed!");
    I2C1_stop(); //needed?
    // return currentTime_buffer;
    //---------End-----------
}

void read_alarm(uint8_t * currentTime_buffer){
    // Student code goes here
    //uint8_t currentTime_buffer[3];
    // uint8_t * currentTime_buffer;
    // currentTime_buffer = malloc(3*sizeof(uint8_t));
    // uint8_t currentTime_buffer[3];
    I2C1_waitidle();
    I2C1_start(ADDR_RTC_I2C, WR);
    uint8_t data[1];
    data[0] = ADDR_SECONDS;
    I2C1_senddata(data, 1);
    //I2C1_stop(); //needed?
    I2C1_start(ADDR_RTC_I2C, RD);
    //int temp = -20;
    int flag = I2C1_readdata(currentTime_buffer, 3);
    currentTime_buffer[0] = ((currentTime_buffer[0] >> 4) * 10) + (currentTime_buffer[0] & 0x0F);
    currentTime_buffer[1] = ((currentTime_buffer[1] >> 4) * 10) + (currentTime_buffer[1] & 0x0F);
    currentTime_buffer[2] = (((currentTime_buffer[2] >> 5) & 0x1) * 20) + (((currentTime_buffer[2] >> 4) & 0x1) * 10) + (currentTime_buffer[2] & 0x0F);
    //return -25; for what?
    if(flag == FAIL) printf("We failed!");
    I2C1_stop(); //needed?
    // return currentTime_buffer;
    //---------End-----------
}


//===========================================================================
// Subroutines for step 5.
//===========================================================================
// See lab document for description
void set_time(uint8_t * desiredTime) {
    // Student code goes here
    uint8_t write_buf[4];
    write_buf[0] = ADDR_SECONDS;
    write_buf[1] = ((((desiredTime[0] / 10) & 0xF) << 4) |((desiredTime[0] % 10) & 0xF));
    write_buf[2] = ((((desiredTime[1] / 10) & 0xF) << 4) |((desiredTime[1] % 10) & 0xF));
    write_buf[3] = (((((desiredTime[2] / 10) & 0x1) << 4)) | (((desiredTime[2] / 20) & 0x1) << 5) |((desiredTime[2] % 10) & 0xF));
    I2C1_waitidle();
    I2C1_start(ADDR_RTC_I2C, WR);
    int flag = I2C1_senddata(write_buf, 4);
    if(flag == FAIL) printf("We failed!");
    I2C1_stop();
    //micro_wait(5000);

    //---------End-----------
}
