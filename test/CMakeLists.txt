cmake_minimum_required(VERSION 3.19)
find_package(GTest REQUIRED)
include(GoogleTest)
add_executable(test_sample
  singleton.cpp
  max_size.cpp
  empty.cpp
  size.cpp
  push.cpp
  pop.cpp
  erase.cpp
)
target_link_libraries(test_sample
  GTest::GTest
  GTest::Main
)
