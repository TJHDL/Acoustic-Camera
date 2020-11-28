#include"sccb_ctrl.h"
void sccb_start(void)
{
	CLOCK_HIGH();
	DATA_HIGH();
	SCCB_DELAY;
	DATA_LOW();
	SCCB_DELAY;
	CLOCK_LOW();
	SCCB_DELAY;
}

void sccb_end(void)
{
	DATA_LOW();
	SCCB_DELAY;
	CLOCK_HIGH();
	SCCB_DELAY;
	DATA_HIGH();
	SCCB_DELAY;
}

int sccb_sendbyte( u8 value )
{
	u8 tmp = value;
	u8  i=0,ack;

	for(i=0; i<8; i++)
	{
		if(tmp & 0x80 )//get the highest bit
				DATA_HIGH();
		else
				DATA_LOW();

		 SCCB_DELAY;
		 CLOCK_HIGH();
		 SCCB_DELAY;
		 CLOCK_LOW();
		 SCCB_DELAY;

		 tmp<<=1;
	 }
	//don't care bit
	 DATA_HIGH();
	 DATA_INPUT();
	 SCCB_DELAY;
	 CLOCK_HIGH();
	 // read ack 
	 ack = GET_DATA();
	 SCCB_DELAY;
	 CLOCK_LOW();
	 //wait for another operation
	 SCCB_DELAY;
	 DATA_OUTPUT();
	 //verify if there is a mistake
	 //printf("ack:%x",ack);
	 if(ack==1)
	 {
		 return -1;
	 }

	 return 0;
}


u8 sccb_readbyte( u8 addr)
{
	u8  i=0,data=0;

	DATA_HIGH();
	DATA_INPUT();

	for(i=0; i<8; i++)
	{
		CLOCK_HIGH();
		SCCB_DELAY;

		data <<= 1;
		if(GET_DATA())
			data |= 1;

		 SCCB_DELAY;
		 CLOCK_LOW();
		 SCCB_DELAY;
	 }
	//NA
	 DATA_OUTPUT();
	 DATA_HIGH();
	 SCCB_DELAY;
	 CLOCK_HIGH();
	 SCCB_DELAY;
	 CLOCK_LOW();
	 SCCB_DELAY;
	 DATA_HIGH();

	 return data;
}

int sccb_readdata(u8 addr, u8 *value)
{

	sccb_start();
	if(sccb_sendbyte(OV7725_WRITE_ADDR) != 0)
	{
		sccb_end();
		return -1;
	}

	if(sccb_sendbyte(addr) != 0)
	{
		sccb_end();
		return -1;
	}
	sccb_end();

	SCCB_DELAY;

	sccb_start();
	if(sccb_sendbyte(OV7725_READ_ADDR) != 0)
	{
		sccb_end();
		return -1;
	}
	*value = sccb_readbyte(addr);
	sccb_end();

	return 0;
}

int sccb_senddata(u8 addr,u8 value)
{
	sccb_start();
	int status = 0;
	
	status = sccb_sendbyte(OV7725_WRITE_ADDR);
	if(status){
		printf("ov7725 device no ack!\n");
		return status;
	}
	
	status = sccb_sendbyte(addr);
	if(status){
		printf("ov7725 regoffset no ack!\n");
		return status;
	}
	
	status = sccb_sendbyte(value);
	if(status){
		printf("send value no ack!\n");
		return status;
	}

	sccb_end();
	return 0;
}