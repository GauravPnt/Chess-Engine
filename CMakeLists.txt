cmake_minimum_required(VERSION 3.0)
project(ChessEngine)

set(includes 
  main.cpp 
  board.cpp 
  hash.cpp
  attack.cpp
  notation.cpp
  moves.cpp
  movegen.cpp
  validate.cpp
  test.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

include_directories(${PROJECT_SOURCE_DIR})
add_executable(chess ${includes})