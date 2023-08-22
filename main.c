/*
 * REAL_CLOCK.c
 *
 * Created: 19/12/2022 04:35:21 م
 * Author : Mahammad_7esHmaT
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "ADC_int.h"
#include "FUNCTION.h"

#define CLOCK  1
#define STOP_WATCH  2
#define ALARM  3
#define TIMER  4
u8 APP ;
static u8 STOP_OV =0 ;

ISR(TIMER2_OVF_vect)
{
	switch (APP)
	{
		case STOP_WATCH :
		{
			STOP_OV++;
			if (STOP_OV == 2)
			{
				DECI_SECOND ++ ;
				STOP_OV = 0;
				TCNT2 = 185;
			}
			if ( DECI_SECOND == 100 )
			{
				DECI_SECOND = 0 ;
				SECOND ++ ;
			}
			if(SECOND == 60 )
			{
				SECOND = 0 ;
				MINUTES ++ ;
			}
			if(MINUTES == 60 )
			{
				MINUTES = 0 ;
				HOUR ++ ;
			}
			if(HOUR == 100 )
			{
				HOUR = 0 ;
				MINUTES = 0 ;
				SECOND = 0 ;
				DECI_SECOND = 0 ;
			}
			break;
		}
		case TIMER :
		{
			SECOND -- ;
			break;
		}
		default:
		{
			SECOND ++ ;
			break;
		}
	}
}

int main(void)
{ 
	
	u8 H , M , S , D ;
	u8 ALARM_H , ALARM_M , ALARM_S , ALARM_D ;
	
	
	DIO_voidInit();
	LCD_voidInit();
	ADC_voidInit();

	DIO_voidSetPinValue(JOY_STICK_PUSHBOTTON,1); //PULL UP 
	DIO_voidSetPinValue(ENCODER_CLK,1);
	DIO_voidSetPinValue(ENCODER_DT,1);
	DIO_voidSetPinValue(ENCODER_PUSHBOTTON,1);
	
	
	
	while(1)
	{
		LCD_voidClear();
		LCD_voidSetCursor(LCD_U8_LINE1 ,1);
		LCD_voidSendString("CLOCK");
		LCD_voidSetCursor(LCD_U8_LINE2 ,1);
		LCD_voidSendString("ALARM");
		LCD_voidSetCursor(LCD_U8_LINE1 ,9);
		LCD_voidSendString("S.WATCH");
		LCD_voidSetCursor(LCD_U8_LINE2 ,9);
		LCD_voidSendString("TIMER");
		
		GET_CHOICE_FROM4();
		
		if ( (POS[0]==0) && (POS[1]==0) )      { APP=1; }	//CLOCK
		else if ( (POS[0]==0) && (POS[1]==1) ) { APP=2; }   //STOP WATCH
		else if ( (POS[0]==1) && (POS[1]==0) ) { APP=3; }	// ALARM
		else if ( (POS[0]==1) && (POS[1]==1) ) { APP=4; }	//TIMER
		
		switch (APP)
		{
			case CLOCK :
			{
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,0);
				LCD_voidSendString("HOUR MINT SCND");
				LCD_voidSetCursor(LCD_U8_LINE2 ,0);
				LCD_voidSendString("    :    :");
				H = SET_HOUR();
				M = SET_MINUTES();
				S = SET_SECONDS();
				D = SET_MODE();
				START_TIMER2_FOR_REAL_CLOCK(H,M,S,D);
				
				break;
			}
			case STOP_WATCH :
			{
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,0);
				LCD_voidSendString("HUR MIN SEC DECI");
				LCD_voidSetCursor(LCD_U8_LINE2 ,0);
				LCD_voidSendString("   :   :   :");
				START_TIMER2_FOR_STOP_WATCH();
				break;
			}
			case ALARM :
			{
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,1);
				LCD_voidSendString("AT FIRST ENTER");
				LCD_voidSetCursor(LCD_U8_LINE2 ,2);
				LCD_voidSendString("YOUR ALARM");
				_delay_ms(2000);
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,0);
				LCD_voidSendString("HOUR MINT SCND");
				LCD_voidSetCursor(LCD_U8_LINE2 ,0);
				LCD_voidSendString("    :    :");
				ALARM_H = SET_HOUR();
				ALARM_M = SET_MINUTES();
				ALARM_S = SET_SECONDS();
				ALARM_D = SET_MODE();
				
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,2);
				LCD_voidSendString("NOW ENTER");
				LCD_voidSetCursor(LCD_U8_LINE2 ,1);
				LCD_voidSendString("THE REAL TIME");
				_delay_ms(2000);
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,0);
				LCD_voidSendString("HOUR MINT SCND");
				LCD_voidSetCursor(LCD_U8_LINE2 ,0);
				LCD_voidSendString("    :    :");
				H = SET_HOUR();
				M = SET_MINUTES();
				S = SET_SECONDS();
				D = SET_MODE();
				
				START_TIMER2_FOR_ALARM(H,M,S,D,ALARM_H,ALARM_M,ALARM_S,ALARM_D);
				break;
			}
			case TIMER :
			{
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,2);
				LCD_voidSendString("ENTER YOUR");
				LCD_voidSetCursor(LCD_U8_LINE2 ,4);
				LCD_voidSendString("TIMER");
				_delay_ms(2000);
				LCD_voidClear();
				LCD_voidSetCursor(LCD_U8_LINE1 ,0);
				LCD_voidSendString("HOUR MINT SCND");
				LCD_voidSetCursor(LCD_U8_LINE2 ,0);
				LCD_voidSendString("    :    :");
				ALARM_H = SET_HOUR_TO_TIMER();
				ALARM_M = SET_MINUTES();
				ALARM_S = SET_SECONDS();
				START_TIMER2_FOR_TIMER (ALARM_H,ALARM_M,ALARM_S);
				break;
			}
		}
	}
}
