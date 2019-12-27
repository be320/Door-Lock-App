#include "lib.h"

int main()
{
    int state =0;
    init();
    LCD_start();
    LCD_command(1);
    LCD_command(2);
    while(1){
      state = GPIO_PORTD_DATA_R & 0x08;
        if (checkPressed()==1)
        { 
            lightOn(getKey());
        }   
        
        if(state == 0x08)
        {
         Unlock();
        }
}
  return 0;
}
