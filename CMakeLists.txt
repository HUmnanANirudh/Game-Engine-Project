cmake_minimum_required(VERSION 3.16)
project(tictactoe_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(engine INTERFACE)

target_include_directories(engine INTERFACE src)

add_library(tictactoe
	src/games/tictactoe/TicTacToe.hpp
	src/games/tictactoe/TicTacToe.cpp
)

target_link_libraries(tictactoe PUBLIC engine)

target_include_directories(tictactoe PUBLIC src)

add_executable(t3_cli src/main.cpp)

target_link_libraries(t3_cli PRIVATE tictactoe)
