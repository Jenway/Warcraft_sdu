cmake_minimum_required(VERSION 3.26)

# set the project name
project(${PROJECT_NAME} Warcraft)

# add the executable
aux_source_directory(src/. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})