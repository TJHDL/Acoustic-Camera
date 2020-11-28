#include "sccb_init.h"

static XGpioPs psGpioInstancePtr;
int EMIO_SCCB_init(void)
{
	XGpioPs_Config* GpioConfigPtr;
	int xStatus;

	GpioConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	if(GpioConfigPtr == NULL)
	return XST_FAILURE;

	xStatus = XGpioPs_CfgInitialize(&psGpioInstancePtr,GpioConfigPtr,GpioConfigPtr->BaseAddr);
	if(XST_SUCCESS != xStatus)
		print("EMIO INIT FAILED \n\r");

	XGpioPs_SetDirectionPin(&psGpioInstancePtr, SIOC_PIN,DIRECTION_OUTPUT);
	XGpioPs_SetDirectionPin(&psGpioInstancePtr, SIOD_PIN,DIRECTION_OUTPUT);

	XGpioPs_SetOutputEnablePin(&psGpioInstancePtr, SIOC_PIN,1);
	XGpioPs_SetOutputEnablePin(&psGpioInstancePtr, SIOD_PIN,1);
	return xStatus;
}


void CLOCK_HIGH(void)
{
	XGpioPs_WritePin(&psGpioInstancePtr,SIOC_PIN, 1);
}

void CLOCK_LOW(void)
{
	XGpioPs_WritePin(&psGpioInstancePtr,SIOC_PIN, 0);
}

int GET_DATA(void)
{
	return XGpioPs_ReadPin(&psGpioInstancePtr,SIOD_PIN);
}

void DATA_INPUT(void)
{
	XGpioPs_SetDirectionPin(&psGpioInstancePtr, SIOD_PIN,DIRECTION_INPUT);//
}

void DATA_OUTPUT(void)
{
	XGpioPs_SetDirectionPin(&psGpioInstancePtr, SIOD_PIN,DIRECTION_OUTPUT);//
}

void DATA_HIGH(void)
{
	XGpioPs_WritePin(&psGpioInstancePtr,SIOD_PIN, 1);
}

void DATA_LOW(void)
{
	XGpioPs_WritePin(&psGpioInstancePtr,SIOD_PIN,0);
}
