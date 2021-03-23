
cmake_minimum_required(VERSION 3.16.3)
project(microlith LANGUAGES CXX)

set(MICROLITH_MAJOR_VERSION 0)
set(MICROLITH_MINOR_VERSION 0)
set(MICROLITH_PATCH_VERSION 2)
set(MICROLITH_VERSION "${MICROLITH_MAJOR_VERSION}.${MICROLITH_MINOR_VERSION}.${MICROLITH_PATCH_VERSION}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/conan-util.cmake)
conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

set(CMAKE_CXX_STANDARD 17)

add_library(microlith
  include/microlith/services.h
  src/abstract_service.cpp
  src/executable_interface.cpp
  src/in_process_service_discoverer.cpp
  src/service_executor.cpp
)

target_include_directories(microlith PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(microlith 
  PUBLIC 
    CONAN_PKG::ctti  
)

add_subdirectory(test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        IMMEDIATE @ONLY
    )
    add_custom_target(docs
        "${DOXYGEN_EXECUTABLE}"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    )
else()
    message(WARNING "Doxygen not found, documentation will not be built")
endif()
