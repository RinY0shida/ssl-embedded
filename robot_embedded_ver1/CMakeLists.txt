cmake_minimum_required(VERSION 3.10)

project(robot_embedded_ver1 VERSION 1.0 LANGUAGES CXX)

add_executable(robot_embedded_ver1 
                src/main.cc 
                src/can_communication
                )

target_include_directories(robot_embedded_ver1 PRIVATE inc)

set_target_properties(robot_embedded_ver1 PROPERTIES 
                CXX_STANDARD 11 
                CXX_STANDARDRE_REQUIRED YES
                CXX_EXTENSIONS NO
                )