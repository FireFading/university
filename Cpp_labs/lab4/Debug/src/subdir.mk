################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lab4.cpp 

CPP_DEPS += \
./src/lab4.d 

OBJS += \
./src/lab4.o 


# Each subdirectory must supply rules for building sources it contributes
src/lab4.o: ../src/lab4.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++2a -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/lab4.d ./src/lab4.o

.PHONY: clean-src

