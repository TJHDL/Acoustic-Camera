
#ifndef SCCB_CTRL_H_
#define SCCB_CTRL_H_

#include<stdio.h>
#include"sccb_init.h"
#include "sleep.h"
#define OV7725_WRITE_ADDR 	0x42
#define OV7725_READ_ADDR 	0x43

#define SCCB_DELAY	usleep(10)// 100khz -> 10us

void sccb_start(void);
void sccb_end(void);
int sccb_sendbyte( u8 value );
u8 sccb_readbyte( u8 addr);
int sccb_readdata(u8 addr, u8 *value);
int sccb_senddata(u8 addr,u8 value);

#endif /* SCCB_CTRL_H_ */
