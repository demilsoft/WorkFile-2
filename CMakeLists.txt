cmake_minimum_required(VERSION 3.27)
project(WorkFile_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(WorkFile_2 appointment_main.cc
        appointment.cc
        appointment.h)
