# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pitchRollCOntroller C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pitchRollCOntroller 
	main.cpp
	MPU6050/I2Cdev.cpp
	MPU6050/MPU6050.cpp
)

pico_enable_stdio_uart(pitchRollCOntroller 0)
pico_enable_stdio_usb(pitchRollCOntroller 1)

# Add any user requested libraries
target_link_libraries(pitchRollCOntroller
        hardware_i2c
		pico_stdlib
        pico_double
)

pico_add_extra_outputs(pitchRollCOntroller)