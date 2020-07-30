cmake_minimum_required(VERSION 2.8.9)

project(lab2)
file(GLOB SOURCES "*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} progbase)