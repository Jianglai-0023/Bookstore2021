cmake_minimum_required(VERSION 3.20)
project(Bookstore)

set(CMAKE_CXX_STANDARD 14)

include_directories(Bookstorebody)

add_executable(Bookstore
        Bookstorebody/blocklist.cpp
        Bookstorebody/blocklist.h
        Bookstorebody/bookstore.cpp
        Bookstorebody/bookstore.h
        Bookstorebody/Main.cpp
        Bookstorebody/usermanager.cpp
        Bookstorebody/usermanager.h)
