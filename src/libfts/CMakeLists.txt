set(target_name libfts)

add_library (${target_name} STATIC libfts.cpp libfts.hpp)

target_include_directories(
  ${target_name}
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../
)

enable_testing()
include(GoogleTest)

add_executable(libfts_test libfts.test.cpp)

target_link_libraries(
   libfts_test
   ${target_name}
   GTest::gtest_main
)

target_include_directories(
  libfts_test
  PRIVATE
  ${target_name}
)

gtest_discover_tests(libfts_test)