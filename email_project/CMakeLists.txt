cmake_minimum_required(VERSION 3.13)
project(email_project C)

set(CMAKE_C_STANDARD 99)

add_executable(email_project email_project.c email_project.h parse.c email_print.c)