#include "LCD.h"

I2C _i2c(D14,D15);
char _slaveAddress = 0x4E;
char _lcd_bus;

void display_to_LCD(int value)
{
      _lcd_bus |= LCD_BUS_I2C_RS;    // Set RS bit
      _i2c.write(_slaveAddress, &_lcd_bus, 1);
      wait_us(1);

      _writeByte(value);
      wait_us(40);

}

//initialise LCD function
void LCD_init(void)
{
      _i2c.frequency(100000);
      wait_ms(20);

      //function mode
      // Change to 4-bit mode (MSN), the LSN is undefined dummy
      _lcd_bus |= LCD_BUS_I2C_E;     // Set E bit
      _i2c.write(_slaveAddress, &_lcd_bus, 1);

      _setDataBits(0x2);
      _i2c.write(_slaveAddress, &_lcd_bus, 1); // Low nibble of value on D4..D7
      wait_us(1); // Data setup time

      _lcd_bus &= ~LCD_BUS_I2C_E;    // Reset E bit
      _i2c.write(_slaveAddress, &_lcd_bus, 1);

      wait_us(40);            // most instructions take 40us

      int _function = 0x08;
      _writeCommand(0x20 | _function);
      _writeCommand(0x02);    // Cursor Home, DDRAM Address to Origin
      wait_ms(10);

      // display mode
      _writeCommand(0x06);
      _writeCommand(0x14);

      _writeCommand(0x0F); // display on, cursor on,  blink on


      // clear
      _writeCommand(0x01);    // clear
      wait_ms(20);

      // _writeCommand(0x80);

      //set cursor blink (0x1)
      // _writeCommand(0x0D);

      // set backlight
      //     _lcd_bus |= LCD_BUS_I2C_BL;
      //     _i2c.write(_slaveAddress, &_lcd_bus, 1);

}


void _setDataBits(int value) {

      //Clear all databits
      _lcd_bus &= ~LCD_BUS_I2C_MSK;

      // Set bit by bit to support any mapping of expander portpins to LCD pins
      if (value & 0x01)   {  _lcd_bus |= LCD_BUS_I2C_D4;  }  // Set Databit

      if (value & 0x02)   {  _lcd_bus |= LCD_BUS_I2C_D5;  }  // Set Databit

      if (value & 0x04)   {  _lcd_bus |= LCD_BUS_I2C_D6;  }  // Set Databit

      if (value & 0x08)   {  _lcd_bus |= LCD_BUS_I2C_D7;  }  // Set Databit

}

void _writeByte(int value) {
      char data[6];
      _lcd_bus |= LCD_BUS_I2C_E;     // Set E bit
      _setDataBits(value >> 4);       // set data high
      data[0] = _lcd_bus;

      _lcd_bus &= ~LCD_BUS_I2C_E;              // clear E
      data[1] = _lcd_bus;

      _lcd_bus |= LCD_BUS_I2C_E;     // Set E bit
      _setDataBits(value);            // set data low
      data[2] = _lcd_bus;

      _lcd_bus &= ~LCD_BUS_I2C_E;              // clear E
      data[3] = _lcd_bus;

      // write the packed data to the I2C portexpander
      _i2c.write(_slaveAddress, data, 4);
}

void _writeCommand(int command) {
      _lcd_bus &= ~LCD_BUS_I2C_RS;   // Reset RS bit
      _i2c.write(_slaveAddress, &_lcd_bus, 1);
      wait_us(1);
      _writeByte(command);
      wait_us(40); // most instructions take 40us
}