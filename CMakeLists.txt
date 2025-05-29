cmake_minimum_required(VERSION 3.31)
project(Antonia)

set(CMAKE_CXX_STANDARD 20)

file(GLOB sources
        "${CMAKE_SOURCE_DIR}/*.cpp"
)

add_executable(Antonia ${sources})
