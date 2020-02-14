cmake_minimum_required(VERSION 3.13)
project(LED-Controller VERSION 1.1)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

add_executable(ledctrl src/main.cpp src/LEDController.cpp src/SerialUtil.cpp src/Color.cpp)
