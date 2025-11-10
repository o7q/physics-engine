cmake_minimum_required(VERSION 3.10)

project(physics_engine)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(${PROJECT_NAME} PRIVATE -O3 -Wall)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)
