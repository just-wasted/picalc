cmake_minimum_required(VERSION 3.15)
project(picalc C)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(picalc ${SRCS})

target_include_directories(picalc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(picalc PRIVATE -Wall -Wextra -Werror)
