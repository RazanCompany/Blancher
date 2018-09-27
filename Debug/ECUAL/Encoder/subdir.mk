################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/Encoder/Encoder.c 

OBJS += \
./ECUAL/Encoder/Encoder.o 

C_DEPS += \
./ECUAL/Encoder/Encoder.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/Encoder/%.o: ../ECUAL/Encoder/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -D__AVR_ATmega16__=0 -U__AVR_ATmega16__ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


