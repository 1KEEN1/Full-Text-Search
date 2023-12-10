set(target_name libparser)

add_library(${target_name} STATIC parser.cpp parser.hpp)

target_include_directories(
  ${target_name}
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(
  ${target_name}
  PUBLIC
  pugixml
)

enable_testing()
include(GoogleTest)

add_executable(libparser_test parser.test.cpp)

target_link_libraries(
   libparser_test
   ${target_name}
   GTest::gtest_main
)

target_include_directories(
  libparser_test
  PRIVATE
  ${target_name}
)

gtest_discover_tests(libparser_test)