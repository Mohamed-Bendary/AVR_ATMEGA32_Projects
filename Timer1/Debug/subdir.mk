################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_program.c \
../EXTI_program.c \
../LCD_program.c \
../Timer0_program.c \
../Timer1_program.c \
../main.c 

OBJS += \
./DIO_program.o \
./EXTI_program.o \
./LCD_program.o \
./Timer0_program.o \
./Timer1_program.o \
./main.o 

C_DEPS += \
./DIO_program.d \
./EXTI_program.d \
./LCD_program.d \
./Timer0_program.d \
./Timer1_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


