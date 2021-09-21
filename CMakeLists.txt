cmake_minimum_required(VERSION 3.15)
project("Lexical_Analyzer") # A lexical Analyzer for my programming language

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

add_executable(lexic4l_4n4lyzer 
			   src/lexic4l_4n4lyzer.cpp )
