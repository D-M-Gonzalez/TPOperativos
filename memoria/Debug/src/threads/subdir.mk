################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/threads/comm_threadCpu.c \
../src/threads/comm_threadFile.c \
../src/threads/comm_threadKernel.c 

C_DEPS += \
./src/threads/comm_threadCpu.d \
./src/threads/comm_threadFile.d \
./src/threads/comm_threadKernel.d 

OBJS += \
./src/threads/comm_threadCpu.o \
./src/threads/comm_threadFile.o \
./src/threads/comm_threadKernel.o 


# Each subdirectory must supply rules for building sources it contributes
src/threads/%.o: ../src/threads/%.c src/threads/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '




