################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../example/src/main.cpp 

OBJS += \
./example/src/main.o 

CPP_DEPS += \
./example/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"F:\schoolCode\ResourceFileUtility\include" -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


