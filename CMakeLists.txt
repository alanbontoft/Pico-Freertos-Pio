cmake_minimum_required(VERSION 3.20)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(Pico-FreeRTOS-Pio)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Pico SDK
pico_sdk_init()

# rest of your project

add_subdirectory(freertos)
add_subdirectory(src)

