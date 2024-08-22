
#include "Lcd/lcd.h"
#include "Keypad/keypad.h"
#include <string.h>
char eq[100]="";
uint8_t count,flag;
void SOLVE(char c)
{
	switch (c)
	{
		case '=':
		{
			uint16_t ans = 0;
			char last = '?';  // To keep track of the last operator
			int j = 0;

			while (j < count)
			{
				int x = 0;

				// Parse the number
				while (j < count && eq[j] != '*' && eq[j] != '-' && eq[j] != '/' && eq[j] != '+')
				{
					x *= 10;
					x += (eq[j] - '0');
					j++;
				}

				// Apply the last operation
				if (last == '?')
				{
					ans = x;  // Initialize ans with the first number
				}
				else
				{
					switch (last)
					{
						case '*':
						ans *= x;
						break;
						case '-':
						ans -= x;
						break;
						case '+':
						ans += x;
						break;
						case '/':
						if (x != 0)
						ans /= x;
						else
						{
							LCD_clear_screen();
							LCD_WRITE_STRING("Error 404");
							flag=1;
							count=0;
							return;
						}
						break;
					}
				}

				// Update the last operator
				if (j < count)
				{
					last = eq[j];
					j++;
				}
			}

			// Display the result on the LCD
			LCD_clear_screen();
			char ss[10];
			itoa(ans, ss, 10);  // Convert the integer 'ans' to a string and store it in 'ss'
			LCD_WRITE_STRING(ss);
			
			count=0;
flag=1;		}
		break;

		default:
		eq[count] = c;
		count++;
		break;
	}
}


int main()
{
	
	LCD_INIT();
	count=0;
	Keypad_init();
	_delay_ms(50);
	LCD_WRITE_STRING("hi Esraa !");
	_delay_ms(50);
	LCD_clear_screen();
	unsigned char key_pressed;
	flag=0;
	while(1){
		key_pressed = Keypad_getkey();
		switch(key_pressed){
			case 'A':
				break;
			case '?':
				LCD_clear_screen();
					flag=0;
				break;
			default:
				if (flag==0)
				LCD_WRITE_CHAR(key_pressed);
				SOLVE(key_pressed);
				
				break;
		}
	}
}


