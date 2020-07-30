cmake_minimum_required(VERSION 2.8.9)

project(csvlab)

file(GLOB SOURCES "*.c")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} m )