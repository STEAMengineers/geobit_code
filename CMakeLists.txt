# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")
set(CMAKE_BUILD_TYPE Debug)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(geolocator C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_definitions(TX_SINGLE_MODE_SECURE)

# Add executables
add_executable(
    geolocator
    main.c
    threads/blink/blink.c
    tx_initialize_low_level.S
)

target_compile_options(geolocator PRIVATE -O0)

pico_set_program_name(geolocator "geolocator")
pico_set_program_version(geolocator "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(geolocator 0)
pico_enable_stdio_usb(geolocator 0)

set(THREADX_ARCH "cortex_m33")
set(THREADX_TOOLCHAIN "gnu")
add_subdirectory(libs/threadx)

# Add the required libraries to link against.
target_link_libraries(
    geolocator
    pico_stdlib
    cmsis_core
    azrtos::threadx
)

# Add the standard include files to the build
target_include_directories(
    geolocator PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(geolocator)

