
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
  include/microlith/executable_interface.h
  include/microlith/in_process_service_discoverer.h
  include/microlith/service_executor.h
  include/microlith/services.h
)

set(PRIVATE_HEADERS
  include/microlith/detail/log.h
  include/microlith/detail/macros.h
)

set(SOURCES
  src/abstract_service.cpp
  src/executable_interface.cpp
  src/in_process_service_discoverer.cpp
  src/service_executor.cpp
)

add_library(microlith ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

set(DEPS CONAN_PKG::ctti)

if(DEFINED MICROLITH_NO_SPDLOG)
target_compile_definitions(microlith
  PUBLIC
    MICROLITH_NO_SPDLOG=1
)
else()
list(APPEND DEPS CONAN_PKG::spdlog)
endif()

target_include_directories(microlith
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/detail
)

target_link_libraries(microlith
  PUBLIC
    ${DEPS}
)

enable_testing()
add_subdirectory(test)

install(FILES ${PUBLIC_HEADERS}
  DESTINATION "include/microlith"
)

install(FILES ${PRIVATE_HEADERS}
  DESTINATION "include/microlith/detail"
)

install(TARGETS microlith)
