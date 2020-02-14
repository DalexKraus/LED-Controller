cmake_minimum_required(VERSION 3.13)
project(LED-Controller VERSION 1.1)

add_executable(ledctrl main.cpp LEDController.cpp SerialUtil.cpp Color.cpp)