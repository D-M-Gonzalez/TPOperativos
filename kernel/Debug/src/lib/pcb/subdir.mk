################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/pcb/corto_plazo.c \
../src/lib/pcb/largo_plazo.c 

C_DEPS += \
./src/lib/pcb/corto_plazo.d \
./src/lib/pcb/largo_plazo.d 

OBJS += \
./src/lib/pcb/corto_plazo.o \
./src/lib/pcb/largo_plazo.o 


# Each subdirectory must supply rules for building sources it contributes
src/lib/pcb/%.o: ../src/lib/pcb/%.c src/lib/pcb/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



