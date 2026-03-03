cmake_minimum_required(VERSION 3.13)

# -------------------------------
# Project definition
# -------------------------------
project(feather_rp2040_passthrough C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# -------------------------------
# Pico SDK path
# -------------------------------
# Use environment variable PICO_SDK_PATH if not passed via command line
if(NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")
endif()

# Check that the path exists
if(NOT EXISTS "${PICO_SDK_PATH}/pico_sdk_import.cmake")
    message(FATAL_ERROR "Cannot find pico_sdk_import.cmake at ${PICO_SDK_PATH}. Make sure Pico SDK is downloaded and PICO_SDK_PATH is correct.")
endif()

# Include the Pico SDK
include(${PICO_SDK_PATH}/pico_sdk_import.cmake)

# Initialize the Pico SDK
pico_sdk_init()

# -------------------------------
# Add executable
# -------------------------------
add_executable(feather_passthrough
    main.c
    usb_descriptors.c
)

# -------------------------------
# Compiler definitions for TinyUSB
# -------------------------------
target_compile_definitions(feather_passthrough PRIVATE
    CFG_TUSB_MCU=OPT_MCU_RP2040
    CFG_TUSB_RHPORT0_MODE=(OPT_MODE_DEVICE|OPT_MODE_HOST)
    CFG_TUSB_OS=OPT_OS_NONE
    CFG_TUH_HID=1
    CFG_TUD_HID=1
)

# -------------------------------
# Link libraries
# -------------------------------
target_link_libraries(feather_passthrough
    pico_stdlib
    tinyusb_device
    tinyusb_host
)

# -------------------------------
# Extra outputs (.uf2, .bin, .map)
# -------------------------------
pico_add_extra_outputs(feather_passthrough)