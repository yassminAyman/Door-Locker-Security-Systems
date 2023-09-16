################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../control_functions.c \
../control_main.c \
../dc_motor.c \
../eeprom.c \
../general_gpio.c \
../i2c.c \
../pwm.c \
../timer.c \
../uart.c 

OBJS += \
./buzzer.o \
./control_functions.o \
./control_main.o \
./dc_motor.o \
./eeprom.o \
./general_gpio.o \
./i2c.o \
./pwm.o \
./timer.o \
./uart.o 

C_DEPS += \
./buzzer.d \
./control_functions.d \
./control_main.d \
./dc_motor.d \
./eeprom.d \
./general_gpio.d \
./i2c.d \
./pwm.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


