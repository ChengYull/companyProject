cmake_minimum_required(VERSION 3.28)
project(companyProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(companyProject main.cpp
        Staff.cpp
        Staff.h
        CommenStaff.cpp
        CommenStaff.h
        Manger.cpp
        Manger.h
        Boss.cpp
        Boss.h)
