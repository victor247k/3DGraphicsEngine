cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2")
#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(untitled src/main.cpp
        src/3DRenderer.cpp
)
