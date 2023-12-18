################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/gpio2.c \
../Inc/nvic.c \
../Inc/rcc.c \
../Inc/spi.c \
../Inc/systick.c \
../Inc/usart.c 

OBJS += \
./Inc/gpio2.o \
./Inc/nvic.o \
./Inc/rcc.o \
./Inc/spi.o \
./Inc/systick.o \
./Inc/usart.o 

C_DEPS += \
./Inc/gpio2.d \
./Inc/nvic.d \
./Inc/rcc.d \
./Inc/spi.d \
./Inc/systick.d \
./Inc/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -DSTM32F411E_DISCO -c -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Inc" -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/gpio2.cyclo ./Inc/gpio2.d ./Inc/gpio2.o ./Inc/gpio2.su ./Inc/nvic.cyclo ./Inc/nvic.d ./Inc/nvic.o ./Inc/nvic.su ./Inc/rcc.cyclo ./Inc/rcc.d ./Inc/rcc.o ./Inc/rcc.su ./Inc/spi.cyclo ./Inc/spi.d ./Inc/spi.o ./Inc/spi.su ./Inc/systick.cyclo ./Inc/systick.d ./Inc/systick.o ./Inc/systick.su ./Inc/usart.cyclo ./Inc/usart.d ./Inc/usart.o ./Inc/usart.su

.PHONY: clean-Inc

