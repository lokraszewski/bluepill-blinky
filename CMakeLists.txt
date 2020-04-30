cmake_minimum_required(VERSION 3.16)

project(bluepill_blinky C ASM)

find_program(ST_FLASH NAMES st-flash)
find_program(OPENOCD NAMES openocd)
find_program(GDB NAMES gdb-multiarch)

set(MCU_FAMILY STM32F1xx)
set(MCU_LINE STM32F103xx)

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE ${PROJECT_SOURCE_DIR}/toolchain/stm32f103.cmake)
endif()
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map"
)

add_subdirectory(blinky)
