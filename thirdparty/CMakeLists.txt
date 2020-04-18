
set(hal_path STM32CubeF1/Drivers/STM32F1xx_HAL_Driver)
file(GLOB_RECURSE HAL_SOURCES ${hal_path}/Src/*.c)
list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_template.c*$")

add_library(hal STATIC
            ${HAL_SOURCES}
            )

target_compile_definitions(hal
                           PUBLIC ${MCU_LINE} USE_HAL_LIBRARY STM32F103xB)

target_include_directories(
  hal
  PUBLIC
  	${PROJECT_SOURCE_DIR}/blinky/include 
    STM32CubeF1/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    STM32CubeF1/Drivers/CMSIS/Include
    STM32CubeF1/Drivers/CMSIS/RTOS/Tempalte
    ${hal_path}/Inc)


set(rtos_path STM32CubeF1/Middlewares/Third_Party/FreeRTOS)
file(GLOB RTOS_SOURCES ${rtos_path}/Source/*.c)
add_library(rtos STATIC
            ${RTOS_SOURCES}
		    ${rtos_path}/Source/CMSIS_RTOS/cmsis_os.c
		    ${rtos_path}/Source/portable/MemMang/heap_4.c
		    ${rtos_path}/Source/portable/GCC/ARM_CM3/port.c
            )

target_compile_definitions(rtos
                           PUBLIC ${MCU_LINE} USE_HAL_LIBRARY STM32F103xB)

target_include_directories(
  rtos
  PUBLIC
  	${PROJECT_SOURCE_DIR}/blinky/include
	${rtos_path}/Source/portable/GCC/ARM_CM3
    ${rtos_path}/Source/CMSIS_RTOS
    ${rtos_path}/Source/include)

# Link for cmsis
target_link_libraries( rtos hal)
