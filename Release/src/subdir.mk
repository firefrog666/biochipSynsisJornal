################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ILP.cpp \
../src/ListAlgorithm.cpp \
../src/main.cpp \
../src/plate\ basically\ working.cpp \
../src/plate.cpp \
../src/randomSeq.cpp 

OBJS += \
./src/ILP.o \
./src/ListAlgorithm.o \
./src/main.o \
./src/plate\ basically\ working.o \
./src/plate.o \
./src/randomSeq.o 

CPP_DEPS += \
./src/ILP.d \
./src/ListAlgorithm.d \
./src/main.d \
./src/plate\ basically\ working.d \
./src/plate.d \
./src/randomSeq.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/plate\ basically\ working.o: ../src/plate\ basically\ working.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/plate basically working.d" -MT"src/plate\ basically\ working.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


