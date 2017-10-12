cmake_minimum_required(VERSION 3.7)
include(~/Documents/HermitCore/cmake/HermitCore-Application.cmake)
project(nginx C)

AUX_SOURCE_DIRECTORY(core CORE)
AUX_SOURCE_DIRECTORY(event EVENT)
AUX_SOURCE_DIRECTORY(os/unix UNIX)
AUX_SOURCE_DIRECTORY(http HTTP)

set (SRC )

add_executable(nginx ${SRC})

