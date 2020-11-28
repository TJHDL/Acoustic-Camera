################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sccb/sccb_ctrl.c \
../sccb/sccb_init.c 

OBJS += \
./sccb/sccb_ctrl.o \
./sccb/sccb_init.o 

C_DEPS += \
./sccb/sccb_ctrl.d \
./sccb/sccb_init.d 


# Each subdirectory must supply rules for building sources it contributes
sccb/%.o: ../sccb/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../project_final_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


