cmake_minimum_required(VERSION 3.8)
project(CaptainsLog)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp date.h Author.cpp Author.h Commit.cpp Commit.h Git.cpp Git.h PathDelta.cpp PathDelta.h Delta.cpp Delta.h Date.cpp Date.h Format.cpp Format.h)

add_executable(CaptainsLog ${SOURCE_FILES})
