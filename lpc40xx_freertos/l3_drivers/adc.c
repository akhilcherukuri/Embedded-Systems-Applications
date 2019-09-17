#include "adc.h"
#include "lpc_peripherals.h"

#define BASE_ADDR_PIN0_25 0x4002C064
#define ADC_DONE (1U << 31)
#define ADC_CLK  12000000U

static adc_cr_t adc_cr;
const uint8_t adc_func_sel0123 = 0x1;
const uint8_t adc_func_sel4567 = 0x3; 

bool adc__init(adc_pins_e adc_pin, adc_channels_e adc_channel)
{
    const uint8_t adc_func_sel0123 = 0x1;
    const uint8_t adc_func_sel4567 = 0x3; 	
    if(adc_pin <= pin1_31 && adc_channel >= 2 && adc_channel <= 5) 
    {
	uint32_t* adc_pin_reg = (uint32_t*)(BASE_ADDR_PIN0_25 + adc_pin * sizeof(uint32_t));    
        //power on adc peripheral
	lpc_peripheral__turn_on_power_to(LPC_PERIHPHERAL__ADC);

        *adc_pin_reg |= (adc_pin < pin1_30) ? (adc_func_sel0123) : (adc_func_sel4567);
        
	//select analog mode 
        *adc_pin_reg &= ~(1 << 7);

        //configure the CR register
        adc_cr.CR = 0;
        adc_cr.sel = 1 << adc_channel;
	const uint32_t clk_divider = clock__get_core_clock_hz()/ADC_CLK;
	adc_cr.clkdiv |= clk_divider;   //Generates 12Mhz or system frequency ADC clock
	adc_cr.burst = 1;
	adc_cr.power = 1;
        LPC_ADC -> CR = adc_cr.CR;
	return true;
    }
     
    return false;
}

uint16_t adc__get_value(adc_channels_e adc_channel)
{
    uint16_t result  = 0u;
    if(adc_channel <= adc0_5)
    {
        adc_cr.start = 0x1;
        LPC_ADC -> CR |= adc_cr.CR;
	while(!(LPC_ADC ->DR[adc_channel] & ADC_DONE));
	result = ((LPC_ADC ->DR[adc_channel] >> 4) & 0xfff);
    }
    return result;
} 

