cmake_minimum_required(VERSION 4.0.0)
project(Renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

option(ONLY_LIBS "" ON)
add_subdirectory(third-party/glew)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# Needed because glfw doesn't work with wayland
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
add_subdirectory(third-party/glfw)

add_executable("CalculatorApp" 
    src/main
    src/Button.cpp
    src/Calculator.cpp
    src/Window.cpp
    )
file(COPY ./font DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories("CalculatorApp" PRIVATE include)
target_link_libraries("CalculatorApp" glfw GL libglew_static)


