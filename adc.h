//ADC header file//

sbit clk	=P1^0;
sbit din	=P1^2;
sbit dout	=P1^1;
sbit cs		=P1^3;

unsigned int read_adc(unsigned int channel)
{

	unsigned int temp=0;
	char i;
	cs=0; //chip enabled
	clk=0; din=1; clk=1;//start bit
	clk=0; din=1; clk=1;//start bit
	clk=0; din=1; clk=1;//D2(which is dont care)
	
	//selection od channel//
	switch(channel)
	{
		case 0: clk=0; din=0; clk=1;//D1 bit
				    clk=0; din=0; clk=1;//D0 bit
					  break;
		
		case 1: clk=0; din=0; clk=1;//D1 bit
				    clk=0; din=1; clk=1;//D0 bit
					  break;
		
		case 2: clk=0; din=1; clk=1;//D1 bit
				    clk=0; din=0; clk=1;//D0 bit
					  break;
		
		case 3: clk=0; din=1; clk=1;//D1 bit
				    clk=0; din=1; clk=1;//D0 bit
					  break;
		
		default:clk=0; din=0; clk=1;//D1 bit
				    clk=0; din=0; clk=1;//D0 bit
					  break;
	}
	
	clk=0; din=1; clk=1;//Tsamploe
	clk=0; din=1; clk=1;//Nulll bit
	
	
//reading 12 bit digital data from ADC//
	
	for(i=11;i>=0;i--)
	{
		clk=0;
		if(dout==1)
			temp |=(1<<i);
		clk=1;
	}
	cs=1;//chip disabled
	return temp;
}//main