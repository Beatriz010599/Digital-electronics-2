/*
 * ---------------------------------------------------------------------
 * Author:      Bruno Miguel Fernandes Esteves #221845
 *		Mara Reis #221848	
 *		Beatriz Lopes #221847
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-12-1
 * Last update: 2019-12-19
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 * Read the consumption of an element with the Atmega 328P using ACS712 curent sensor
 * and read the voltage with the internal ADC of de microcontroler using a current divider   
 * 
 * Note:
 *
 */

/* Includes ----------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>            // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
	int mode = 0; //Mode=0 --> Current Sensor // Mode=1 --> Tension from de ADC
	uint16_t value = 0; 
	uint16_t count = 0;
	uint16_t Amps = 0;
    uint16_t sensivity = 0.066;
    char rxbuffer[20];
    char uart_string[4];
    char uart_string2[4];
/* Function prototypes -----------------------------------------------*/
void selectpin (uint8_t mode); 
/* Functions ---------------------------------------------------------*/



int main(void)
{
/*
char buff [20];
    int status;
    char *text;
    float value2;
    value2 = 10.23;
    text = ftoa(value2,&status);
    strcpy(buff,text);
*/



    //ADC
    // Set Reference Voltage Source
    ADMUX |= _BV(REFS0);
    ADMUX &= ~_BV(REFS1);

   /* // Select ADC channel
    ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3)); */

    // Enable ADC
    ADCSRA |= _BV(ADEN);
    
    // Enable ADC interrupt
    ADCSRA |= _BV(ADIE);

    // Set ADC prescaler
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);

    /* Timer1 */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

   /* // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n"); */

    // Infinite loop
     while(1);
     
    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    ADCSRA |= _BV(ADSC);    
}

ISR(ADC_vect)

{
	
	if (mode==0){
	selectpin(mode); //This Function set the pin for the ADC
	value = ADC;                           
    //ftoa(value, uart_string2, 3); 
    sprintf(rxbuffer, "%d", value);
    uart_puts(rxbuffer);
    uart_puts("\r\nVoltage: ");
    uart_puts(uart_string2);
	mode++;
	}
	if (mode==1){
		selectpin(mode);
	value = ADC + 1;
    count = value * 0.004883;
    count -= 2.5 ;
    Amps = count / sensivity; 
    //ftoa(Amps, uart_string, 3);
    //ftoa(value, uart_string2, 3);
    uart_puts("\r\nCurrent: ");
    uart_puts(uart_string); 
    uart_puts("\r\nADC: ");
    uart_puts(uart_string2);
	mode--;
		
}
}




void selectpin (uint8_t mode) {
	
	if(mode==0)
    {
    ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3)); //Select The pin A0

	/* */
	}
	
    if(mode==1){  
    ADMUX |= _BV(MUX0); //Select the Pin A1
    ADMUX &= ~(_BV(MUX1));
	}
	
}




/*
    float value = 0; //uint16_t
    float count = 0;
    float Amps = 0;
    float sensivity = 0.066;
    float uart_string[4];
    float uart_string2[4];
    

    //Read 10-bit ACD value
    
    value = ADC + 1;
    
    count = value * 0.004883;
    count -= 2.5 ;
    Amps = count / sensivity; 
    ftoa(Amps, uart_string, 10);
    ftoa(value, uart_string2, 10);

    uart_puts("\r\nAmps: ");
    uart_puts(uart_string);  //uart_string    //Tentar com o uart_putc
    uart_puts("\r\nADC: ");
    uart_puts(uart_string2); */
