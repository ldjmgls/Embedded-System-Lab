#include "mbed.h"
#include "uLCD_4DGL.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "iostream"
#include "math.h"

#define UINT14_MAX        16383
// FXOS8700CQ I2C address
#define FXOS8700CQ_SLAVE_ADDR0 (0x1E<<1) // with pins SA0=0, SA1=0
#define FXOS8700CQ_SLAVE_ADDR1 (0x1D<<1) // with pins SA0=1, SA1=0
#define FXOS8700CQ_SLAVE_ADDR2 (0x1C<<1) // with pins SA0=0, SA1=1
#define FXOS8700CQ_SLAVE_ADDR3 (0x1F<<1) // with pins SA0=1, SA1=1
// FXOS8700CQ internal register addresses
#define FXOS8700Q_STATUS 0x00
#define FXOS8700Q_OUT_X_MSB 0x01
#define FXOS8700Q_OUT_Y_MSB 0x03
#define FXOS8700Q_OUT_Z_MSB 0x05
#define FXOS8700Q_M_OUT_X_MSB 0x33
#define FXOS8700Q_M_OUT_Y_MSB 0x35
#define FXOS8700Q_M_OUT_Z_MSB 0x37
#define FXOS8700Q_WHOAMI 0x0D
#define FXOS8700Q_XYZ_DATA_CFG 0x0E
#define FXOS8700Q_CTRL_REG1 0x2A
#define FXOS8700Q_M_CTRL_REG1 0x5B
#define FXOS8700Q_M_CTRL_REG2 0x5C
#define FXOS8700Q_WHOAMI_VAL 0xC7

#define waveformLength (128)
#define lookUpTableDelay (10)
#define bufferLength (32)

I2C i2c( PTD9,PTD8);
Serial pc(USBTX, USBRX);
AnalogOut Aout(DAC0_OUT);
uLCD_4DGL uLCD(D1, D0, D2);

InterruptIn keyboard0(D2);
InterruptIn keyboard1(D3);
InterruptIn keyboard2(D4);
InterruptIn keyboard3(D5);
InterruptIn keyboard4(D6);
InterruptIn keyboard5(D7);
InterruptIn keyboard6(D8);
InterruptIn keyboard7(D9);
InterruptIn keyboard8(D10);
InterruptIn keyboard9(D11);
InterruptIn keyboard10(D12);
InterruptIn keyboard11(D13);
InterruptIn button(SW2);

EventQueue queue(64 * EVENTS_EVENT_SIZE);
Thread t;
int idC = 0, idC1 = 0;
int idD = 0, idD1 = 0;
int idE = 0, idF = 0;
int idF1 = 0, idG = 0;
int idG1 = 0, idA = 0;
int idA1 = 0, idB = 0;

float waveform[waveformLength];
char serialInBuffer[bufferLength];
int serialCount = 0;
int m_addr = FXOS8700CQ_SLAVE_ADDR1;
double angle;

double acc();
void FXOS8700CQ_readRegs(int addr, uint8_t * data, int len);
void FXOS8700CQ_writeRegs(uint8_t * data, int len);

void loadWaveform(void)
{
  char byteIn;
  int i = 0;
  serialCount = 0;
  Aout = 0;
  pc.printf("Loading Waveform ...\r\n");
  while(i < waveformLength)
  {
    if(pc.readable())
    {
      serialInBuffer[serialCount] = pc.getc();
      serialCount++;
      if(serialCount == 5)
      {
        serialInBuffer[serialCount] = '\0';
        waveform[i] = (float) atof(serialInBuffer);
        serialCount = 0;
        i++;
      }
    }
  }
  pc.printf("Waveform Loaded\r\n");
}

void playNote(int freq)
{
  int i = freq;
  int j = waveformLength;
  int waitTime = (1000000/waveformLength/freq - lookUpTableDelay) << 0;
  double r_angle, n;
  int sound_lv;
 
  r_angle = acc();
  sound_lv = r_angle/30;
  switch (sound_lv) {
    case 0: n=0.005;
            break;
    case 1: n=0.01;
            break;
    case 2: n=0.05;
            break;
    case 3: n=0.1;
            break;
    case 4: n=0.5;
            break;        
    case 5: n=1;
            break;
    default: n=0.005;
  } 

  uLCD.cls();
  switch (freq) {
    case 131: uLCD.printf("Note C\n");
              break;
    case 139: uLCD.printf("Note C#\n");
              break;
    case 147: uLCD.printf("Note D\n");
              break;
    case 156: uLCD.printf("Note D#\n");
              break;
    case 165: uLCD.printf("Note E\n");
              break;          
    case 175: uLCD.printf("Note F\n");
              break;  
    case 185: uLCD.printf("Note F#\n");
              break;  
    case 196: uLCD.printf("Note G\n");
              break;  
    case 208: uLCD.printf("Note G#\n");
              break;  
    case 220: uLCD.printf("Note A\n");
              break;  
    case 233: uLCD.printf("Note A#\n");
              break;  
    case 247: uLCD.printf("Note B\n");
              break;   
  }
  uLCD.printf("Freq = %d Hz\n", freq);
  uLCD.locate(0,0);

  while(i--)
  {
    j = waveformLength;
    while(j--)
    {
      Aout = waveform[j]*n;
      wait_us(waitTime);
    }
  }
}

void loadWaveformHandler(void) {queue.call(loadWaveform);}

void playNoteC(void) {idC = queue.call_every(500, playNote, 131);}
void playNoteC1(void) {idC1 = queue.call_every(500, playNote, 139);}
void playNoteD(void) {idD = queue.call_every(500, playNote, 147);}
void playNoteD1(void) {idD1 = queue.call_every(500, playNote, 156);}
void playNoteE(void) {idE = queue.call_every(500, playNote, 165);}
void playNoteF(void) {idF = queue.call_every(500, playNote, 175);}
void playNoteF1(void) {idF1 = queue.call_every(500, playNote, 185);}
void playNoteG(void) {idG = queue.call_every(500, playNote, 196);}
void playNoteG1(void) {idG1 = queue.call_every(500, playNote, 208);}
void playNoteA(void) {idA = queue.call_every(500, playNote, 220);}
void playNoteA1(void) {idA1 = queue.call_every(500, playNote, 233);}
void playNoteB(void) {idB = queue.call_every(500, playNote, 247);}


void stopPlayNoteC(void) {queue.cancel(idC);}
void stopPlayNoteC1(void) {queue.cancel(idC1);}
void stopPlayNoteD(void) {queue.cancel(idD);}
void stopPlayNoteD1(void) {queue.cancel(idD1);}
void stopPlayNoteE(void) {queue.cancel(idE);}
void stopPlayNoteF(void) {queue.cancel(idF);}
void stopPlayNoteF1(void) {queue.cancel(idF1);}
void stopPlayNoteG(void) {queue.cancel(idG);}
void stopPlayNoteG1(void) {queue.cancel(idG1);}
void stopPlayNoteA(void) {queue.cancel(idA);}
void stopPlayNoteA1(void) {queue.cancel(idA1);}
void stopPlayNoteB(void) {queue.cancel(idB);}

int main(void)
{
  t.start(callback(&queue, &EventQueue::dispatch_forever));
  button.rise(queue.event(loadWaveformHandler));
  keyboard0.rise(queue.event(playNoteC));
  keyboard1.rise(queue.event(playNoteC1));
  keyboard2.rise(queue.event(playNoteD));
  keyboard3.rise(queue.event(playNoteD1));
  keyboard4.rise(queue.event(playNoteE));
  keyboard5.rise(queue.event(playNoteF));
  keyboard6.rise(queue.event(playNoteF1));
  keyboard7.rise(queue.event(playNoteG));
  keyboard8.rise(queue.event(playNoteG1));
  keyboard9.rise(queue.event(playNoteA));
  keyboard10.rise(queue.event(playNoteA1));
  keyboard11.rise(queue.event(playNoteB));
  
  keyboard0.fall(queue.event(stopPlayNoteC));
  keyboard1.fall(queue.event(stopPlayNoteC1));
  keyboard2.fall(queue.event(stopPlayNoteD));
  keyboard3.fall(queue.event(stopPlayNoteD1));
  keyboard4.fall(queue.event(stopPlayNoteE));
  keyboard5.fall(queue.event(stopPlayNoteF));
  keyboard6.fall(queue.event(stopPlayNoteF1));
  keyboard7.fall(queue.event(stopPlayNoteG));
  keyboard8.fall(queue.event(stopPlayNoteG1));
  keyboard9.fall(queue.event(stopPlayNoteA));
  keyboard10.fall(queue.event(stopPlayNoteA1));
  keyboard11.fall(queue.event(stopPlayNoteB));

  loadWaveform();
}

double acc(void) {
  
  pc.baud(115200);

  uint8_t who_am_i, data[2], res[6];
  int16_t acc16;
  double T[3];

  // Enable the FXOS8700Q
   FXOS8700CQ_readRegs( FXOS8700Q_CTRL_REG1, &data[1], 1);
   data[1] |= 0x01;
   data[0] = FXOS8700Q_CTRL_REG1;
   FXOS8700CQ_writeRegs(data, 2);

   // Get the slave address
   FXOS8700CQ_readRegs(FXOS8700Q_WHOAMI, &who_am_i, 1);

   pc.printf("Here is %x\r\n", who_am_i);
   //while (true) {

      FXOS8700CQ_readRegs(FXOS8700Q_OUT_X_MSB, res, 6);

      acc16 = (res[0] << 6) | (res[1] >> 2);
      if (acc16 > UINT14_MAX/2)
         acc16 -= UINT14_MAX;
      T[0] = ((float)acc16) / 4096.0f;

      acc16 = (res[2] << 6) | (res[3] >> 2);
      if (acc16 > UINT14_MAX/2)
         acc16 -= UINT14_MAX;
      T[1] = ((float)acc16) / 4096.0f;

      acc16 = (res[4] << 6) | (res[5] >> 2);
      if (acc16 > UINT14_MAX/2)
         acc16 -= UINT14_MAX;
      T[2] = ((float)acc16) / 4096.0f;

      angle = acos(T[2])*180/3.14159265;

      //wait(1.0);
      return angle; 
}

void FXOS8700CQ_readRegs(int addr, uint8_t * data, int len) {
   char t = addr;
   i2c.write(m_addr, &t, 1, true);
   i2c.read(m_addr, (char *)data, len);
}

void FXOS8700CQ_writeRegs(uint8_t * data, int len) {
   i2c.write(m_addr, (char *)data, len);
}