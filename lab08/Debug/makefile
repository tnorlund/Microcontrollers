################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./control.obj" \
"./lab08.obj" \
"./mp3.obj" \
"./sound.obj" \
"../ssi_DAC.obj" \
"./tm4c1294ncpdt_startup_ccs.obj" \
"../libmad.lib" \
"../tm4c1294ncpdt.cmd" \
$(GEN_CMDS__FLAG) \
-l"/Users/tnor/workspace_v8/ff13b/ff13b.lib" \
-l"/Users/tnor/workspace_v8/periph/Debug/periph.lib" \
-l"/Users/tnor/workspace_v8/utils/Debug/utils.lib" \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
lab08.out \

EXE_OUTPUTS__QUOTED += \
"lab08.out" \

BIN_OUTPUTS += \
lab08.hex \

BIN_OUTPUTS__QUOTED += \
"lab08.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "lab08.out"

dependents:
	-cd /Users/tnor/workspace_v8/ff13b/Debug && $(MAKE) all
	-cd /Users/tnor/workspace_v8/periph/Debug && $(MAKE) all
	-cd /Users/tnor/workspace_v8/utils/Debug && $(MAKE) all

# Tool invocations
lab08.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS) /Users/tnor/workspace_v8/ff13b/Debug/ff13b.lib /Users/tnor/workspace_v8/periph/Debug/periph.lib /Users/tnor/workspace_v8/utils/Debug/utils.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"lab08.map" --heap_size=52000 --stack_size=8192 -i"/Users/tnor/workspace_v8/ff13b" -i"/Users/tnor/workspace_v8/periph/Debug" -i"/Users/tnor/workspace_v8/utils/Debug" -i"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/lib" -i"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="lab08_linkInfo.xml" --rom_model -o "lab08.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

lab08.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armhex"  -o "lab08.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "control.obj" "lab08.obj" "mp3.obj" "sound.obj" "tm4c1294ncpdt_startup_ccs.obj" 
	-$(RM) "control.d" "lab08.d" "mp3.d" "sound.d" "tm4c1294ncpdt_startup_ccs.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/tnor/workspace_v8/ff13b/Debug/ff13b.lib:
/Users/tnor/workspace_v8/periph/Debug/periph.lib:
/Users/tnor/workspace_v8/utils/Debug/utils.lib:

-include ../makefile.targets

