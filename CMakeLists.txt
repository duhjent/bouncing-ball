cmake_minimum_required(VERSION 3.5)
project(BouncingBall)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

add_executable(BouncingBall src/base.cpp src/drawing.cpp src/main.cpp)

target_link_libraries(BouncingBall PRIVATE SDL3::SDL3)
target_include_directories(BouncingBall PRIVATE ${PROJECT_SOURCE_DIR}/include)

file(COPY ${PROJECT_BINARY_DIR}/vendor/SDL/SDL3.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})

