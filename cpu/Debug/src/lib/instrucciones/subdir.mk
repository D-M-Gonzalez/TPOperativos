################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/instrucciones/cmp_instruction.c \
../src/lib/instrucciones/create_segment.c \
../src/lib/instrucciones/exit_instruction.c \
../src/lib/instrucciones/f_read_write_instruction.c \
../src/lib/instrucciones/inc_instruction.c \
../src/lib/instrucciones/ip_instruction.c \
../src/lib/instrucciones/jz_instruction.c \
../src/lib/instrucciones/mov_in_instruction.c \
../src/lib/instrucciones/mov_out_instruction.c \
../src/lib/instrucciones/set_instruction.c \
../src/lib/instrucciones/syscall_instruccion.c \
../src/lib/instrucciones/yield_instruction.c 

C_DEPS += \
./src/lib/instrucciones/cmp_instruction.d \
./src/lib/instrucciones/create_segment.d \
./src/lib/instrucciones/exit_instruction.d \
./src/lib/instrucciones/f_read_write_instruction.d \
./src/lib/instrucciones/inc_instruction.d \
./src/lib/instrucciones/ip_instruction.d \
./src/lib/instrucciones/jz_instruction.d \
./src/lib/instrucciones/mov_in_instruction.d \
./src/lib/instrucciones/mov_out_instruction.d \
./src/lib/instrucciones/set_instruction.d \
./src/lib/instrucciones/syscall_instruccion.d \
./src/lib/instrucciones/yield_instruction.d 

OBJS += \
./src/lib/instrucciones/cmp_instruction.o \
./src/lib/instrucciones/create_segment.o \
./src/lib/instrucciones/exit_instruction.o \
./src/lib/instrucciones/f_read_write_instruction.o \
./src/lib/instrucciones/inc_instruction.o \
./src/lib/instrucciones/ip_instruction.o \
./src/lib/instrucciones/jz_instruction.o \
./src/lib/instrucciones/mov_in_instruction.o \
./src/lib/instrucciones/mov_out_instruction.o \
./src/lib/instrucciones/set_instruction.o \
./src/lib/instrucciones/syscall_instruccion.o \
./src/lib/instrucciones/yield_instruction.o 


# Each subdirectory must supply rules for building sources it contributes
src/lib/instrucciones/%.o: ../src/lib/instrucciones/%.c src/lib/instrucciones/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



