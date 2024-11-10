################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Kernel/Src/TuNN41_OsKernel.c 

OBJS += \
./Kernel/Src/TuNN41_OsKernel.o 

C_DEPS += \
./Kernel/Src/TuNN41_OsKernel.d 


# Each subdirectory must supply rules for building sources it contributes
Kernel/Src/%.o Kernel/Src/%.su Kernel/Src/%.cyclo: ../Kernel/Src/%.c Kernel/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -c -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Inc" -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Kernel/Inc" -I"C:/Users/tungu/Desktop/STM32IDE/stm32f4xx_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Kernel-2f-Src

clean-Kernel-2f-Src:
	-$(RM) ./Kernel/Src/TuNN41_OsKernel.cyclo ./Kernel/Src/TuNN41_OsKernel.d ./Kernel/Src/TuNN41_OsKernel.o ./Kernel/Src/TuNN41_OsKernel.su

.PHONY: clean-Kernel-2f-Src

