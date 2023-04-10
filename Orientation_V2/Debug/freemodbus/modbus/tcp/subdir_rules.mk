################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
freemodbus/modbus/tcp/%.obj: ../freemodbus/modbus/tcp/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="D:/Workspace_Space/FreeModBus/Modbus_PIC_1.1" --include_path="D:/Workspace_Space/FreeModBus/Modbus_PIC_1.1/freemodbus/modbus/rtu" --include_path="D:/Workspace_Space/FreeModBus/Modbus_PIC_1.1/freemodbus/port" --include_path="D:/Workspace_Space/FreeModBus/Modbus_PIC_1.1/freemodbus/modbus/include" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c1294xl" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=TARGET_IS_TM4C129_RA2 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="freemodbus/modbus/tcp/$(basename $(<F)).d_raw" --obj_directory="freemodbus/modbus/tcp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


