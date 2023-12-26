################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/adc.c \
../Drivers/clock.c \
../Drivers/lpit.c \
../Drivers/lpspi.c \
../Drivers/lpuart.c \
../Drivers/nvic.c \
../Drivers/port.c \
../Drivers/sevenseg.c \
../Drivers/systick.c 

OBJS += \
./Drivers/adc.o \
./Drivers/clock.o \
./Drivers/lpit.o \
./Drivers/lpspi.o \
./Drivers/lpuart.o \
./Drivers/nvic.o \
./Drivers/port.o \
./Drivers/sevenseg.o \
./Drivers/systick.o 

C_DEPS += \
./Drivers/adc.d \
./Drivers/clock.d \
./Drivers/lpit.d \
./Drivers/lpspi.d \
./Drivers/lpuart.d \
./Drivers/nvic.d \
./Drivers/port.d \
./Drivers/sevenseg.d \
./Drivers/systick.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Drivers/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


