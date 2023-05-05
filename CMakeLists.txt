cmake_minimum_required(VERSION 3.26)

# set the project name
project(${PROJECT_NAME} Warcraft)

# set cpp standard
set(CMAKE_CXX_STANDARD 14)


# 当使用 MSVC 编译器时, 设置输入代码的编码格式为 utf-8
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# add the executable
aux_source_directory(src/. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})