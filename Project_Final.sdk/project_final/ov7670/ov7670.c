#include<stdio.h>
#include "OV7670.h"
#include "sccb_ctrl.h"

#define OVSLEEP(time) usleep(time*1000)

Register_Info Sensor_Cfg[]={

	{0x11, 0x80},
	{0x6b, 0x0a},
	{0x2a, 0x00},
	{0x2b, 0x00},
	{0x92, 0x00},
	{0x93, 0x00},
	{0x3b, 0x0a},

	{0x12, 0x04},
	{0x40, 0x10},
	{0x8c, 0x00},

	{0x3a, 0x04},
	{0x67, 0xc0},
	{0x68, 0x80},
	//flip and mirror
	{0x1e, 0x31},
	//hstart hstop 
	{0x18, 0x02},
	{0x17, 0x14},
	//vstart vstop
	{0x32, 0x80},
	{0x19, 0x02},
	{0x1a, 0x7a},
	{0x03, 0x0a},

	{0x15, 0x02},
	{0xb0, 0x84},
	//{0x70, 0x80},
	{0x70, 0x00},
	//{0x71, 0x80},
	{0x71, 0x00},

	//filter
	{0x13, 0xe7},
	{0x9d, 0x98},//50 hz
	{0x9e, 0x7f},//60 hz
	{0xa5, 0x02},//3 step for 50hz
	{0xab, 0x03},//4 step for 60hz
	{0x3b, 0x02},//auto dectect

	//SWB
	{0x13, 0xe7},
	{0x6f, 0x9f},
	
	// //home
	// {0x13, 0xe5}, //AWB off	
	// {0x01, 0x96},
	// {0x02, 0x40},

	// //Sunny
	// {0x13, 0xe5}, //AWB off
	// {0x01, 0x5a}, 
	// {0x02, 0x5c}, 

	// //Cloudy
	// {0x13, 0xe5}, //AWB off
	// {0x01, 0x58}, 
	// {0x02, 0x60}, 

	// //Office
	// {0x13, 0xe5}, //AWB off
	// {0x01, 0x84}, 
	// {0x02, 0x4c}, 


	// //auto wb control
	// {0x43, 0xf0},
	// {0x45, 0x34},
	// {0x46, 0x58},
	// {0x47, 0x28},
	// {0x48, 0x3a},

	// {0x59, 0x88},
	// {0x5a, 0x88},
	// {0x5b, 0x44},
	// {0x5c, 0x67},
	// {0x5d, 0x49},
	// {0x53, 0x0e},
	
	// {0x6c, 0x0a},
	// {0x6d, 0x55},
	// {0x6e, 0x11},
	// {0x6f, 0x9f},

	// {0x00, 0x00},
	// {0x14, 0x20},
	// {0x24, 0x75},
	// {0x25, 0x63},
	// {0x26, 0xa5},
	
	// //agc/aec
	// //{0xaa, 0x94},

	// {0x9f, 0x78},
	// {0xa0, 0x68},
	// {0xa6, 0xdf},	
	// {0xa7, 0xdf},
	// {0xa8, 0xf0},
	// {0xa9, 0x90},
	// //end of awbc 1


	//{0x02, 0x80},//RED GAIN
	//{0x01, 0x80},//BLUE GAIN
	//{0x6a, 0x00},//GREEN GAIN
	//{0x0f, 0x4b},
	//{0x28, 0x88},

	//brightness
	//{0x55, 0x30},//+2
	{0x55, 0x18},//+1
	//{0x55, 0x00},//+0
	//{0x55, 0x98},//-1
	//{0x55, 0xb0},//-2

	//contrast
	//{0x56, 0x60},//+2
	{0x56, 0x50},//+1
	//{0x56, 0x40},//+0
	//{0x56, 0x38},//-1
	//{0x56, 0x30},//-2

	// //Saturation + 2
	// {0x4f, 0xc0},
	// {0x50, 0xc0},
	// {0x51, 0x00},
	// {0x52, 0x33},
	// {0x53, 0x8d},
	// {0x54, 0xc0},
	// {0x58, 0x9e},

	// //Saturation + 1
	// {0x4f, 0x99},
	// {0x50, 0x99},
	// {0x51, 0x00},
	// {0x52, 0x28},
	// {0x53, 0x71},
	// {0x54, 0x99},
	// {0x58, 0x9e},

	//Saturation 0
	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},
	{0x58, 0x9e},

	// //Saturation -1
	// {0x4f, 0x66},
	// {0x50, 0x66},
	// {0x51, 0x00},
	// {0x52, 0x1b},
	// {0x53, 0x4b},
	// {0x54, 0x66},
	// {0x58, 0x9e},
	// //Saturation - 2
	// {0x4f, 0x40},
	// {0x50, 0x40},
	// {0x51, 0x00},
	// {0x52, 0x11},
	// {0x53, 0x2f},
	// {0x54, 0x40},
	// {0x58, 0x9e},



};
u8 OV7670_REG_NUM = sizeof(Sensor_Cfg) / sizeof(Sensor_Cfg[0]);


int OV7670_Init(){
    printf("ov7670 initialization!\n");
    OVSLEEP(50);
    int i = 0;
    u8 veri = 0,pid = 0;

    //reset ov7670
    while(sccb_senddata(0x12,0x80)){
        i++;
        if(i>=20){
            printf("reset ov7670 error!\n");
            return XST_FAILURE;
        }
    }
    OVSLEEP(50);

    //verify the pid and verison
    if(sccb_readdata(0x0a,&pid)){
        printf("read pid error\n");;
        return XST_FAILURE;
    }

    if(pid != 0x76)    printf("pid wrong!\n");
    else printf("get pid:%x, verify success!\n",pid);

    sccb_readdata(0x0b,&veri);
    printf("get ver:%x, verify success!\n",veri);

    if(pid == 0x76){
        for(int i = 0; i < OV7670_REG_NUM; i++){
            if(sccb_senddata(Sensor_Cfg[i].Address,Sensor_Cfg[i].Value)){
                printf("0v7670 reg: 0x%x write failed!\n",Sensor_Cfg[i].Address);
            }
        }
    }else
    {
        return -1;
    }


    printf("0v7670 init success!\n");
    return 0;
}