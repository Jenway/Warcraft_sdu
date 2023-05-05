cmake_minimum_required(VERSION 3.0)

# set the project name
project(${PROJECT_NAME} Warcraft)

# set cpp standard
set(CMAKE_CXX_STANDARD 14)

if(MSVC)
    # 添加编译选项, 设置 输入代码的编码格式为 utf-8
    add_compile_options("/source-charset:utf-8")
endif()

# add the executable
aux_source_directory(src/. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})