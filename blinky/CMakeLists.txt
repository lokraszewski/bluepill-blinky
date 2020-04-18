add_executable(
  ${PROJECT_NAME}.elf
  src/main.c
  src/stm32f1xx_it.c
  ${CMAKE_SOURCE_DIR}/thirdparty/STM32CubeF1/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/system_stm32f1xx.c
  ${CMAKE_SOURCE_DIR}/thirdparty/STM32CubeF1/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/gcc/startup_stm32f103xb.s
)

target_compile_definitions(${PROJECT_NAME}.elf
                           PUBLIC ${MCU_LINE} USE_HAL_LIBRARY STM32F103xB)

target_include_directories(${PROJECT_NAME}.elf PUBLIC include)

add_custom_command(
  TARGET ${PROJECT_NAME}.elf
  POST_BUILD
  COMMAND arm-none-eabi-objcopy ARGS -O binary ${PROJECT_NAME}.elf
          ${PROJECT_NAME}.bin)

target_link_libraries(${PROJECT_NAME}.elf rtos hal)
