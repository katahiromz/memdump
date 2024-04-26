# CMakeLists.txt --- CMake project settings
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.6)

# project name and languages
project(memdump CXX)

# memdump.exe
add_executable(memdump memdump.cpp)

##############################################################################
