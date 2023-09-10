cmake_minimum_required(VERSION 3.16)

# set the project name
project(${PROJECT_NAME} Warcraft VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH ${QT_ROOT_DIR})

# set qt toolchain
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# set compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# set cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

# add the executable
aux_source_directory(src/. SRC_LIST)

# add GUI version of the executable
qt_add_executable(${PROJECT_NAME}
    main.cpp
    ${SRC_LIST}
    app_win32.rc
    res.qrc
)

# add CLI version of the executable
add_executable(
    ${PROJECT_NAME}_CLI 
    main_CLI.cpp
    src/AbstractCity.cpp
    src/EventHandler.cpp
    src/GameIO.cpp
    src/Headquarter.cpp
    src/Warrior.cpp
)

# add support for unicode in MSVC
if(MSVC)
    target_compile_options(${PROJECT_NAME}_CLI PRIVATE "/source-charset:utf-8")
endif()


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
