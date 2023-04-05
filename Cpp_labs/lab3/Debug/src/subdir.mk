################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lab3.cpp 

CPP_DEPS += \
./src/lab3.d 

OBJS += \
./src/lab3.o 


# Each subdirectory must supply rules for building sources it contributes
src/lab3.o: ../src/lab3.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++2a -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/lab3.d ./src/lab3.o

.PHONY: clean-src

