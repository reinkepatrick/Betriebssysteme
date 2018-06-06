cmake_minimum_required(VERSION 3.10)
project(scheduling C)

set(CMAKE_C_STANDARD 99)

find_package(Threads)

add_executable(scheduling
        src/main.c
        src/lists.c
        src/global.c
        include/lists.h
        include/global.h)

link_libraries(scheduling ${CMAKE_THREAD_LIBS_INIT})
