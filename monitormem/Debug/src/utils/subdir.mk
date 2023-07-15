################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/utils/server_utils.c \
../src/utils/utils.c 

C_DEPS += \
./src/utils/server_utils.d \
./src/utils/utils.d 

OBJS += \
./src/utils/server_utils.o \
./src/utils/utils.o 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.c src/utils/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-utils

clean-src-2f-utils:
	-$(RM) ./src/utils/server_utils.d ./src/utils/server_utils.o ./src/utils/utils.d ./src/utils/utils.o

.PHONY: clean-src-2f-utils

