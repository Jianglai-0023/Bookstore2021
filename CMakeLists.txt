cmake_minimum_required(VERSION 3.16)
project(Bookstore)

set(CMAKE_CXX_STANDARD 14)

include_directories(Bookstorebody)

add_executable(code
        Bookstorebody/blocklist.cpp
        Bookstorebody/blocklist.h
        Bookstorebody/Bookstore_main.cpp
        Bookstorebody/Command.cpp
        Bookstorebody/usermanager.cpp
        Bookstorebody/file.cpp
        Bookstorebody/lubang.cpp
        Bookstorebody/Booksystem.cpp

        )
