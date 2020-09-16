################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_prog.c \
../DIO_FUNC.c \
../INTERRUPT_FUNC.c \
../MAX7219_FUNC.c \
../RAM_128K_FUNC.c \
../SPI_Prog.c \
../TIMER_FUNC.c \
../main.c 

OBJS += \
./ADC_prog.o \
./DIO_FUNC.o \
./INTERRUPT_FUNC.o \
./MAX7219_FUNC.o \
./RAM_128K_FUNC.o \
./SPI_Prog.o \
./TIMER_FUNC.o \
./main.o 

C_DEPS += \
./ADC_prog.d \
./DIO_FUNC.d \
./INTERRUPT_FUNC.d \
./MAX7219_FUNC.d \
./RAM_128K_FUNC.d \
./SPI_Prog.d \
./TIMER_FUNC.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


