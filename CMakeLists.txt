cmake_minimum_required(VERSION 3.0.0)
project(Einsteinium VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

include(CTest)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/http
                    ../Dependencies/boost_1_82_0)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE src ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.c)

add_executable(Einsteinium ${src}
        src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
