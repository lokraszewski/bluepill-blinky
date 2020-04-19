
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
  ${cube_path}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/system_stm32f1xx.c
  ${cube_path}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/gcc/startup_stm32f103xb.s
  ${hal_sources}
  ${rtos_sources}
  ${rtos_path}/Source/CMSIS_RTOS/cmsis_os.c
  ${rtos_path}/Source/portable/MemMang/heap_4.c
  ${rtos_path}/Source/portable/GCC/ARM_CM3/port.c)

target_compile_definitions(${PROJECT_NAME}.elf
                           PUBLIC ${MCU_LINE} USE_HAL_LIBRARY STM32F103xB)


add_link_options('--specs=rdimon.specs -lc -lrdimon')

target_include_directories(
  ${PROJECT_NAME}.elf
  PUBLIC include
         ${rtos_path}/Source/portable/GCC/ARM_CM3
         ${rtos_path}/Source/CMSIS_RTOS
         ${rtos_path}/Source/include
         ${cube_path}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
         ${cube_path}/Drivers/CMSIS/Include
         ${cube_path}/Drivers/CMSIS/RTOS/Template
         ${hal_path}/Inc
         )

add_custom_command(
  TARGET ${PROJECT_NAME}.elf
  POST_BUILD
  COMMAND arm-none-eabi-objcopy ARGS -O binary ${PROJECT_NAME}.elf
          ${PROJECT_NAME}.bin)
