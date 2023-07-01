################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tp-2023-1c-Segmentation-Fault.c 

C_DEPS += \
./src/tp-2023-1c-Segmentation-Fault.d 

OBJS += \
./src/tp-2023-1c-Segmentation-Fault.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/tp-2023-1c-Segmentation-Fault.d ./src/tp-2023-1c-Segmentation-Fault.o

.PHONY: clean-src

