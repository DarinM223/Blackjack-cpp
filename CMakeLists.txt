cmake_minimum_required(VERSION 2.8.3)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror -lpthread")

project(Blackjack)

file(GLOB_RECURSE SRCS "src/*.c*")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(Blackjack ${SRCS})
