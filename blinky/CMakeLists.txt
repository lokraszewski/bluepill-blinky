set(cube_path ${CMAKE_SOURCE_DIR}/thirdparty/STM32CubeF1)
set(hal_path ${cube_path}/Drivers/STM32F1xx_HAL_Driver)
set(rtos_path ${cube_path}/Middlewares/Third_Party/FreeRTOS)

file(GLOB_RECURSE hal_sources ${hal_path}/Src/*.c)
list(FILTER hal_sources EXCLUDE REGEX ".*_template.c*$")
file(GLOB rtos_sources ${rtos_path}/Source/*.c)

add_executable(
  ${PROJECT_NAME}.elf
  src/main.c
  src/stm32f1xx_it.c
  src/stm32f1xx_hal_msp.c
  src/stm32f1xx_hal_timebase_tim.c
  ${cube_path}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/system_stm32f1xx.c
  ${cube_path}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/gcc/startup_stm32f103xb.s
  ${hal_sources}
  ${rtos_sources}
  ${rtos_path}/Source/CMSIS_RTOS/cmsis_os.c
  ${rtos_path}/Source/portable/MemMang/heap_4.c
  ${rtos_path}/Source/portable/GCC/ARM_CM3/port.c)

target_compile_definitions(${PROJECT_NAME}.elf
                           PUBLIC ${MCU_LINE} USE_HAL_LIBRARY STM32F103xB)

target_compile_options(${PROJECT_NAME}.elf PRIVATE --specs=rdimon.specs)
target_link_options(${PROJECT_NAME}.elf PRIVATE -lc -lrdimon)

target_include_directories(
  ${PROJECT_NAME}.elf
  PUBLIC include
         ${rtos_path}/Source/portable/GCC/ARM_CM3
         ${rtos_path}/Source/CMSIS_RTOS
         ${rtos_path}/Source/include
         ${cube_path}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
         ${cube_path}/Drivers/CMSIS/Include
         ${cube_path}/Drivers/CMSIS/RTOS/Template
         ${hal_path}/Inc)

add_custom_target(
  ${PROJECT_NAME}.bin ALL
  COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf
          ${PROJECT_NAME}.bin
  DEPENDS ${PROJECT_NAME}.elf
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

if(ST_FLASH)
  set(FLASH_START_ADDR 0x8000000)
  add_custom_target(
    flash
    COMMAND ${ST_FLASH} --reset write
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin ${FLASH_START_ADDR}
    DEPENDS ${PROJECT_NAME}.bin
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(OPENOCD)
  add_custom_target(
    debug_server
    COMMAND ${OPENOCD} openocd --file ${PROJECT_SOURCE_DIR}/openocd-stm32f103.cfg -c 'init'
    )
endif()


if(GDB)
  add_custom_target(
    debug_session
    COMMAND ${GDB} -x ${PROJECT_SOURCE_DIR}/debug.gdb
            ${PROJECT_NAME}.elf
    DEPENDS ${PROJECT_NAME}.elf
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()
