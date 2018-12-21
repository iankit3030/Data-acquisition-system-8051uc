////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int ldr,pot1,pot2,t4;

sbit LED=P2^7;
void spi_ldr()
{
			ldr=read_adc(2);
				
			ldr=(ldr*100,)/4095;
			ldr=100-ldr;

			uart_string("\r\b");
			uart_string("Light Intencity is:");
			uart_integer(ldr);
			uart_tx('%');

			if(ldr<40)
			LED=0;
			else
			LED=1;
					
		uart_string("\r\n");
}//spi_ldr

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void i2c_rtc()
{
		unsigned char temp,op;
	
//------Reading RTC time------------------//

//-------------Hour--------------------------//
		//uart_string("\r");
		uart_string("Time:- ");
		temp=i2c_device_read(0xD0,0x2);
		op=temp&~0xDF;	//temp&~(1101 1111)
		uart_tx((temp&0x1f)/16+48);	//temp&0001 1111
		uart_tx((temp&0x1f)%16+48);	//temp&0001 1111		
		uart_tx(':');
	
//-------------Minute--------------------------//
		temp=i2c_device_read(0xD0,0x1);
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
		uart_tx(':');
	
//-------------Second--------------------------//
		temp=i2c_device_read(0xD0,0x0);
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
	
//-------------AM or PM--------------------------//
		if((op>>5)==1) //check 5th bit
			uart_string("PM");
		else
			uart_string("AM");
	
//-------------Date--------------------------//
		uart_string("\r\n");
		uart_string("Date:-");
		temp=i2c_device_read(0xD0,0x4);
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
		uart_tx('/');
	
//-------------Month--------------------------//		
		temp=i2c_device_read(0xD0,0x5);
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
		uart_tx('/');
	
//-------------Year--------------------------//		
		temp=i2c_device_read(0xD0,0x6);
		uart_string("20");
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
	
//-------------Day--------------------------//		
		uart_string("\r\n");
		temp=i2c_device_read(0xD0,0x3);
		uart_string("Day:-");
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
		uart_string(" ");
		
		uart_string("\r\n");
}//main_rtc

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void spi_pot1()
{
   		pot1=read_adc(0);
		uart_string("\r\nPot1 data=");

		uart_integer(pot1);
		uart_string("=");
		uart_float((pot1*5.)/4095);
		uart_string("V");
		uart_string("\r\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void spi_pot2()
{

   	pot2=read_adc(1);
		uart_string("\r\nPot2 data=");

		uart_integer(pot2);
		uart_string("=");
		pot2=(pot2*5.)/4095;
		uart_float(pot2);
		uart_string("V");
		uart_string("\r\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*int eeprom_pass()
{
	unsigned char i,j,temp[10]=0,p[10]=0,ch,new[10];
	for(j=0;;j++)
	{
		temp[j]=i2c_device_read(0xA0,0x1+j);
		if(temp[j]==0)
			break;
	}
	uart_string("\r\nEnter the password\r\n");
	for(i=0;;i++)
	{
	  p[i]=uart_rx();
   	  uart_tx(p[i]);
	  if(p[i]=='\r')
	  	break;
	}
	p[i]=0;

	if((strcmp(temp,p))==0)
	//if(i>0)
	{
				uart_string("\r\nPassword match");
		
	}		
	else
	{
		uart_string("\r\npassword not matched\r\n");
		return 2;
	}
}*/
/////////////////////////////////////////////////////////////////////////////////////////

void i2c_temp()
{
	unsigned int t1,t2,t3;
	uart_string("\r\nTemperature=");
	
	i2c_device_write(0x90,0xAC,0x02); 
	i2c_device_write(0x90,0xA1,0x28); 
	i2c_device_write(0x90,0xA2,0x0A); 
	i2c_device_write(0x90,0xEE,0x0);

	t1=i2c_device_read(0x90,0xAA);
	t2=i2c_device_read(0x90,0xA8);
	t3=i2c_device_read(0x90,0xA9);

	t4=(t1-0.25+((t3-t2)/t3));
	uart_integer(t4);
	uart_string(" celcius\r\n");
	
}
/////////////////////////////////////////////////////////////////////////////////////

