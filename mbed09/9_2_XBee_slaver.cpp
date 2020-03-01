#include "mbed.h"

Serial pc(USBTX, USBRX);
Serial xbee(D12, D11);
char str[50];

void reply_message(char *xbee_reply, char *message){
  xbee_reply[0] = xbee.getc();
  xbee_reply[1] = xbee.getc();
  xbee_reply[2] = xbee.getc();
  pc.printf("reply\r\n");
  if(xbee_reply[1] == 'O' && xbee_reply[2] == 'K'){
   pc.printf("%s\r\n", message);
   xbee_reply[0] = '\0';
   xbee_reply[1] = '\0';
   xbee_reply[2] = '\0';
  }
}

void check_addr(char *xbee_reply, char *message){
  xbee_reply[0] = xbee.getc();
  xbee_reply[1] = xbee.getc();
  xbee_reply[2] = xbee.getc();
  pc.printf("%s = %c%c\r\n", message, xbee_reply[1], xbee_reply[2]);
  xbee_reply[0] = '\0';
  xbee_reply[1] = '\0';
  xbee_reply[2] = '\0';
}


int main(){
  int i=0;
  pc.baud(9600);

  char xbee_reply[3];
  char message[50];

  // XBee setting
  xbee.baud(9600);
  xbee.printf("+++");
  xbee_reply[0] = xbee.getc();
  xbee_reply[1] = xbee.getc();
  if(xbee_reply[0] == 'O' && xbee_reply[1] == 'K'){
   pc.printf("enter AT mode.\r\n");
   xbee_reply[0] = '\0';
   xbee_reply[1] = '\0';
  }
  xbee.printf("ATMY 0x50\r\n");
  reply_message(xbee_reply, "set MY : 0x50");

  xbee.printf("ATDL 0x51\r\n");
  reply_message(xbee_reply, "set DL : 0x51");

  xbee.printf("ATWR\r\n");
  reply_message(xbee_reply, "write config");

  xbee.printf("ATMY\r\n");
  check_addr(xbee_reply, "MY");

  xbee.printf("ATDL\r\n");
  check_addr(xbee_reply, "DL");

  xbee.printf("ATCN\r\n");
  reply_message(xbee_reply, "exit AT mode");

  // start
  pc.printf("Slave:\r\n");

  while(1){
    while(xbee.readable()){
      char c = xbee.getc();
      if(c!='\n'&&c!='\r'){
        str[i] = c;
        i++;
        str[i] = '\0';
      }
      else{
        pc.printf("%s\r\n", str);
        str[0] = '\0';
        i = 0;
      }
    }
    wait(0.001);
  }
}