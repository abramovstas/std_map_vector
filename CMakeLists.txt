cmake_minimum_required(VERSION 3.0.0)

project(std_map_vector VERSION 0.1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Werror=unused-result -Werror=return-type -std=c++11")
set(CMAKE_C_FLAGS "-O2 -g -Wall -Werror=unused-result -Werror=return-type -std=c11")


add_executable(${PROJECT_NAME} "main.cpp")
