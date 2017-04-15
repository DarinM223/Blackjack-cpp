cmake_minimum_required(VERSION 2.8.3)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror -lpthread")

project(Blackjack)

file(GLOB_RECURSE SRCS "src/*.c*")
file(GLOB_RECURSE TEST_SRCS "test/*.c*")

find_package(Threads REQUIRED)

include(ExternalProject)

# Downloads googletest from external git repository.
ExternalProject_Add(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
)

# Get some properties from the googletest project.
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Sets up googletest library.
add_library(libgtest IMPORTED STATIC GLOBAL)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Sets up googlemock library.
add_library(libgmock IMPORTED STATIC GLOBAL)
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Include the googletest and googlemock libraries along with your main source folder.
include_directories(
    "${source_dir}/googletest/include"
    "${source_dir}/googlemock/include"
    ${CMAKE_SOURCE_DIR}/src
)

# Normal blackjack executable.
add_executable(Blackjack ${SRCS})

# Test blackjack executable.
add_executable(Blackjack_test ${TEST_SRCS})
add_dependencies(Blackjack_test libgmock libgtest)
target_link_libraries(Blackjack_test libgtest libgmock)
