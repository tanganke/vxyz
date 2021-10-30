project(vxyz)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(VXYZ_TEST ON)

file(GLOB SOURCES src/*.cpp)
add_library(vxyz ${SOURCES})
target_include_directories(vxyz PUBLIC src)
target_link_libraries(vxyz fmt)

if(VXYZ_TEST)
    file(GLOB SOURCES test/*.cpp)
    add_executable(test ${SOURCES})
    target_link_libraries(test vxyz)
endif()