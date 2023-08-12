cmake_minimum_required(VERSION 3.21)
project(words C)

set(CMAKE_C_STANDARD 11)

include_directories(ADT)

add_executable(9024_ass
        ADT/list.c
        ADT/list.h
        ADT/PQueue.c
        ADT/PQueue.h
        ADT/queue.c
        ADT/queue.h
        ADT/stack.c
        ADT/stack.h
        ADT/WGraph.c
        ADT/WGraph.h
        words.c)
