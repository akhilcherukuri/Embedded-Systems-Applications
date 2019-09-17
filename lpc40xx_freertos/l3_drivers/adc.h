#pragma once
#include<stdbool.h>
#include<stdint.h>

#include "lpc40xx.h"

typedef enum{
    pin0_25 = 0,
    pin0_26 = 1,
    pin1_30 = 37,
    pin1_31 = 38
}adc_pins_e;

typedef enum{
    adc0_2 = 2,
    adc0_3 = 3,
    adc0_4 = 4,
    adc0_5 = 5
}adc_channels_e;

typedef union{
    uint32_t CR;
    struct{
         uint32_t sel        : 8,
		  clkdiv     : 8,
		  burst      : 1,
		             : 4,
		  power      : 1,
		             : 2,
		  start      : 3,
		  edge       : 1,
		             : 4 ;
    };
}adc_cr_t;

/*initializes adc pin  
 * @params: requires adc pin and corresponding adc channel*/
bool adc__init(adc_pins_e adc_pin, adc_channels_e adc_channel);

/*returns the ADC value computed from a channel
 * @params: adc_channel which was initialized in adc__init*/
uint16_t adc__get_value(adc_channels_e adc_channel);
