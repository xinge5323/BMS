cmake_minimum_required(VERSION 3.26)
project(BMS C)

set(CMAKE_C_STANDARD 99)

include_directories(Header_file)

add_executable(BMS
        main.c
        Source_file/LinkList.c
        Source_file/account_create.c
        Header_file/login.h
        Header_file/interface.h
        Source_file/interface.c
        Header_file/book_user_operation.h
        Source_file/book_user_operation.c
        Header_file/loading.h
        Source_file/loading.c
        Source_file/login.c
)
