cmake_minimum_required(VERSION 3.10.3)

set(PROJECT_NAME "comb")
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#---------------------------------------------------------

# sources & headers
set(SOURCES main.cpp calc.cpp error.cpp parser.cpp)
set(HEADERS calc.h error.h parser.h)

#---------------------------------------------------------

set(ALL_FILES ${SOURCES}
              ${HEADERS})

add_executable(${PROJECT_NAME} ${ALL_FILES})

# Filters
source_group("" FILES ${ALL_FILES})