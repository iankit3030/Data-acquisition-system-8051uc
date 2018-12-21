//UART Header file//

//------UART Initiliastion------//
void uart_init(unsigned int baud)
{
	SCON=0x50;
	TMOD=0x20;
	switch(baud)
	{
	case 7200	:TH1=252;	break;
	case 9600	:TH1=253;	break;
	case 28800	:TH1=255;	break;
	case 576000	:TH1=255;	PCON=0x80;	break;
	default	:TH1=253;
	}
TR1=1;	
}


//----UART Transmitter-----------//
void uart_tx(unsigned char ch)
{
	SBUF=ch;
	while(TI==0);
	TI=0;
}

//----UART Receiver-----------//
unsigned char uart_rx()
{
	while(RI==0);
	RI=0;
	return SBUF;
}

//------string-------------//
void uart_string(char *s)
{
	
	while(*s)
		uart_tx(*s++);
}

//-------integer--------//
void uart_integer(int n)
{
unsigned char x=5,a[5];
if(n<0)
{
uart_tx('-');
n=-n;
}
if(n==0) uart_tx(n+48);
while(n)
{
a[--x] = n%10+48;
n/=10;
}
uart_string(&a[x]);
}  

//-------float--------//
void uart_float(float f)
{
	int n = f;
	if(f<0)
	{
	 uart_tx('-');
	 n=-n;
	 f=-f;
	}
	uart_integer(n);
	uart_tx('.');
	uart_integer((f-n)*100);
}