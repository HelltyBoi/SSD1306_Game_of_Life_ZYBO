################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
SSD1306_example_app_bsp_xilffs_polled_example_1.elf.size \


# All Target
all: SSD1306_example_app_bsp_xilffs_polled_example_1.elf secondary-outputs

# Tool invocations
SSD1306_example_app_bsp_xilffs_polled_example_1.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM gcc linker'
	arm-xilinx-eabi-gcc -Wl,-T -Wl,../src/lscript.ld -L../../SSD1306_example_app_bsp/ps7_cortexa9_0/lib -o "SSD1306_example_app_bsp_xilffs_polled_example_1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SSD1306_example_app_bsp_xilffs_polled_example_1.elf.size: SSD1306_example_app_bsp_xilffs_polled_example_1.elf
	@echo 'Invoking: ARM Print Size'
	arm-xilinx-eabi-size SSD1306_example_app_bsp_xilffs_polled_example_1.elf  |tee "SSD1306_example_app_bsp_xilffs_polled_example_1.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) SSD1306_example_app_bsp_xilffs_polled_example_1.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
