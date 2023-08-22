/***************************************/
/*         Auother: Mahammad Heshmat   */
/*         Data   : 26-8-2022          */
/*         Version: 1.0                */
/*         Module : DIO                */
/*                                     */
/***************************************/

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#define DIO_U8_PORTA_LAST_PIN 7
#define DIO_U8_PORTB_LAST_PIN 15
#define DIO_U8_PORTC_LAST_PIN 23
#define DIO_U8_PORTD_LAST_PIN 31
#define DIO_U8_PORT_OFFSET    1

#define  DIO_U8_PORTA_DIR  CONC_BIT(DIO_U8_PIN7_DIR,DIO_U8_PIN6_DIR,DIO_U8_PIN5_DIR,DIO_U8_PIN4_DIR,DIO_U8_PIN3_DIR,DIO_U8_PIN2_DIR,DIO_U8_PIN1_DIR,DIO_U8_PIN0_DIR) 
#define  DIO_U8_PORTB_DIR  CONC_BIT(DIO_U8_PIN15_DIR,DIO_U8_PIN14_DIR,DIO_U8_PIN13_DIR,DIO_U8_PIN12_DIR,DIO_U8_PIN11_DIR,DIO_U8_PIN10_DIR,DIO_U8_PIN9_DIR,DIO_U8_PIN8_DIR)
#define  DIO_U8_PORTC_DIR  CONC_BIT(DIO_U8_PIN23_DIR,DIO_U8_PIN22_DIR,DIO_U8_PIN21_DIR,DIO_U8_PIN20_DIR,DIO_U8_PIN19_DIR,DIO_U8_PIN18_DIR,DIO_U8_PIN17_DIR,DIO_U8_PIN16_DIR)
#define  DIO_U8_PORTD_DIR  CONC_BIT(DIO_U8_PIN31_DIR,DIO_U8_PIN30_DIR,DIO_U8_PIN29_DIR,DIO_U8_PIN28_DIR,DIO_U8_PIN27_DIR,DIO_U8_PIN26_DIR,DIO_U8_PIN25_DIR,DIO_U8_PIN24_DIR)

#define PORTA *((volatile u8*)0x3B)
#define DDRA  *((volatile u8*)0x3A)
#define PINA  *((volatile u8*)0x39)

#define PORTB *((volatile u8*)0x38)
#define DDRB  *((volatile u8*)0x37)
#define PINB  *((volatile u8*)0x36)

#define PORTC *((volatile u8*)0x35)
#define DDRC  *((volatile u8*)0x34)
#define PINC  *((volatile u8*)0x33)

#define PORTD *((volatile u8*)0x32)
#define DDRD  *((volatile u8*)0x31)
#define PIND  *((volatile u8*)0x30)


#define DIO_U8_INPUT    0 
#define DIO_U8_OUTPUT   1

#define LOW    0
#define HIGH   1
#endif