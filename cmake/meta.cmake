
set(BUILD_SYSTEM CMAKE CACHE STRING "Build system for finding dependencies")
set_property(CACHE BUILD_SYSTEM PROPERTY STRINGS CONAN CMAKE)

if(BUILD_SYSTEM STREQUAL "CONAN")
  include(cmake/conan-util.cmake)
elseif(BUILD_SYSTEM STREQUAL "CMAKE")
  # currently do nothing, using find_package anyway
endif()

option(MICROLITH_EMBED_CTTI OFF)

if(MICROLITH_EMBED_CTTI)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ctti)
  add_library(ctti::ctti ALIAS ctti)
else()
  find_package(ctti REQUIRED)
endif()

set(MICROLITH_DEPS ctti::ctti)

option(MICROLITH_NO_SPDLOG OFF)

if(MICROLITH_NO_SPDLOG)
target_compile_definitions(microlith
  PUBLIC
    MICROLITH_NO_SPDLOG=1
)
else()
target_compile_definitions(microlith
  PUBLIC
    MICROLITH_NO_SPDLOG=0
)
find_package(spdlog REQUIRED)
list(APPEND MICROLITH_DEPS spdlog::spdlog)
endif()
