set architecture arm
set remotetimeout 100000

# connect to the gdbserver
target remote :3333

#enable tui
tui enable

# turn off pagination in GDB
set pagination off

# Set flash parallelism mode to 32, 16, or 8 bit when using STM32 F2/F4 microcontrollers
# 2=32 bit, 1=16 bit and 0=8 bit parallelism mode
#monitor flash set_parallelism_mode 2

set print asm-demangle on
monitor arm semihosting enable

# Reset the device.
monitor reset init
monitor sleep 1000
monitor halt
monitor sleep 1000

# Load the program executable
load

break main

# Run to the breakpoint.
continue

