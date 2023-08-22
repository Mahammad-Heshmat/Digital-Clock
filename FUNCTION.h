#ifndef FUNCTION_H_
#define FUNCTION_H_


#define SOUFOOF  0
#define A3MEDA  1
#define LEFT  0
#define RIGHT  1
#define UPPER  0
#define LOWER  1

volatile u8 POS [2] = {0,0};
volatile u8 DECI_SECOND ;
volatile u8 SECOND ;
volatile u8 MINUTES ;
volatile u8 HOUR ;
volatile u8 MODE ;


void TIMER2_init(void)
{
	TIMSK = 0 ;			// Disable overflow interrupt
	ASSR  = (1<<AS2);	//Enable asynchronous mode
	TCNT2 = 0;
	TCCR2 |= (1<<CS22)|(1<<CS00);				// set up timer with prescaller = 128
	while (ASSR & ((1<<TCN2UB)|(1<<TCR2UB)));	//wait for registers update
	TIFR  = (1<<TOV2);			//clear interrupt flags
	TIMSK |= (1 << TOIE2);		// enable overflow interrupt
	sei();		// enable global interrupts
}

void START_TIMER2_FOR_REAL_CLOCK(u8 hourr , u8 min , u8 sec , u8 modd )
{
	TIMSK = 0 ;			// Disable overflow interrupt
	ASSR  = (1<<AS2);	//Enable asynchronous mode
	TCNT2 = 0;
	TCCR2 |= (1<<CS22)|(1<<CS00);				// set up timer with prescaller = 128
	while (ASSR & ((1<<TCN2UB)|(1<<TCR2UB)));	//wait for registers update
	TIFR  = (1<<TOV2);			//clear interrupt flags
	TIMSK |= (1 << TOIE2);		// enable overflow interrupt
	sei();		// enable global interrupts
	
	SECOND = sec;
	MINUTES = min;
	HOUR = hourr ;
	MODE = modd ;
	u8 EVENT =1 ;
	while(EVENT)
	{
		LCD_voidSetCursor(LCD_U8_LINE2,1);
		LCD_voidSendNumberII(HOUR);
		LCD_voidSetCursor(LCD_U8_LINE2,6);
		LCD_voidSendNumberII(MINUTES);
		LCD_voidSetCursor(LCD_U8_LINE2,11);
		LCD_voidSendNumberII(SECOND);
		
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
		if(HOUR == 13 )
		{
			HOUR = 1 ;
			MINUTES = 0 ;
			SECOND = 0 ;
			if (MODE==0)
			{
				MODE=1;
				LCD_voidSetCursor(LCD_U8_LINE2,14);
				LCD_voidSendString("PM");
			} 
			else
			{
				MODE=0;
				LCD_voidSetCursor(LCD_U8_LINE2,14);
				LCD_voidSendString("AM");
			}
			
		}
		
		while (GET_BIT(PINC,0)==0)
		{ EVENT = 0 ;}
	}
}

void START_TIMER2_FOR_ALARM(u8 hourr , u8 min , u8 sec , u8 modd ,u8 ahour , u8 amin , u8 asec , u8 amode )
{
	TIMSK = 0 ;			// Disable overflow interrupt
	ASSR  = (1<<AS2);	//Enable asynchronous mode
	TCNT2 = 0;
	TCCR2 |= (1<<CS22)|(1<<CS00);				// set up timer with prescaller = 128
	while (ASSR & ((1<<TCN2UB)|(1<<TCR2UB)));	//wait for registers update
	TIFR  = (1<<TOV2);			//clear interrupt flags
	TIMSK |= (1 << TOIE2);		// enable overflow interrupt
	sei();		// enable global interrupts
	
	SECOND = sec;
	MINUTES = min;
	HOUR = hourr ;
	MODE = modd ;
	
	LCD_voidClear();
	LCD_voidSetCursor(LCD_U8_LINE2,1);
	LCD_voidSendNumberII(ahour);
	LCD_voidSetCursor(LCD_U8_LINE2,6);
	LCD_voidSendNumberII(amin);
	LCD_voidSetCursor(LCD_U8_LINE2,11);
	LCD_voidSendNumberII(asec);
	
	if (amode==0)
	{	LCD_voidSetCursor(LCD_U8_LINE2,14);
		LCD_voidSendString("AM");}
	else
	{	LCD_voidSetCursor(LCD_U8_LINE2,14);
		LCD_voidSendString("PM");}
	
	if (MODE==0)
	{	LCD_voidSetCursor(LCD_U8_LINE1,14);
		LCD_voidSendString("AM");}
	else
	{	LCD_voidSetCursor(LCD_U8_LINE1,14);
		LCD_voidSendString("PM");}
	
	u8 EVENT =1 ;
	while(EVENT)
	{
		LCD_voidSetCursor(LCD_U8_LINE1,1);
		LCD_voidSendNumberII(HOUR);
		LCD_voidSetCursor(LCD_U8_LINE1,6);
		LCD_voidSendNumberII(MINUTES);
		LCD_voidSetCursor(LCD_U8_LINE1,11);
		LCD_voidSendNumberII(SECOND);
		
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
		if(HOUR == 13 )
		{
			HOUR = 1 ;
			MINUTES = 0 ;
			SECOND = 0 ;
			if (MODE==0)
			{
				MODE=1;
				LCD_voidSetCursor(LCD_U8_LINE1,14);
				LCD_voidSendString("PM");
			}
			else
			{
				MODE=0;
				LCD_voidSetCursor(LCD_U8_LINE1,14);
				LCD_voidSendString("AM");
			}
		}
		
		if ((amode==MODE)&&(ahour==HOUR))
		{
			if ((amin==MINUTES)&&(asec==SECOND))
			{   
				while (EVENT)
				{
					DIO_voidSetPinValue(BUZZER,1);
					_delay_ms(500);
					DIO_voidSetPinValue(BUZZER,0);
					_delay_ms(500);
					while (GET_BIT(PINC,0)==0)
					{
						EVENT = 0 ;
					}
				}
			}
		}
		while (GET_BIT(PINC,0)==0)
		{ EVENT = 0 ;}
	}
}

void START_TIMER2_FOR_TIMER(u8 hourr , u8 min , u8 sec )
{
	TIMSK = 0 ;			// Disable overflow interrupt
	ASSR  = (1<<AS2);	//Enable asynchronous mode
	TCNT2 = 0;
	TCCR2 |= (1<<CS22)|(1<<CS00);				// set up timer with prescaller = 128
	while (ASSR & ((1<<TCN2UB)|(1<<TCR2UB)));	//wait for registers update
	TIFR  = (1<<TOV2);			//clear interrupt flags
	TIMSK |= (1 << TOIE2);		// enable overflow interrupt
	sei();		// enable global interrupts
	
	SECOND = sec;
	MINUTES = min;
	HOUR = hourr ;
	u8 EVENT =1 ;
	while(EVENT)
	{
		LCD_voidSetCursor(LCD_U8_LINE2,1);
		LCD_voidSendNumberII(HOUR);
		LCD_voidSetCursor(LCD_U8_LINE2,6);
		LCD_voidSendNumberII(MINUTES);
		LCD_voidSetCursor(LCD_U8_LINE2,11);
		LCD_voidSendNumberII(SECOND);
		
		if ((SECOND == 0)&&(MINUTES > 0))
		{
			SECOND = 59 ;
			MINUTES -- ;
		}
		if ((MINUTES == 0)&&(HOUR > 0))
		{
			MINUTES = 59 ;
			HOUR -- ;
		}
		if(HOUR == 0 )
		{
			HOUR = 0 ;
			if ((SECOND==0)&&(MINUTES==0))
			{
				while (EVENT)
				{
					DIO_voidSetPinValue(BUZZER,1);
					_delay_ms(500);
					DIO_voidSetPinValue(BUZZER,0);
					_delay_ms(500);
					while (GET_BIT(PINC,0)==0)
					{
						EVENT = 0 ;
					}
				}
			}
		}
		while (GET_BIT(PINC,0)==0)
		{ EVENT = 0 ;}
	}
}

void START_TIMER2_FOR_STOP_WATCH( void )
{
	DECI_SECOND =0 ;
	SECOND =0 ;
	MINUTES =0 ;
	HOUR = 0 ;
	TIMSK = 0 ;			// Disable overflow interrupt
	ASSR  = (1<<AS2);	//Enable asynchronous mode
	TCNT2 = 185;
	TCCR2 |= (1<<CS20);				//(0<<CS22)| set up timer without prescaller
	while (ASSR & ((1<<TCN2UB)|(1<<TCR2UB)));	//wait for registers update
	TIFR  = (1<<TOV2);			//clear interrupt flags
	TIMSK |= (1 << TOIE2);		// enable overflow interrupt
	sei();		// enable global interrupts
	u8 EVENT = 1;
		while(EVENT)
		{
			LCD_voidSetCursor(LCD_U8_LINE2,0);
			LCD_voidSendNumberII(HOUR);
			LCD_voidSetCursor(LCD_U8_LINE2,4);
			LCD_voidSendNumberII(MINUTES);
			LCD_voidSetCursor(LCD_U8_LINE2,8);
			LCD_voidSendNumberII(SECOND);
			LCD_voidSetCursor(LCD_U8_LINE2,12);
			LCD_voidSendNumberII(DECI_SECOND);
			
			
			while (GET_BIT(PINC,0)==0)
			{
				EVENT = 0 ;
				_delay_ms(2000);
			}
		}
}

void GET_CHOICE_FROM4(void)
{
	u16 VRY , VRX ;
	u8 EVENT = 1;
	LCD_voidSetCursor(LCD_U8_LINE1,0);
	LCD_voidSendString("*");
	
	    while (EVENT)
	    {
		    VRY = ADC_u16Convert(ADC_u8_Channel0);
		    VRX = ADC_u16Convert(ADC_u8_Channel1);
		    
		    if (VRY == 0)
		    {
			    while(VRY == 0){VRY = ADC_u16Convert(ADC_u8_Channel1);};
			    POS[SOUFOOF]=0;
			    if (POS[A3MEDA]==LEFT)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString("*");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString(" ");
			    }
			    if (POS[A3MEDA]==RIGHT)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString("*");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString(" ");
			    }
		    }
		    if (VRY == 1023)
		    {
			    while(VRY==1023){VRY = ADC_u16Convert(ADC_u8_Channel1);};
			    POS[SOUFOOF]=1;
			    if (POS[A3MEDA]==LEFT)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString("*");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString(" ");
			    }
			    if (POS[A3MEDA]==RIGHT)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString("*");
			    }
		    }
		    
		    if (VRX == 1023)
		    {
			    while(VRX == 1023){VRX = ADC_u16Convert(ADC_u8_Channel0);};
			    POS[A3MEDA]=1;
			    if (POS[SOUFOOF]==UPPER)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString("*");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString(" ");
			    }
			    if (POS[SOUFOOF]==LOWER)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString("*");
			    }
		    }
		    if (VRX == 0)
		    {
			    while(VRX == 0){VRX = ADC_u16Convert(ADC_u8_Channel0);};
			    POS[A3MEDA]=0;
			    if (POS[SOUFOOF]==UPPER)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString("*");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString(" ");
			    }
			    if (POS[SOUFOOF]==LOWER)
			    {
				    LCD_voidSetCursor(LCD_U8_LINE1,0);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE1,8);
				    LCD_voidSendString(" ");
				    LCD_voidSetCursor(LCD_U8_LINE2,0);
				    LCD_voidSendString("*");
				    LCD_voidSetCursor(LCD_U8_LINE2,8);
				    LCD_voidSendString(" ");
			    }
		    }
		    
		    while (GET_BIT(PINB,7)==0)
		    {
			   EVENT = 0 ; 
		    }
	    }
}

u8 SET_HOUR (void)
{
	u8 x = 1 ,EVENT =1 ;
	u8 currunt_state ;
	u8 last_state = GET_BIT(PIND,4);
	
	LCD_voidSetCursor(LCD_U8_LINE2,1);
	LCD_voidSendNumberII(x);
	
	while (EVENT)
	{
		currunt_state = GET_BIT(PIND,4);
		
		if ( currunt_state != last_state )
		{
			if (GET_BIT(PIND,5) != currunt_state )
			{
				if (x==12)
				{
					x=1;
					LCD_voidSetCursor(LCD_U8_LINE2,1);
					LCD_voidSendNumberII(x);
				}
				else
				{
					x++;
					LCD_voidSetCursor(LCD_U8_LINE2,1);
					LCD_voidSendNumberII(x);
				}
				
				
			}
			else
			{
				if (x==1)
				{
					x=12;
					LCD_voidSetCursor(LCD_U8_LINE2,1);
					LCD_voidSendNumberII(x);
				}
				else
				{
					x--;
					LCD_voidSetCursor(LCD_U8_LINE2,1);
					LCD_voidSendNumberII(x);
				}
				
			}
		}
		last_state = currunt_state ;
		 while (GET_BIT(PINC,0)==0)
		 {
			 EVENT = 0 ;
		 }
	}
	return x ;
}

u8 SET_HOUR_TO_TIMER (void)
{
	u8 x = 0 ,EVENT =1 ;
	u8 currunt_state ;
	u8 last_state = GET_BIT(PIND,4);
	
	LCD_voidSetCursor(LCD_U8_LINE2,1);
	LCD_voidSendNumberIII(x);
	
	while (EVENT)
	{
		currunt_state = GET_BIT(PIND,4);
		
		if ( currunt_state != last_state )
		{
			if (GET_BIT(PIND,5) != currunt_state )
			{
					x++;
					LCD_voidSetCursor(LCD_U8_LINE2,1);
					LCD_voidSendNumberIII(x);
			}
			else
			{
					x--;
					LCD_voidSetCursor(LCD_U8_LINE2,1);
					LCD_voidSendNumberIII(x);
			}
		}
		last_state = currunt_state ;
		while (GET_BIT(PINC,0)==0)
		{
			EVENT = 0 ;
		}
	}
	return x ;
}

u8 SET_MINUTES (void)
{
	u8 x = 0 ,EVENT =1 ;
	u8 currunt_state ;
	u8 last_state = GET_BIT(PIND,4);
	
	LCD_voidSetCursor(LCD_U8_LINE2,6);
	LCD_voidSendNumberII(x);
	
	while (EVENT)
	{
		currunt_state = GET_BIT(PIND,4);
		
		if ( currunt_state != last_state )
		{
			if (GET_BIT(PIND,5) != currunt_state )
			{
				if (x==59)
				{
					x=0;
					LCD_voidSetCursor(LCD_U8_LINE2,6);
					LCD_voidSendNumberII(x);
				}
				else
				{
					x++;
					LCD_voidSetCursor(LCD_U8_LINE2,6);
					LCD_voidSendNumberII(x);
				}
				
				
			}
			else
			{
				if (x==0)
				{
					x=59;
					LCD_voidSetCursor(LCD_U8_LINE2,6);
					LCD_voidSendNumberII(x);
				}
				else
				{
					x--;
					LCD_voidSetCursor(LCD_U8_LINE2,6);
					LCD_voidSendNumberII(x);
				}
				
			}
		}
		last_state = currunt_state ;
		while (GET_BIT(PINC,0)==0)
		{
			EVENT = 0 ;
		}
	}
	return x ;
}

u8 SET_SECONDS (void)
{
	u8 x = 0 ,EVENT =1 ;
	u8 currunt_state ;
	u8 last_state = GET_BIT(PIND,4);
	
	LCD_voidSetCursor(LCD_U8_LINE2,11);
	LCD_voidSendNumberII(x);
	
	while (EVENT)
	{
		currunt_state = GET_BIT(PIND,4);
		
		if ( currunt_state != last_state )
		{
			if (GET_BIT(PIND,5) != currunt_state )
			{
				if (x==59)
				{
					x=0;
					LCD_voidSetCursor(LCD_U8_LINE2,11);
					LCD_voidSendNumberII(x);
				}
				else
				{
					x++;
					LCD_voidSetCursor(LCD_U8_LINE2,11);
					LCD_voidSendNumberII(x);
				}
				
				
			}
			else
			{
				if (x==0)
				{
					x=59;
					LCD_voidSetCursor(LCD_U8_LINE2,11);
					LCD_voidSendNumberII(x);
				}
				else
				{
					x--;
					LCD_voidSetCursor(LCD_U8_LINE2,11);
					LCD_voidSendNumberII(x);
				}
				
			}
		}
		last_state = currunt_state ;
		while (GET_BIT(PINC,0)==0)
		{
			EVENT = 0 ;
		}
	}
	return x ;
}

u8 SET_MODE (void)
{
	u8 x = 0 ,EVENT =1 ;
	u8 currunt_state ;
	u8 last_state = GET_BIT(PIND,4);
	
	LCD_voidSetCursor(LCD_U8_LINE2,14);
	LCD_voidSendString("AM");
	
	while (EVENT)
	{
		currunt_state = GET_BIT(PIND,4);
		
		if ( currunt_state != last_state )
		{
			if (GET_BIT(PIND,5) != currunt_state )
			{
				if (x==1)
				{
					x=0;
					LCD_voidSetCursor(LCD_U8_LINE2,14);
					LCD_voidSendString("AM");
				}
				else
				{
					x++;
					LCD_voidSetCursor(LCD_U8_LINE2,14);
					LCD_voidSendString("PM");
				}
				
				
			}
			else
			{
				if (x==0)
				{
					x=1;
					LCD_voidSetCursor(LCD_U8_LINE2,14);
					LCD_voidSendString("PM");
				}
				else
				{
					x--;
					LCD_voidSetCursor(LCD_U8_LINE2,14);
					LCD_voidSendString("AM");
				}
				
			}
		}
		last_state = currunt_state ;
		while (GET_BIT(PINC,0)==0)
		{
			EVENT = 0 ;
		}
	}
	return x ;
}
#endif