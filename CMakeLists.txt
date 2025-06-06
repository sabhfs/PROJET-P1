cmake_minimum_required(VERSION 3.30)
project(ProjetC C)

set(CMAKE_C_STANDARD 99)

add_executable(ProjetC
        main.c
        column.c
        dataframe.c
        sort.c
        list.c
        column.h
        dataframe.h
        sort.h
        list.h
        tp.c
)
