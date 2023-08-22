/***************************************/
/*         Auother: Mahammad Heshmat   */
/*         Data   : 16-10-2022          */
/*         Version: 1.0                */
/*         Module : ADC                */
/*                                     */
/***************************************/

#ifndef ADC_INT_H_
#define ADC_INT_H_

void ADC_voidInit(void);
void ADC_voidEnable(void);
void ADC_voidDisable(void);

#define ADC_u8_Channel0  0
#define ADC_u8_Channel1  1
#define ADC_u8_Channel2  2
#define ADC_u8_Channel3  3
#define ADC_u8_Channel4  4
#define ADC_u8_Channel5  5
#define ADC_u8_Channel6  6
#define ADC_u8_Channel7  7

#if ADC_u8ADJUSTMENT == ADC_u8_LEFT
u8 ADC_u8Convert(u8 Local_u8Channel);
#elif ADC_u8ADJUSTMENT == ADC_u8_RIGHT
u16 ADC_u16Convert(u8 Local_u8Channel);
#endif

#endif