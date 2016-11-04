################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ILP.cpp \
../src/ListAlgorithm.cpp \
../src/main.cpp \
../src/plate.cpp \
../src/randomSeq.cpp 

OBJS += \
./src/ILP.o \
./src/ListAlgorithm.o \
./src/main.o \
./src/plate.o \
./src/randomSeq.o 

CPP_DEPS += \
./src/ILP.d \
./src/ListAlgorithm.d \
./src/main.d \
./src/plate.d \
./src/randomSeq.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


