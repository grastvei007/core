cmake_minimum_required(VERSION 3.16)
project(core)

include_directories(include)


add_library(core SHARED
    include/daemon.h
    src/daemon.cpp
    )


add_custom_command(TARGET core
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:core> $ENV{DEV_LIBS} )
