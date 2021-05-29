
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(microlith-tests
  test-in_process_service_discoverer.cpp
  test-service_executor.cpp
)

target_link_libraries(microlith-tests
  microlith
  GTest::gtest
  GTest::gtest_main
)

gtest_discover_tests(microlith-tests)
