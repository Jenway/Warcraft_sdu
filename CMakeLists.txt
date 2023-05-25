cmake_minimum_required(VERSION 3.16)

# set the project name
project(${PROJECT_NAME} Warcraft VERSION 1.0.0 LANGUAGES CXX)

if(MSVC)
    set(CMAKE_PREFIX_PATH $ENV{QTDIR})
else()
    set(CMAKE_PREFIX_PATH $ENV{QTDIRMINGW})    
endif()

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置Qt工具链的环境变量
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



# 设置 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# set cpp standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

# qt_add_resources(RESOURCES src/assets.qrc)

if(MSVC)
    # 添加编译选项, 设置 输入代码的编码格式为 utf-8
    # add_compile_options("/source-charset:utf-8")
    # add_compile_options("/execution-charset:gbk")
endif()


# add the executable
aux_source_directory(src/. SRC_LIST)

# add_executable(${PROJECT_NAME} ${SRC_LIST})

qt_add_executable(${PROJECT_NAME}
    ${SRC_LIST}
    res.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test")
    enable_testing()

    add_executable(test1 test/test1.cpp)

    add_test(NAME test1 COMMAND test1)
endif()
