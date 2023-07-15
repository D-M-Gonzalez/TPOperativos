################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/client_utils.c \
../src/initial_setup.c \
../src/kernel.c \
../src/long_term_planification.c \
../src/server_utils.c \
../src/short_term_planification.c 

C_DEPS += \
./src/client_utils.d \
./src/initial_setup.d \
./src/kernel.d \
./src/long_term_planification.d \
./src/server_utils.d \
./src/short_term_planification.d 

OBJS += \
./src/client_utils.o \
./src/initial_setup.o \
./src/kernel.o \
./src/long_term_planification.o \
./src/server_utils.o \
./src/short_term_planification.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


