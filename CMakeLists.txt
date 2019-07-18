cmake_minimum_required(VERSION 3.0)
project(ChessEngine)

set(includes 
  main.cpp 
  board.cpp 
  hash.cpp
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(chess ${includes})