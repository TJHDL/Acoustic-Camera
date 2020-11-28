#ifndef SCCB_INIT_H_
#define SCCB_INIT_H_

#include"xgpiops.h"

#define SIOD_PIN 	54 //data	
#define SIOC_PIN 	55 //clk


#define DIRECTION_INPUT 0
#define DIRECTION_OUTPUT 1


int EMIO_SCCB_init(void);
void CLOCK_HIGH(void);
void CLOCK_LOW(void);
int GET_DATA(void);
void DATA_INPUT(void);
void DATA_OUTPUT(void);
void DATA_HIGH(void);
void DATA_LOW(void);

#endif /* SCCB_INIT_H_ */
