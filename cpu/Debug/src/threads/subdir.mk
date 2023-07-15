################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/threads/comm_thread.c 

C_DEPS += \
./src/threads/comm_thread.d 

OBJS += \
./src/threads/comm_thread.o 


# Each subdirectory must supply rules for building sources it contributes
src/threads/%.o: ../src/threads/%.c src/threads/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '




