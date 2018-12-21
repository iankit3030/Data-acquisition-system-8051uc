//LCD8bit.h//
sfr LCD_PORT=0x80; //data line D0 to D1
sbit RS=P3^4;
sbit RW=P3^5;
sbit EN=P3^6;

////////////////////////////////////////////
void lcd_cmd(unsigned char c)
{
 LCD_PORT=c;
 RS=0;
 RW=0;
 EN=1;
 delay_ms(2);
 EN=0;
}
////////////////////////////////////////////
void lcd_data(unsigned char d)
{
LCD_PORT=d;
RS=1;
RW=0;
EN=1;
delay_ms(2);
EN=0;
}
////////////////////////////////////////////
void lcd_init()
{
 lcd_cmd(0x2);
 lcd_cmd(0x38);
 lcd_cmd(0xE);
 lcd_cmd(0x6);
 lcd_cmd(0x1);
}
////////////////////////////////////////////
void lcd_string(char *s)
{
 while(*s)
 {
  lcd_data(*s++);
 }
}
////////////////////////////////////////////////
void lcd_integer(int n)
{
 char buf[7];
 sprintf(buf,"%d",n);
 lcd_string(buf);
}
///////////////////////////////////////////////
