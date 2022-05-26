cmake_minimum_required(VERSION 3.22)
project(HangManProVip)

set(CMAKE_CXX_STANDARD 23)

add_executable(HangManProVip main.cpp "Sources/Main Rule.cpp" "Header/Main Rule.h" Sources/Draw.cpp Header/Draw.h Sources/HintFunctions.cpp Header/HintFunctions.h Sources/Ai_Function.cpp Header/Ai_Function.h Sources/Player.cpp Header/Player.h)
