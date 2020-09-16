################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Voice-Recorder.lss \

FLASH_IMAGE += \
Voice-Recorder.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Voice-Recorder.elf secondary-outputs

# Tool invocations
Voice-Recorder.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Voice-Recorder.map -mmcu=atmega32 -o "Voice-Recorder.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Voice-Recorder.lss: Voice-Recorder.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Voice-Recorder.elf  >"Voice-Recorder.lss"
	@echo 'Finished building: $@'
	@echo ' '

Voice-Recorder.hex: Voice-Recorder.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Voice-Recorder.elf  "Voice-Recorder.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Voice-Recorder.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Voice-Recorder.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Voice-Recorder.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
