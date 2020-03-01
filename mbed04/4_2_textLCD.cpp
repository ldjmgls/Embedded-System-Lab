#include "mbed.h"
#include "TextLCD.h"

DigitalOut led(LED_RED);
TextLCD lcd(D2, D3, D4, D5, D6, D7);
int i;

int main()
{
      lcd.printf("106061224\n");
      while(true) {
            led = !led;                   // toggle led
            //lcd.locate(5,1);
            for (i=30; i>=0; i--) {
                  lcd.locate(14,1);
                  lcd.printf("%2d",i);    //conuter display (%i=%d)
                  wait(1);
            }
      }
}