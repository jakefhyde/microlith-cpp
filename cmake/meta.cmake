
set(BUILD_SYSTEM CMAKE CACHE STRING "Build system for finding dependencies")
set_property(CACHE BUILD_SYSTEM PROPERTY STRINGS CONAN CMAKE)

if(BUILD_SYSTEM STREQUAL "CONAN")
  include(cmake/conan-util.cmake)
elseif(BUILD_SYSTEM STREQUAL "CMAKE")
  # currently do nothing, using find_package anyway
endif()

if(DEFINED MICROLITH_EMBED_CTTI)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ctti)
  add_library(ctti::ctti ALIAS ctti)
else()
  find_package(ctti REQUIRED)
endif()
