

# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "DIO_interface.h"
# include "Keypad_config.h"
# include "Keypad_interface.h"
# include "Keypad_private.h"


void KEYPAD_voidInit(void)
{
	/*The pins are manipulated (not like the configurations)*/
	// Set keypad columns pins as OUTPUT
	DIO_voidSetPinDirection(KEYPAD_CLOUMNS_PORT, KEY_PAD_COLUMN0_PIN, DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_CLOUMNS_PORT, KEY_PAD_COLUMN1_PIN, DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_CLOUMNS_PORT, KEY_PAD_COLUMN2_PIN, DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_CLOUMNS_PORT, KEY_PAD_COLUMN3_PIN, DIO_u8PIN_OUTPUT);

	// Set keypad rows pins as INPUT
	DIO_voidSetPinDirection(KEYPAD_ROWS_PORT, KEY_PAD_ROW0_PIN, DIO_u8PIN_INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROWS_PORT, KEY_PAD_ROW1_PIN, DIO_u8PIN_INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROWS_PORT, KEY_PAD_ROW2_PIN, DIO_u8PIN_INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROWS_PORT, KEY_PAD_ROW3_PIN, DIO_u8PIN_INPUT);

	/* Set keypad port value to HIGH (to enable pull-up in rows pins
	   and output HIGH signal on columns pins) */

	//DIO_voidSetPortValue(KEYPAD_PORT, DIO_u8PORT_HIGH);


	/* Set keypad pins values  to HIGH (to enable pull-up in rows pins
	   and output HIGH signal on columns pins) */
	DIO_voidSetPinValue(KEYPAD_CLOUMNS_PORT,KEY_PAD_COLUMN0_PIN,DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KEYPAD_CLOUMNS_PORT,KEY_PAD_COLUMN1_PIN,DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KEYPAD_CLOUMNS_PORT,KEY_PAD_COLUMN2_PIN,DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KEYPAD_CLOUMNS_PORT,KEY_PAD_COLUMN3_PIN,DIO_u8PIN_HIGH);

	DIO_voidSetPinValue(KEYPAD_ROWS_PORT,KEY_PAD_ROW0_PIN,DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KEYPAD_ROWS_PORT,KEY_PAD_ROW1_PIN,DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KEYPAD_ROWS_PORT,KEY_PAD_ROW2_PIN,DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KEYPAD_ROWS_PORT,KEY_PAD_ROW3_PIN,DIO_u8PIN_HIGH);
}

u8 KEYPAD_u8GetPressedKey(void)
{
	u8 local_u8PressedKey = KEYPAD_DEFAULT_KEY;

	// Keypad characters array
	u8 KeypadArr [KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = KEYPAD_ARR_VAL;

	// Rows and columns arrays
	u8 ColumnsArr[KEYPAD_COLS_NUM] = {KEY_PAD_COLUMN0_PIN, KEY_PAD_COLUMN1_PIN, KEY_PAD_COLUMN2_PIN, KEY_PAD_COLUMN3_PIN};
	u8 RowsArr[KEYPAD_ROWS_NUM] = {KEY_PAD_ROW0_PIN, KEY_PAD_ROW1_PIN, KEY_PAD_ROW2_PIN, KEY_PAD_ROW3_PIN};

	// Loop over each column
	for(u8 i = 0; i < KEYPAD_COLS_NUM; i++)
	{
		// Activate current column (Set to PIN_LOW)
		DIO_voidSetPinValue(KEYPAD_CLOUMNS_PORT, ColumnsArr[i], DIO_u8PIN_LOW);

		// Loop over rows to get the pressed key
		for(u8 j = 0; j < KEYPAD_ROWS_NUM; j++)
		{
			if(DIO_u8GetPinValue(KEYPAD_ROWS_PORT, RowsArr[j]) == DIO_u8PIN_LOW)
			{
				local_u8PressedKey = KeypadArr[j][i];

				// Polling till switch released (to avoid bouncing)
				while(DIO_u8GetPinValue(KEYPAD_ROWS_PORT, RowsArr[j]) == DIO_u8PIN_LOW)
				{
					/*Blank condition*/
					local_u8PressedKey = KeypadArr[j][i];
				}

				return local_u8PressedKey;
			}
			else{}
		}

		// deActivate the current column (Set to PIN_HIGH)
		DIO_voidSetPinValue(KEYPAD_CLOUMNS_PORT, ColumnsArr[i], DIO_u8PIN_HIGH);
	}
//if its the default value,it means that is no pressed key, so i will put simple if condition in the main.c so the LCD doesnt print it
	return local_u8PressedKey;
}



