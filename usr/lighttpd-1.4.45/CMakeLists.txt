cmake_minimum_required(VERSION 3.7)
include(~/Documents/HermitCore/cmake/HermitCore-Application.cmake)
project(lighttpd C)

AUX_SOURCE_DIRECTORY(src SRC)

add_executable(lighttpd ${SRC})

