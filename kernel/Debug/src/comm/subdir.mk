################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/comm/comm_File.c \
../src/comm/comm_Mem.c \
../src/comm/comm_threadKernel.c \
../src/comm/console_threads.c 

C_DEPS += \
./src/comm/comm_File.d \
./src/comm/comm_Mem.d \
./src/comm/comm_threadKernel.d \
./src/comm/console_threads.d 

OBJS += \
./src/comm/comm_File.o \
./src/comm/comm_Mem.o \
./src/comm/comm_threadKernel.o \
./src/comm/console_threads.o 


# Each subdirectory must supply rules for building sources it contributes
src/comm/%.o: ../src/comm/%.c src/comm/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


