
#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/*Check for this value to know if the keybad is pressed or not*/
#define KEYPAD_DEFAULT_KEY		0xFF

void KEYPAD_voidInit(void);

u8 KEYPAD_u8GetPressedKey(void);

#endif /* KEYPAD_INTERFACE_H_ */
