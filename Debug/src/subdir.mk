################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ILP.cpp \
../src/goodLuck.cpp \
../src/plate.cpp 

OBJS += \
./src/ILP.o \
./src/goodLuck.o \
./src/plate.o 

CPP_DEPS += \
./src/ILP.d \
./src/goodLuck.d \
./src/plate.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


