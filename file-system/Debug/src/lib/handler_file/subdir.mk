################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/handler_file/escribir_archivo.c \
../src/lib/handler_file/leer_archivo.c 

C_DEPS += \
./src/lib/handler_file/escribir_archivo.d \
./src/lib/handler_file/leer_archivo.d 

OBJS += \
./src/lib/handler_file/escribir_archivo.o \
./src/lib/handler_file/leer_archivo.o 


# Each subdirectory must supply rules for building sources it contributes
src/lib/handler_file/%.o: ../src/lib/handler_file/%.c src/lib/handler_file/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



