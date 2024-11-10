################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Kernel/TuNN41_OsKernel.c 

OBJS += \
./Kernel/TuNN41_OsKernel.o 

C_DEPS += \
./Kernel/TuNN41_OsKernel.d 


# Each subdirectory must supply rules for building sources it contributes
Kernel/%.o Kernel/%.su Kernel/%.cyclo: ../Kernel/%.c Kernel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -DSTM32F411E_DISCO -c -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Inc" -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Inc" -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Kernel" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Kernel

clean-Kernel:
	-$(RM) ./Kernel/TuNN41_OsKernel.cyclo ./Kernel/TuNN41_OsKernel.d ./Kernel/TuNN41_OsKernel.o ./Kernel/TuNN41_OsKernel.su

.PHONY: clean-Kernel

