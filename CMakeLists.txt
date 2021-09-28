cmake_minimum_required(VERSION 3.15)
project("Str Language") # my programming language called Str

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/vars.txt ${CMAKE_CURRENT_BINARY_DIR}/vars.txt)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/conditionals.txt ${CMAKE_CURRENT_BINARY_DIR}/conditionals.txt)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/bucles.txt ${CMAKE_CURRENT_BINARY_DIR}/bucles.txt)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/functions.txt ${CMAKE_CURRENT_BINARY_DIR}/functions.txt)


file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.h )


include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )


add_executable(str_language src/main.cpp ${HEADERS} ${SOURCES})
