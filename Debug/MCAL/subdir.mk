################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ADC.c \
../MCAL/DIO.c \
../MCAL/Interrupt.c \
../MCAL/SPI.c \
../MCAL/Timer.c \
../MCAL/UART.c 

OBJS += \
./MCAL/ADC.o \
./MCAL/DIO.o \
./MCAL/Interrupt.o \
./MCAL/SPI.o \
./MCAL/Timer.o \
./MCAL/UART.o 

C_DEPS += \
./MCAL/ADC.d \
./MCAL/DIO.d \
./MCAL/Interrupt.d \
./MCAL/SPI.d \
./MCAL/Timer.d \
./MCAL/UART.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -D__AVR_ATmega16__=0 -U__AVR_ATmega16__ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


