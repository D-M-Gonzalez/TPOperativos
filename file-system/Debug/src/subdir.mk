################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/file-system.c \
../src/initial_setup.c 

C_DEPS += \
./src/file-system.d \
./src/initial_setup.d 

OBJS += \
./src/file-system.o \
./src/initial_setup.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/file-system.d ./src/file-system.o ./src/initial_setup.d ./src/initial_setup.o

.PHONY: clean-src

