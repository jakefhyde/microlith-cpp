
add_executable(microlithic-test services-test.cpp)

target_link_libraries(microlithic-test
  PUBLIC
    microlithic
)
