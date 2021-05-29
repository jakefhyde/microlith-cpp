
cmake_minimum_required(VERSION 3.16.3)
project(microlith LANGUAGES CXX)

include(cmake/meta.cmake)

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

set(DEPS ctti::ctti)

if(DEFINED MICROLITH_NO_SPDLOG)
target_compile_definitions(microlith
  PUBLIC
    MICROLITH_NO_SPDLOG=1
)
else()
find_package(spdlog REQUIRED)
list(APPEND DEPS spdlog::spdlog)
endif()

target_include_directories(microlith
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
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

option(BUILD_DOCS "Build documentation" ON)

if(BUILD_DOCS)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/Doxyfile.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/Doxyfile"
)
add_custom_target(docs ALL
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/docs"
  COMMAND make html
)
endif()
