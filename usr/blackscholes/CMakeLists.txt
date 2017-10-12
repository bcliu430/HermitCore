cmake_minimum_required(VERSION 3.7)
include(~/Documents/HermitCore/cmake/HermitCore-Application.cmake)
#INCLUDE_DIRECTORIES("/usr/include")
project(blackscholes C)

#set(CMAKE_C_FLAGS "-nostdlib -nodefaultlibs -nostartfiles")
set (CMAKE_SHARED_LINKER_FLAGS "--DNCO=4")
add_executable(blackscholes blackscholes.c)



