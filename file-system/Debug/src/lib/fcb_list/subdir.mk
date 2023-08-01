################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/fcb_list/borrar_fcb.c \
../src/lib/fcb_list/buscar_fcb.c \
../src/lib/fcb_list/cant_bloques_fcb.c \
../src/lib/fcb_list/crear_fcb.c \
../src/lib/fcb_list/get_fcb.c \
../src/lib/fcb_list/inicializar_fcb_list.c \
../src/lib/fcb_list/lista_bloques_fcb.c \
../src/lib/fcb_list/modificar_fcb.c \
../src/lib/fcb_list/nombre_fcb.c \
../src/lib/fcb_list/truncar_fcb.c \
../src/lib/fcb_list/valor_fcb.c 

C_DEPS += \
./src/lib/fcb_list/borrar_fcb.d \
./src/lib/fcb_list/buscar_fcb.d \
./src/lib/fcb_list/cant_bloques_fcb.d \
./src/lib/fcb_list/crear_fcb.d \
./src/lib/fcb_list/get_fcb.d \
./src/lib/fcb_list/inicializar_fcb_list.d \
./src/lib/fcb_list/lista_bloques_fcb.d \
./src/lib/fcb_list/modificar_fcb.d \
./src/lib/fcb_list/nombre_fcb.d \
./src/lib/fcb_list/truncar_fcb.d \
./src/lib/fcb_list/valor_fcb.d 

OBJS += \
./src/lib/fcb_list/borrar_fcb.o \
./src/lib/fcb_list/buscar_fcb.o \
./src/lib/fcb_list/cant_bloques_fcb.o \
./src/lib/fcb_list/crear_fcb.o \
./src/lib/fcb_list/get_fcb.o \
./src/lib/fcb_list/inicializar_fcb_list.o \
./src/lib/fcb_list/lista_bloques_fcb.o \
./src/lib/fcb_list/modificar_fcb.o \
./src/lib/fcb_list/nombre_fcb.o \
./src/lib/fcb_list/truncar_fcb.o \
./src/lib/fcb_list/valor_fcb.o 


# Each subdirectory must supply rules for building sources it contributes
src/lib/fcb_list/%.o: ../src/lib/fcb_list/%.c src/lib/fcb_list/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-lib-2f-fcb_list

clean-src-2f-lib-2f-fcb_list:
	-$(RM) ./src/lib/fcb_list/borrar_fcb.d ./src/lib/fcb_list/borrar_fcb.o ./src/lib/fcb_list/buscar_fcb.d ./src/lib/fcb_list/buscar_fcb.o ./src/lib/fcb_list/cant_bloques_fcb.d ./src/lib/fcb_list/cant_bloques_fcb.o ./src/lib/fcb_list/crear_fcb.d ./src/lib/fcb_list/crear_fcb.o ./src/lib/fcb_list/get_fcb.d ./src/lib/fcb_list/get_fcb.o ./src/lib/fcb_list/inicializar_fcb_list.d ./src/lib/fcb_list/inicializar_fcb_list.o ./src/lib/fcb_list/lista_bloques_fcb.d ./src/lib/fcb_list/lista_bloques_fcb.o ./src/lib/fcb_list/modificar_fcb.d ./src/lib/fcb_list/modificar_fcb.o ./src/lib/fcb_list/nombre_fcb.d ./src/lib/fcb_list/nombre_fcb.o ./src/lib/fcb_list/truncar_fcb.d ./src/lib/fcb_list/truncar_fcb.o ./src/lib/fcb_list/valor_fcb.d ./src/lib/fcb_list/valor_fcb.o

.PHONY: clean-src-2f-lib-2f-fcb_list

