cmake_minimum_required(VERSION 3.8)

project(ntree)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)