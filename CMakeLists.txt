cmake_minimum_required(VERSION 3.22)
project(libasm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address,undefined -fno-omit-frame-pointer")


## google test -----------------------------------------------------------------
include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#find_package(GTest REQUIRED)
enable_testing()

## libasm.a --------------------------------------------------------------------
link_directories(${CMAKE_SOURCE_DIR}/lib)

## includes --------------------------------------------------------------------
include_directories(
        includes
        tests/includes
)

## srcs ------------------------------------------------------------------------
set (utest_srcs
        tests/utest/test_strlen.cpp
        tests/utest/test_strcpy.cpp
        tests/utest/test_strcmp.cpp
        tests/utest/test_write.cpp
        tests/utest/test_read.cpp
)


add_executable(utest ${utest_srcs})

## test ------------------------------------------------------------------------
target_link_libraries(
        utest
        GTest::gtest_main
        asm
)

gtest_discover_tests(utest)
