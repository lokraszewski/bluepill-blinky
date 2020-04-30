# bluepill-blinky
cmake project for STM32F103 ["Bluepill"](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill.html) board with FreeRTOS & STM32CubeF1

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

![](png/pinout.png)


---

## Dependancies 

```shell
sudo apt-get install -y cmake gcc-arm-none-eabi openocd cmake
```

## Clone

```shell
% git clone --recursive git@github.com:lokraszewski/bluepill-blinky.git
```

## Configure & Build
Create build directory and configure using cmake:
```shell
% mkdir build && cd $_
% cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain/stm32f103.cmake -DCMAKE_BUILD_TYPE=Debug
```
The build type is optional here, we use it in the example for Debug session. Build:
```shell
make -j
```


---


## Debug 
Fir start the debugger, in our case we're using OpenOCD:
```shell
% make debug_server
Scanning dependencies of target debug_server
Open On-Chip Debugger 0.10.0
Licensed under GNU GPL v2
```
From the build directory we can now load our firmware and run it:
```shell
% make debug_session
```
You should see the following:
![](png/gdb_session.png)

Once the program is running you should see the printf printing via semihosting in OpenOCD window:
![](png/semi_host_print.png)



---


---

## License
[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)
- **[MIT license](http://opensource.org/licenses/mit-license.php)**
