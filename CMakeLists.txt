
cmake_minimum_required(VERSION 3.16.3)
project(microlith LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/conan-util.cmake)
conan_cmake_run(CONANFILE conanfile.py
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD missing
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")

set(PUBLIC_HEADERS
  include/microlith/detail/log.h
  include/microlith/executable_interface.h
  include/microlith/in_process_service_discoverer.h
  include/microlith/service_executor.h
  include/microlith/services.h
)

set(SOURCES
  src/abstract_service.cpp
  src/executable_interface.cpp
  src/in_process_service_discoverer.cpp
  src/service_executor.cpp
)

add_library(microlith ${PUBLIC_HEADERS} ${SOURCES})

set_target_properties(microlith
  PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

target_include_directories(microlith
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/detail
)

target_link_libraries(microlith
  PUBLIC
    CONAN_PKG::ctti
    CONAN_PKG::spdlog
)

add_subdirectory(test)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include"
  DESTINATION "include/microlith"
  FILES_MATCHING PATTERN "*.h"
)
