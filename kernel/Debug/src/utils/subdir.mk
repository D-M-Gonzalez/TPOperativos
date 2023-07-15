################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/utils/archivos_utils.c \
../src/utils/calculos.c \
../src/utils/contexto_utils.c \
../src/utils/datos.c \
../src/utils/file_utils.c \
../src/utils/init_utils.c \
../src/utils/instruc_utils.c \
../src/utils/mutex_utils.c \
../src/utils/recursos_utils.c \
../src/utils/registros_utils.c \
../src/utils/segmentos_utils.c \
../src/utils/utils.c 

C_DEPS += \
./src/utils/archivos_utils.d \
./src/utils/calculos.d \
./src/utils/contexto_utils.d \
./src/utils/datos.d \
./src/utils/file_utils.d \
./src/utils/init_utils.d \
./src/utils/instruc_utils.d \
./src/utils/mutex_utils.d \
./src/utils/recursos_utils.d \
./src/utils/registros_utils.d \
./src/utils/segmentos_utils.d \
./src/utils/utils.d 

OBJS += \
./src/utils/archivos_utils.o \
./src/utils/calculos.o \
./src/utils/contexto_utils.o \
./src/utils/datos.o \
./src/utils/file_utils.o \
./src/utils/init_utils.o \
./src/utils/instruc_utils.o \
./src/utils/mutex_utils.o \
./src/utils/recursos_utils.o \
./src/utils/registros_utils.o \
./src/utils/segmentos_utils.o \
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
	-$(RM) ./src/utils/archivos_utils.d ./src/utils/archivos_utils.o ./src/utils/calculos.d ./src/utils/calculos.o ./src/utils/contexto_utils.d ./src/utils/contexto_utils.o ./src/utils/datos.d ./src/utils/datos.o ./src/utils/file_utils.d ./src/utils/file_utils.o ./src/utils/init_utils.d ./src/utils/init_utils.o ./src/utils/instruc_utils.d ./src/utils/instruc_utils.o ./src/utils/mutex_utils.d ./src/utils/mutex_utils.o ./src/utils/recursos_utils.d ./src/utils/recursos_utils.o ./src/utils/registros_utils.d ./src/utils/registros_utils.o ./src/utils/segmentos_utils.d ./src/utils/segmentos_utils.o ./src/utils/utils.d ./src/utils/utils.o

.PHONY: clean-src-2f-utils

