cmake_minimum_required(VERSION 3.7.2)
project(PrakBS24 C)

set(CMAKE_C_STANDARD 99)

add_executable(PrakBS24 main.c
        main.h
        sub.c
        sub.c
        sub.c
        keyValStore.h
        keyValStore.c
        sub.h
        client.c)
