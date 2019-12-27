#include "lib.h"

char input[4] = {'0','0','0','0'};
volatile int counter =0;
char pass[4] = {'1','9','9','9'};
char wrong[10] = {'w','r','o','n','g',' ','p','a','s','s'};
char welcome[7] = {'w','e','l','c','o','m','e'};

void delayMs (int delay)
{
    NVIC_ST_RELOAD_R = (16000*delay)-1;
    NVIC_ST_CTRL_R = 5;
    while((NVIC_ST_CTRL_R & 0x10000) == 0);
}
void delayUs (int delay)
{
    NVIC_ST_RELOAD_R = (16*delay)-1;
    NVIC_ST_CTRL_R = 5;
    while((NVIC_ST_CTRL_R & 0x10000) == 0);
}
void reset (void)
{
    LCD_command(0x01);
    LCD_command(0x02);
    counter=0;
}
void clear(void)
{
    LCD_command(0x01);
    LCD_command(0x02);
}
void blink(void)
{
    for(int i=0;i<5;i++)
    {
        GPIO_PORTF_DATA_R |= 0x02;
        delayMs(500);
        GPIO_PORTF_DATA_R &= ~(0x02);
        delayMs(500);
    }
}
void LCD_command(unsigned char command)
{
    LCD_CTRL_DATA = 0;     	/* RS = 0, R/W = 0 */
    LCD_DATA_DATA = command;
    LCD_CTRL_DATA = EN;    	/* pulse E */
    delayUs(1);		/* Enable pulse Width */
    LCD_CTRL_DATA = 0;
    if(command < 4)
        delayMs(2);         	/* command 1 and 2 needs up to 1.64ms */
    else
        delayUs(40);        /* all others 40 us */
}
void LCD_data(unsigned char data)
{
    LCD_CTRL_DATA = RS;    /* RS = 1, R/W = 0 */
    LCD_DATA_DATA = data;
    LCD_CTRL_DATA = EN | RS;   /* pulse E */
    delayUs(1);
    LCD_CTRL_DATA = 0;
    delayUs(40);

}
void LCD_start(void)
{  
    delayMs(20);            /* initialization sequence */// Wait >15 ms after power is applied
    LCD_command(0x30);		// command 0x30 = Wake up
    delayMs(5);				// must wait 5ms, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #2
    delayUs(100);			// must wait 100us, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #3
    delayUs(100);			// must wait 100us, busy flag not available
  // Prepare LCD Operation and Function  
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    //LCD_command(0x06);      /* move cursor right */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      
}
void init(void){
    //initialize ports B & E & F & A & C  & D       (E & B )  =>  LCD     (A & C) => KEYPAD    F => (SWITCHES & RED LED)  D2 => Motor  D3 => Arduino
    SYSCTL_RCGCGPIO_R |= 0x3f;
    while (SYSCTL_PRGPIO_R & 0x3f == 0){};
    GPIO_PORTF_LOCK_R   =       0x4c4f434b;
    GPIO_PORTF_CR_R     =       0x11;

    GPIO_PORTB_DIR_R   |=       0xff;
    GPIO_PORTE_DIR_R   |=       0x38;
    GPIO_PORTF_DIR_R   |=       0x02;
    GPIO_PORTF_DIR_R   &=      ~0x11;
    GPIO_PORTA_DIR_R   |=       0xf0; /* port A output  (rows) */
    GPIO_PORTC_DIR_R   &=      ~0xf0;  /* port C input  (columns) */
    GPIO_PORTC_ODR_R    |=       0xf0;

    GPIO_PORTB_DEN_R   |=       0xff;
    GPIO_PORTE_DEN_R   |=       0x38;
    GPIO_PORTA_DEN_R   |=       0xf0;
    GPIO_PORTC_DEN_R   |=       0xf0;
    GPIO_PORTF_DEN_R   |=       0x13;

    GPIO_PORTF_PUR_R    =       0x11;
    GPIO_PORTC_PUR_R    =       0xf0;

    GPIO_PORTD_DIR_R   |=       0x04;
    GPIO_PORTD_DEN_R   |=       0x04;
    GPIO_PORTD_DIR_R   &=      ~0x08;
    GPIO_PORTD_DEN_R   |=       0x08;
}

unsigned char checkPressed(void)
{
GPIO_PORTA_DATA_R = 0; /* enable all rows */
int col = GPIO_PORTC_DATA_R  & 0xf0; /* read all columns */
if (col == 0xf0)
return 0; /* no key pressed */
else
return 1; /* a key is pressed */
}

unsigned char getKey(void)
{
    const unsigned char keymap[4][4] = {
    { '1', '2', '3', 'A'},
    { '4', '5', '6', 'B'},
    { '7', '8', '9', 'C'},
    { 'E', '0', 'F', 'D'},
    };
    if(checkPressed()==0) return 0;
    int col,row;
    while (1)
    {
        row = 0;
        GPIO_PORTA_DATA_R = 0xE0; /* enable row 0 */
        delayMs(2); /* wait for signal to settle */
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;
            row = 1;
            GPIO_PORTA_DATA_R = 0xD0; /* enable row 1 */
            delayMs(2); /* wait for signal to settle */
            col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;
            row = 2;
            GPIO_PORTA_DATA_R = 0xB0; /* enable row 2 */
            delayMs(2); /* wait for signal to settle */
            col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;
            row = 3;
            GPIO_PORTA_DATA_R = 0x70; /* enable row 3 */
            delayMs(2); /* wait for signal to settle */
            col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;
            return 0; /* if no key is pressed */
    }
    /* gets here when one of the rows has key pressed */
    if (col == 0xE0) return keymap[row][0]; /* key in column 0 */
    if (col == 0xD0) return keymap[row][1]; /* key in column 1 */
    if (col == 0xB0) return keymap[row][2]; /* key in column 2 */
    if (col == 0x70) return keymap[row][3]; /* key in column 3 */
    return 0; /* just to be safe */
}
void lightOn (unsigned char key)
{
    if(counter<4){
        delayMs(350);
        LCD_data(key);
        input[counter]=key;
        counter++;
    }
    if(counter==4){
        if(checkpass()){
            Unlock();
            showmessage(welcome,7);
        }else{
            blink();
            showmessage(wrong,10);
        }
        reset();
    }
}
bool checkpass(void){
  bool result = true;
  for(int i = 0;i<4;i++){
    if(input[i] != pass[i]){
        result = false;
    }
  }
  return result;
}
void Unlock(void){
    GPIO_PORTD_DATA_R |= 0x04;
    for(int i = 0;i<4;i++){
      delayMs(1000);
    }
    GPIO_PORTD_DATA_R &= ~0x04;
}
void showmessage(char message[],int size){
  clear();
  for(int i =0;i<size;i++){
    delayMs(350);
    LCD_data(message[i]);
  }
    delayMs(1000);
    delayMs(1000);
    delayMs(1000);
    delayMs(1000);
    delayMs(1000);
}





