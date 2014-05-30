cmake_minimum_required(VERSION 2.8)

project(levlib CXX)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

set(src
	"src/loop.cpp"
	"src/timer.cpp"
	"src/socket.cpp"
	"src/signal_break.cpp"
	)

list(APPEND include_dirs "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(public_hdrs
	"include/lev/lev.h"
	"include/lev/loop.h"
	"include/lev/timer.h"
	"include/lev/socket.h"
	"include/lev/signal_break.h"
	)

set(hdrs
	)

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/libev" "${CMAKE_BINARY_DIR}/vendor/libev")
list(APPEND libraries "libev")
list(APPEND include_dirs "${CMAKE_SOURCE_DIR}/vendor/libev")

list(APPEND libraries "${platformlibs}")

add_library(levlib STATIC ${src} ${hdrs} ${public_hdrs})

set_target_properties(levlib PROPERTIES 
	INCLUDE_DIRECTORIES "${include_dirs}"
	PUBLIC_HEADER "${public_hdrs}"
	VERSION ${MAJOR_VERSION}.${MINOR_VERSION}
	SOVERSION ${MAJOR_VERSION}
)

target_link_libraries(levlib ${libraries})

#include(print_properties.cmake)
#echo_target(levlib)