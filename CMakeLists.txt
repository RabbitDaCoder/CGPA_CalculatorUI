cmake_minimum_required(VERSION 3.27)
project(CGPA_CalculatorUI C)

set(CMAKE_C_STANDARD 11)

# Suppress warnings
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

# -------------------------
# Raylib via FetchContent
# -------------------------
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "5.5"
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

# Add include directory
include_directories(include)

# -------------------------
# Your Executable
# -------------------------
add_executable(CGPA_CalculatorUI
        main.c
        app.c
        app.h
        renderers/raylib/clay_renderer_raylib.c  # Add Clay renderer
)

# -------------------------
# Link with Raylib
# -------------------------
target_link_libraries(CGPA_CalculatorUI raylib)

if(WIN32)
    target_link_libraries(CGPA_CalculatorUI
            opengl32
            gdi32
            winmm
            kernel32
            user32
            shell32
    )
endif()