/***************************************/
/*         Auother: Mahammad Heshmat   */
/*         Data   : 16-10-2022          */
/*         Version: 1.0                */
/*         Module : ADC                */
/*                                     */
/***************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
/*
options:

ADC_u8_EXTERNAL_AVCC
ADC_u8_EXTERNAL_AREF
ADC_u8_EXTERNAL_INTERNAL

*/

#define ADC_u8_VREF   ADC_u8_EXTERNAL_INTERNAL

/*
ADC_u8_LEFT
ADC_u8_RIGHT

*/
#define ADC_u8ADJUSTMENT ADC_u8_RIGHT


/*
ADC_u8_BY4
ADC_u8_BY8
ADC_u8_BY16
ADC_u8_BY32
ADC_u8_BY64
ADC_u8_BY128
*/
#define ADC_u8_PRESCALER ADC_u8_BY128

#endif