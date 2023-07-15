################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/allocate_segment.c 

C_DEPS += \
./src/lib/allocate_segment.d 

OBJS += \
./src/lib/allocate_segment.o 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.c src/lib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



