//i2c_device header file//
//i2c byte write frame//
void i2c_device_write(unsigned char sa,unsigned char mr,unsigned char d)
{
 	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(mr);
	i2c_ack();
	i2c_write(d);
	i2c_ack();
	i2c_stop();
	delay_ms(10);
}

//i2c byte read/random read frame//
unsigned char i2c_device_read(unsigned char sa,unsigned char mr)
{
	unsigned char temp;
	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(mr);
	i2c_ack();
	i2c_start();
	i2c_write(sa|0x1);
	i2c_ack();
	temp=i2c_read();
	i2c_noack();
	i2c_stop();
	return temp;
}