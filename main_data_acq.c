#include<reg51.h>
//#include<stdio.h>
//#include<string.h>
#include"delay.h"
#include"uart.h"
#include"i2c.h"
#include"i2c_device.h"
//#include"lcd8bit.h"
#include"adc.h"
#include"support_file.h"


main()
{
	
	int cat;
	unsigned char temp[10]=0,s[10]={"Ankit"},j,i;

//	lcd_init();
	uart_init(9600);

	//-------------Setting the Values--------------------------//
	//setting RTC time 23:59:10//
	i2c_device_write(0xD0,0x2,0x71); //hour set time for 11 PM	//0111 0001
	//i2c_device_write(0xD0,0x2,0x51); //hour set time for 11AM		//0101 0001
	i2c_device_write(0xD0,0x1,0x59); //min
	i2c_device_write(0xD0,0x0,0x10); //sec
//
	i2c_device_write(0xD0,0x4,0x31); //date
	i2c_device_write(0xD0,0x5,0x12); //month
	i2c_device_write(0xD0,0x6,0x18); //year
//
	i2c_device_write(0xD0,0x3,0x2); //day
	
	
//////////////////////////////////////////////////////////
	 
	uart_init(9600);
//
	for(i=0;s[i];i++)
		i2c_device_write(0xA0,(0x1+i),s[i]);
		i2c_device_write(0xA0,(0x1+i),0);
		
	for(j=0;;j++)
	{
		temp[j]=i2c_device_read(0xA0,0x1+j);
		if(temp[j]==0)
			break;
	}
	uart_string("\r\n");
	uart_string(temp);

//////////////////////////////////////////////////////////
	
/*	cat=eeprom_pass();
	
	if(cat==2)
		{
			uart_string("\r\bSYSTEM BLOCK\r\n");
		while(1);
		}

	if(cat==1)
{*/
		while(1)
	{
		i2c_rtc();
		spi_ldr();
		spi_pot1();
		spi_pot2();
		i2c_temp();
		delay_ms(900);
		uart_string("\x1b[2J");//to clear the uart//

	}//while	
//if
}//main