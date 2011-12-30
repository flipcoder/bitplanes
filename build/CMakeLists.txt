cmake_minimum_required(VERSION 2.8.1)
cmake_policy(SET CMP0015 NEW) # link_directories relative
project(bitplanes)

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected - Adding compiler flags")
	set(CMAKE_CXX_FLAGS "-pthread -ggdb -Wextra -Wall -std=c++0x")
    #set(CMAKE_CXX_FLAGS "-pthread -O2 -Wextra -Wall -std=c++0x")
endif(CMAKE_COMPILER_IS_GNUCXX)

file(GLOB_RECURSE SRCS ../src/*.cpp)
link_directories(../third_party/lib)
add_executable(../bin/bitplanes ${SRCS})
target_link_libraries(../bin/bitplanes allegro allegro_image allegro_font allegro_acodec)

if(CMAKE_COMPILER_IS_GNUCXX)
	include_directories(/usr/include/freetype2/)
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories(../third_party/include/)

