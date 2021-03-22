project(microlithic)
cmake_minimum_required(VERSION 3.16.3)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/conan-util.cmake)
conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

add_library(microlithic INTERFACE)

add_subdirectory(test)
