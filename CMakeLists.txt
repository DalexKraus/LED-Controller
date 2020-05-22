cmake_minimum_required(VERSION 3.13)
project(ledctrl VERSION 1.1)

#Disable in source-builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# --------------------  Sources --------------------
file(GLOB_RECURSE CXX_SOURCES RELATIVE  ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE C_SOURCES RELATIVE    ${CMAKE_SOURCE_DIR} "src/*.c")
include_directories("include/")
include_directories("src/")

find_package(Threads)

add_executable(ledctrl ${CXX_SOURCES}  ${C_SOURCES})

target_link_libraries(ledctrl ${CMAKE_THREAD_LIBS_INIT})