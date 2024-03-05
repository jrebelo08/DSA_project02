cmake_minimum_required(VERSION 3.26.4)
project(AED2324_PRJ2_G105)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED2324_PRJ2_G105 src/main.cpp
        src/Airline.cpp
        src/Airline.h
        src/Airport.cpp
        src/Airport.h
        src/Graph.h
        src/App.h
        src/App.cpp
        src/reader.h
        src/reader.cpp)