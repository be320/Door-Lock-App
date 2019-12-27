#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include <stdbool.h>

#define LCD_CTRL_DATA GPIO_PORTE_DATA_R
#define LCD_DATA_DATA GPIO_PORTB_DATA_R
#define EN 0x08
#define RS 0x10
#define RW 0x20

/*#define EN 0x20
#define RS 0x08
#define RW 0x10*/

void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_start(void);
void delayMs(int n);
void delayUS(int n);
void init(void);
unsigned char checkPressed(void);
char checkrow(int state);
unsigned char getKey(void);
void lightOn (unsigned char key);
void reset (void);
void blink(void);
bool checkpass(void);
void Unlock(void);
void showmessage(char message[],int size);
