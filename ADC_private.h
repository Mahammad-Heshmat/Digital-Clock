/***************************************/
/*         Auother: Mahammad Heshmat   */
/*         Data   : 16-10-2022          */
/*         Version: 1.0                */
/*         Module : ADC                */
/*                                     */
/***************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADC_u8_EXTERNAL_AVCC       0
#define ADC_u8_EXTERNAL_AREF       1
#define ADC_u8_EXTERNAL_INTERNAL   2

#define ADC_u8_LEFT     3
#define ADC_u8_RIGHT    4

#define ADC_u8_BY2    1
#define ADC_u8_BY4    2
#define ADC_u8_BY8    3
#define ADC_u8_BY16   4
#define ADC_u8_BY32   5
#define ADC_u8_BY64   6
#define ADC_u8_BY128  7

#define ADCL    *((volatile u8 *)0x24)
#define ADCH    *((volatile u8 *)0x25)
#define ADCSRA  *((volatile u8 *)0x26)
#define ADMUX   *((volatile u8 *)0x27)

#endif