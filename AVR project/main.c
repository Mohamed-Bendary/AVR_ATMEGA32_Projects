
# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "DIO_interface.h"
# include "LCD_interface.h"
# include "Keypad_interface.h"
# include "ADC_interface.h"
# include "UART_Interface.h"
# include "EXTI_interface.h"
# include <util/delay.h>


#define Autonomous_Mode      'A'
#define Manual_Mode          'B'

#define Manual_Mode_LampOn   'C'
#define Manual_Mode_LampOFF  'D'
#define Manual_Mode_FanOn    'E'
#define Manual_Mode_FanOFF   'F'

#define HighTemp             150
#define LowTemp              50

void Lamp_On (void);
void Lamp_OFF(void);
void Fan_On  (void);
void Fan_OFF (void);

void IR_SystemON_OFF(void);

u8 LM35TempCalculations (void);

u8 APP_u8SentUARTMode=NULL;
u8 APP_u8SentUARTManualAction=NULL;

u8 Local_u8ElementsEntered=0;
u8 Local_PasswordIsCorrect=0;
void main(void)
{
	u8 Local_u8TempReading=0;
	u8 Local_KEYVAL;

	/*Definig arrays for the correct password & for the password the user will put
	 * to compare them */
	char Local_u8CorrectPasswordArr[4]={'2','2','2','2'};
	char Local_u8TrialPasswordArr[4];


	/*Defining the lamp pin as output*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_OUTPUT);

	/*Defining the Fan pin as output*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_OUTPUT);

	/*Defining the EXT0 pin as input*/
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_INPUT);

	/*Setting the ADC channel pin to input*/
	DIO_voidSetPinDirection(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_INPUT);

	/*RX PIN*/
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_INPUT);

	/*TX PIN*/
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_OUTPUT);



	/*Initialize USART*/
	UART_voidInit();

	/*Initializing the ADC*/
	ADC_voidADCInit();

	/*Initializing the EXT0 for IR*/
	EXTI_voidINT0Init();

	/*Set callback function to excute the ISR*/
	EXTI_u8SetCallBack(&IR_SystemON_OFF);

	/*Initializing the global interrupt*/
	GIE_voidEnable();

	/*Keybad initializing*/
	KEYPAD_voidInit();

	/*LCD initializing and clearing*/
	LCD_voidInit();
	LCD_voidClear();
	LCD_voidPosition(0,0);

	while(1)
	{

		while(Local_u8ElementsEntered!=4)
		{
			/*I will not check the password again if it was entered correctly*/
			if(Local_PasswordIsCorrect==1){break;}

			LCD_voidPosition(0,0);
			LCD_voidSendString("Enter pass");
			Local_KEYVAL=KEYPAD_u8GetPressedKey();
			if (Local_KEYVAL!=KEYPAD_DEFAULT_KEY)
			{
				Local_u8TrialPasswordArr[Local_u8ElementsEntered]=Local_KEYVAL;
				LCD_voidPosition(1,Local_u8ElementsEntered);
				LCD_voidSendCharacter(Local_KEYVAL);
				Local_u8ElementsEntered++;
			}
			else{}

		}
		if(Local_PasswordIsCorrect==0)
		{
			/*Checking if the entered password is correct or not*/
			if((Local_u8TrialPasswordArr[0]==Local_u8CorrectPasswordArr[0])&&(Local_u8TrialPasswordArr[1]==Local_u8CorrectPasswordArr[1])&&(Local_u8TrialPasswordArr[2]==Local_u8CorrectPasswordArr[2])&&(Local_u8TrialPasswordArr[3]==Local_u8CorrectPasswordArr[3]))
			{
				/*I put a flag to not check the password again if its correct*/
				Local_PasswordIsCorrect=1;
				LCD_voidClear();
				LCD_voidPosition(0,0);
				LCD_voidSendString("Password is R");
				LCD_voidPosition(1,0);
				LCD_voidSendString("Enter home");
				_delay_ms(100);
			}
			else if((Local_u8TrialPasswordArr[0]!=Local_u8CorrectPasswordArr[0])||(Local_u8TrialPasswordArr[1]!=Local_u8CorrectPasswordArr[1])||(Local_u8TrialPasswordArr[2]!=Local_u8CorrectPasswordArr[2])||(Local_u8TrialPasswordArr[3]!=Local_u8CorrectPasswordArr[3]))
			{

				LCD_voidClear();
				LCD_voidPosition(0,0);
				LCD_voidSendString("Password is W");
				LCD_voidPosition(1,0);
				LCD_voidSendString("Try again");
				_delay_ms(1000);
				LCD_voidClear();
				/*Clearing the holding variable of the elements to recheck */
				Local_u8ElementsEntered=0;


			}

		}



		if(APP_u8SentUARTMode==Autonomous_Mode)
		{
			while((APP_u8SentUARTMode==Autonomous_Mode)&&(Local_PasswordIsCorrect==1))
			{
				Local_u8TempReading=LM35TempCalculations();

				if(Local_u8TempReading>HighTemp)
				{
					Fan_On();
					Lamp_OFF();
					_delay_ms(1000);
				}

				else
				{
					Fan_OFF();
					Lamp_On();
					_delay_ms(1000);
				}

			}
			if(Local_PasswordIsCorrect==0)
			{
				Fan_OFF();
				Lamp_OFF();
			}



		}
		else if(APP_u8SentUARTMode==Manual_Mode)
		{
			while((APP_u8SentUARTMode==Manual_Mode)&&(Local_PasswordIsCorrect==1))
			{

				if(APP_u8SentUARTManualAction==Manual_Mode_LampOn)
				{
					Lamp_On();
					_delay_ms(500);
				}
				else if(APP_u8SentUARTManualAction==Manual_Mode_LampOFF)
				{
					Lamp_OFF();
					_delay_ms(500);
				}
				else if(APP_u8SentUARTManualAction==Manual_Mode_FanOn)
				{
					Fan_On();
					_delay_ms(500);
				}
				else if(APP_u8SentUARTManualAction==Manual_Mode_FanOFF)
				{
					Fan_OFF();
					_delay_ms(500);
				}


			}

			if(Local_PasswordIsCorrect==0)
			{
				Fan_OFF();
				Lamp_OFF();
			}


		}

		else
		{
			Fan_OFF();
			Lamp_OFF();
		}









	}
}



void Lamp_On (void)
{
	DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_HIGH);
}

void Lamp_OFF(void)
{
	DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_LOW);
}
void Fan_On (void)
{
	DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_HIGH);
}
void Fan_OFF (void)
{
	DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_LOW);
}





void IR_SystemON_OFF(void)
{
	u8 Local_u8IRData=DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8PIN2);
	if(Local_u8IRData==DIO_u8PIN_HIGH)
	 {

	 }
	else if(Local_u8IRData==DIO_u8PIN_LOW)
	 {
	/*Re-entering the password*/
     Local_u8ElementsEntered=0;
     Local_PasswordIsCorrect=0;
	 }

}



u8 LM35TempCalculations (void)
{
	u8 Local_u8DigitalChannelRead=ADC_u8GetChannelReadSynch(7);
	u8 Local_AnalogValue_millivolt=((u32)Local_u8DigitalChannelRead*5000UL)/256UL;
	u8 Local_TempretureReading=Local_AnalogValue_millivolt/10;


	return Local_TempretureReading;
}




void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	u8 Local_u8SentUARTData=UART_u8Recieve();

	if((Local_u8SentUARTData==Autonomous_Mode)||(Local_u8SentUARTData==Manual_Mode))
	{
		APP_u8SentUARTMode=Local_u8SentUARTData;
	}

	else if ((APP_u8SentUARTMode==Manual_Mode)&&
			((Local_u8SentUARTData==Manual_Mode_LampOn)||(Local_u8SentUARTData==Manual_Mode_LampOFF)||
			(Local_u8SentUARTData==Manual_Mode_FanOn)||(Local_u8SentUARTData==Manual_Mode_FanOFF)))
	{
		APP_u8SentUARTManualAction=Local_u8SentUARTData;
	}
	else
	{
		/*Do nothing*/

	}

}




