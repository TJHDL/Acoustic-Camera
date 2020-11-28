#ifndef _OV7670_H
#define _OV7670_H

#include "xil_types.h"

#define DEV_WRITE_ADDR 0x43
#define DEV_READ_ADDR 0x42

typedef struct
{
    u8 Address;
    u8 Value;
} Register_Info;


int OV7670_Init();
#endif
