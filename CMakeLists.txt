cmake_minimum_required(VERSION 3.10)
project(CGPA_CalculatorUI C)

set(CMAKE_C_STANDARD 11)

# Include folder
include_directories(${CMAKE_SOURCE_DIR}/include)

# Library folder
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Executable
add_executable(CGPA_CalculatorUI main.c)

# Link with raylib + system libs
target_link_libraries(CGPA_CalculatorUI
        raylib
        opengl32
        gdi32
        winmm
        kernel32
        user32
        shell32)
