cmake_minimum_required(VERSION 3.14)
project(ships)
set(CMAKE_CXX_STANDARD 17)

include_directories(include src)

add_executable( ships
        src/main.cpp
        src/Ivec2.cpp
        include/Ivec2.h
        src/Ship.cpp
        include/Ship.h
        src/Target.cpp
        include/Target.h
        src/Board.cpp
        include/Board.h
        src/Turn.cpp
        include/Turn.h
        src/Player.cpp
        include/Player.h
        src/Network.cpp
        include/Network.h
        src/TextGame.cpp
        include/TextGame.h)