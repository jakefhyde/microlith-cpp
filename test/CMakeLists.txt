
add_executable(microlith-test services-test.cpp)

target_link_libraries(microlith-test
  PUBLIC
    microlith
)
