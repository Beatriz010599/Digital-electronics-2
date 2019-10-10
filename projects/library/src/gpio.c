#include "gpio.h"
#define DDR(x) (*(&x - 1))


/*  Functions  ---------------------------------------------------------*/
void  GPIO_config_output(volatile  uint8_t *reg_name , uint8_t  pin_num)

{
    // Body of the  function
    *reg_name  |= _BV(pin_num);
    }



void  GPIO_config_output(volatile uint8_t *reg_name,uint8_t pinnum)
{
    *reg_name  |= _BV(pin_num);
    }

void  GPIO_config_input_nopull(volatile uint8_t *reg_name,uint8_t pinnum)
{
    *reg_name  &= _BV(pin_num);
    DDR(*reg_name) &= ~_BV(pin_num);
    }

void  GPIO_config_input_pullup(volatile uint8_t *reg_name,uint8_t pinnum)
{
    *reg_name  |= _BV(pin_num);
    DDR(*reg_name) &= ~_BV(pin_num);
    }

void  GPIO_toggle(volatile uint8_t *regname,uint8_t pinnum);
    {
    *reg_name  ^= _BV(pin_num);
    }
void  GPIO_write(volatile uint8t *regname,uint8_t pinnum,uint8_t pinval);
{
    if(pinval == 1)
    {

        *reg_name  |= _BV(pin_num);
    }
    else
    {
        *reg_name  &= ~_BV(pin_num);
    }
    // Body of the  function
    }
void  GPIO_read(volatile  uint8_t *reg_name , uint8_t  pin_num);
{
    // Body of the  function
    return((*reg_name & _BV(pin_num))>>pin_num);
    }