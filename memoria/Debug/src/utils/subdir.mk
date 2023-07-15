################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/utils/algoritmos.c \
../src/utils/calculos.c \
../src/utils/client_utils.c \
../src/utils/datos.c \
../src/utils/server_utils.c \
../src/utils/utils.c 

C_DEPS += \
./src/utils/algoritmos.d \
./src/utils/calculos.d \
./src/utils/client_utils.d \
./src/utils/datos.d \
./src/utils/server_utils.d \
./src/utils/utils.d 

OBJS += \
./src/utils/algoritmos.o \
./src/utils/calculos.o \
./src/utils/client_utils.o \
./src/utils/datos.o \
./src/utils/server_utils.o \
./src/utils/utils.o 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.c src/utils/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '




