cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)

project(SDLxQt)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# SDL Stuff
add_subdirectory(SDL EXCLUDE_FROM_ALL)

# Qt Stuff

list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.4.0/macos")
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.4.0/msvc2019_64")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
qt_standard_project_setup()

# Link it all up
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 Qt6::Widgets)
