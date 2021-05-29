
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CONAN_CMAKE_URL
  "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS
    "Downloading conan.cmake from https://github.com/conan-io/cmake-conan"
  )
  file(DOWNLOAD
    "${CONAN_CMAKE_URL}"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    TLS_VERIFY ON
  )
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.py
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD missing
)
