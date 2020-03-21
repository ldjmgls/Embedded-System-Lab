#include "mbed.h"

RawSerial pc(USBTX, USBRX);    // computer to mbed board
RawSerial esp(D1, D0);         // mbed board to target board

int
main()
{
   pc.baud(115200);
   esp.baud(115200);
   wait(0.1);
   pc.printf("\r\n########### ready ###########\r\n");
   esp.printf("AT\r\n");    // send AT to esp
   char str[50];
   int i=0;

   while(1) {
      if(pc.readable()){    // if we type somethong on pc
               char c = pc.getc();
               if(c!='\r'&&c!='\n'){
                  pc.printf("%c", c);
                  str[i++] = c;
               }
               else{        // enter at last
                  pc.printf("(%d)\r\n", c);
                  str[i] = 0;
                  i=0;
                  esp.printf("%s\r\n", str);    // send full string to esp 
               }
      }
      while(esp.readable()){    // if esp receive something
            char c = esp.getc();    // c = reply from esp
            pc.printf("%c",c);      // print reply 

      }
      wait(.001);
   }
}