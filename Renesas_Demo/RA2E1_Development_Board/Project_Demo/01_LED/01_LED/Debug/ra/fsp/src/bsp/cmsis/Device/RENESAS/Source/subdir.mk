################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c \
../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.c 

C_DEPS += \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.d \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.d 

OBJS += \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.o \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.o 

SREC += \
01_LED.srec 

MAP += \
01_LED.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/%.o: ../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/src" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/src/key" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/src/gpt" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/src/led" -I"." -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/ra/fsp/inc" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/ra/fsp/inc/api" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/ra/fsp/inc/instances" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/ra_gen" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/ra_cfg/fsp_cfg/bsp" -I"C:/Users/80023166/Desktop/RA2E1_Development_Board/Project_Demo/01_LED/01_LED/ra_cfg/fsp_cfg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

