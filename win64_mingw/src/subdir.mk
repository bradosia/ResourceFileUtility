################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Compiler.cpp \
../src/Loader.cpp \
../src/Stream.cpp \
../src/export.cpp 

OBJS += \
./src/Compiler.o \
./src/Loader.o \
./src/Stream.o \
./src/export.o 

CPP_DEPS += \
./src/Compiler.d \
./src/Loader.d \
./src/Stream.d \
./src/export.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

