add_library (libfts STATIC libfts.cpp libfts.hpp)
target_include_directories(
  libfts
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../
)

enable_testing()
include(GoogleTest)

add_executable(libfts_test libfts.test.cpp)
target_link_libraries(
   libfts_test
   libfts
   GTest::gtest_main
)

target_include_directories(
  libfts_test
  PRIVATE
  libfts
)

gtest_discover_tests(libfts_test)