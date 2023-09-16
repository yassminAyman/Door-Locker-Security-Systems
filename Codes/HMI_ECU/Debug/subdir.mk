################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../eeprom.c \
../general_gpio.c \
../hmi_functions.c \
../hmi_main.c \
../i2c.c \
../keypad.c \
../lcd.c \
../timer.c \
../uart.c 

OBJS += \
./eeprom.o \
./general_gpio.o \
./hmi_functions.o \
./hmi_main.o \
./i2c.o \
./keypad.o \
./lcd.o \
./timer.o \
./uart.o 

C_DEPS += \
./eeprom.d \
./general_gpio.d \
./hmi_functions.d \
./hmi_main.d \
./i2c.d \
./keypad.d \
./lcd.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


