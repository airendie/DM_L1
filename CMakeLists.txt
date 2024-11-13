cmake_minimum_required(VERSION 3.5.0)
project(DM_L1_V2 VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp")
#file(GLOB INCLUDE "include/*.hpp" "include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

