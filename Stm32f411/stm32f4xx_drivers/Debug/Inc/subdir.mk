################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Inc/TuNN41_OsScheduler.s 

C_SRCS += \
../Inc/TuNN41_OsKernel.c \
../Inc/gpio2.c \
../Inc/i2c.c \
../Inc/nvic.c \
../Inc/rcc.c \
../Inc/spi.c \
../Inc/systick.c \
../Inc/tim.c \
../Inc/usart.c 

OBJS += \
./Inc/TuNN41_OsKernel.o \
./Inc/TuNN41_OsScheduler.o \
./Inc/gpio2.o \
./Inc/i2c.o \
./Inc/nvic.o \
./Inc/rcc.o \
./Inc/spi.o \
./Inc/systick.o \
./Inc/tim.o \
./Inc/usart.o 

S_DEPS += \
./Inc/TuNN41_OsScheduler.d 

C_DEPS += \
./Inc/TuNN41_OsKernel.d \
./Inc/gpio2.d \
./Inc/i2c.d \
./Inc/nvic.d \
./Inc/rcc.d \
./Inc/spi.d \
./Inc/systick.d \
./Inc/tim.d \
./Inc/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/%.o: ../Inc/%.s Inc/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/TuNN41_OsKernel.cyclo ./Inc/TuNN41_OsKernel.d ./Inc/TuNN41_OsKernel.o ./Inc/TuNN41_OsKernel.su ./Inc/TuNN41_OsScheduler.d ./Inc/TuNN41_OsScheduler.o ./Inc/gpio2.cyclo ./Inc/gpio2.d ./Inc/gpio2.o ./Inc/gpio2.su ./Inc/i2c.cyclo ./Inc/i2c.d ./Inc/i2c.o ./Inc/i2c.su ./Inc/nvic.cyclo ./Inc/nvic.d ./Inc/nvic.o ./Inc/nvic.su ./Inc/rcc.cyclo ./Inc/rcc.d ./Inc/rcc.o ./Inc/rcc.su ./Inc/spi.cyclo ./Inc/spi.d ./Inc/spi.o ./Inc/spi.su ./Inc/systick.cyclo ./Inc/systick.d ./Inc/systick.o ./Inc/systick.su ./Inc/tim.cyclo ./Inc/tim.d ./Inc/tim.o ./Inc/tim.su ./Inc/usart.cyclo ./Inc/usart.d ./Inc/usart.o ./Inc/usart.su

.PHONY: clean-Inc

