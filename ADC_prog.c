
#define F_CPU 16000000UL
#include <util/delay.h>

#include "STD_types.h"
#include "BIT_MATH.h"
#include "ADC_private.h"
#include "ADC_int.h"
#include "ADC_config.h"


void ADC_voidInit(void)
{
	#if ADC_u8_VREF  == ADC_u8_EXTERNAL_AREF
	CLEAR_BIT(ADMUX , 6);
	CLEAR_BIT(ADMUX , 7);
	#elif ADC_u8_VREF  == ADC_u8_EXTERNAL_AVCC
	SET_BIT(ADMUX , 6);
	CLEAR_BIT(ADMUX , 7);
	#elif ADC_u8_VREF  == ADC_u8_EXTERNAL_INTERNAL
	SET_BIT(ADMUX , 6);
	SET_BIT(ADMUX , 7);
	#endif
	
	#if ADC_u8ADJUSTMENT == ADC_u8_LEFT
	SET_BIT(ADMUX , 5);
	#elif ADC_u8ADJUSTMENT == ADC_u8_RIGHT
	CLEAR_BIT(ADMUX , 5);
	#endif
	
	
	#if ADC_u8_PRESCALER == ADC_u8_BY2
	CLEAR_BIT(ADCSRA , 0);
	CLEAR_BIT(ADCSRA , 1);
	CLEAR_BIT(ADCSRA , 2);
	#elif ADC_u8_PRESCALER == ADC_u8_BY4
    #elif ADC_u8_PRESCALER == ADC_u8_BY8
	#elif ADC_u8_PRESCALER == ADC_u8_BY16
	#elif ADC_u8_PRESCALER == ADC_u8_BY32
	#elif ADC_u8_PRESCALER == ADC_u8_BY64
    #elif ADC_u8_PRESCALER == ADC_u8_BY128
		SET_BIT(ADCSRA , 0);
		SET_BIT(ADCSRA , 1);
		SET_BIT(ADCSRA , 2);
	#endif
	
	ADC_voidEnable();
}

void ADC_voidEnable(void)
{
	SET_BIT(ADCSRA , 7);
}

void ADC_voidDisable(void)
{
	CLEAR_BIT(ADCSRA , 7);
}

#if ADC_u8ADJUSTMENT == ADC_u8_LEFT
u8 ADC_u8Convert(u8 Local_u8Channel)
{
		ADC_voidDisable();
		_delay_ms(500);
	ADMUX = ADMUX & 0b11100000; // mask
	ADMUX =  ADMUX | Local_u8Channel;
	_delay_ms(500);
	ADC_voidEnable();
	_delay_ms(500);
	// start conversion
	SET_BIT(ADCSRA , 6);
	// wait for ADC to finish conversion
	while(GET_BIT(ADCSRA , 6) == 1);
	
	return ADCH;
}

#elif ADC_u8ADJUSTMENT == ADC_u8_RIGHT
u16 ADC_u16Convert(u8 Local_u8Channel)
{
	u8 Local_u8High = 0;
	u8 Local_u8LOW = 0;
	u16 result = 0;
	
	ADMUX = ADMUX & 0b11100000; // mask
	ADMUX =  ADMUX | Local_u8Channel;
	ADCL = 0;
	ADCH = 0;
	// start conversion
	SET_BIT(ADCSRA , 6);
	// wait for ADC to finish conversion
	while(GET_BIT(ADCSRA , 6) == 1);
	
	Local_u8LOW = ADCL;
    Local_u8High = ADCH;

	result = ( (Local_u8High & 0b00000011) << 8) | Local_u8LOW;
	return result;
}

#endif