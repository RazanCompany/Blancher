################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/Modbus/Modbus_master.c 

OBJS += \
./ECUAL/Modbus/Modbus_master.o 

C_DEPS += \
./ECUAL/Modbus/Modbus_master.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/Modbus/%.o: ../ECUAL/Modbus/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -D__AVR_ATmega16__=0 -U__AVR_ATmega16__ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


