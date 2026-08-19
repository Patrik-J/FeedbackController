cmake_minimum_required(VERSION 4.3)
project(feedback_controller)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/feedbackcontroller.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/feedbackcontroller.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/timer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pid.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/pid.hpp"
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")