################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/Blancher_level.c \
../ECUAL/Flow_rate.c \
../ECUAL/Gas.c \
../ECUAL/Inverter.c \
../ECUAL/LCD.c \
../ECUAL/PowderIF.c \
../ECUAL/Pumb.c \
../ECUAL/Tank_level.c \
../ECUAL/Temperature.c 

OBJS += \
./ECUAL/Blancher_level.o \
./ECUAL/Flow_rate.o \
./ECUAL/Gas.o \
./ECUAL/Inverter.o \
./ECUAL/LCD.o \
./ECUAL/PowderIF.o \
./ECUAL/Pumb.o \
./ECUAL/Tank_level.o \
./ECUAL/Temperature.o 

C_DEPS += \
./ECUAL/Blancher_level.d \
./ECUAL/Flow_rate.d \
./ECUAL/Gas.d \
./ECUAL/Inverter.d \
./ECUAL/LCD.d \
./ECUAL/PowderIF.d \
./ECUAL/Pumb.d \
./ECUAL/Tank_level.d \
./ECUAL/Temperature.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/%.o: ../ECUAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -D__AVR_ATmega16__=0 -U__AVR_ATmega16__ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


