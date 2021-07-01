cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
project(test_project CXX)

set(PROJECT_NAME LibUsb)

add_executable(${PROJECT_NAME} Source.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE "usb-1.0")
