################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/initial_setup.c \
../src/monitor_mem.c 

C_DEPS += \
./src/initial_setup.d \
./src/monitor_mem.d 

OBJS += \
./src/initial_setup.o \
./src/monitor_mem.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/initial_setup.d ./src/initial_setup.o ./src/monitor_mem.d ./src/monitor_mem.o

.PHONY: clean-src

