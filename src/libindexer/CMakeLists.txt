set(target_name libindexer)

add_library(${target_name} STATIC indexer.cpp indexer.hpp)

target_include_directories(
    ${target_name}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(
  ${target_name}
  PUBLIC
  pugixml
  picosha2
)

enable_testing()
include(GoogleTest)

add_executable(libindexer_test indexer.test.cpp ../libparser/parser.cpp)

target_link_libraries(
    libindexer_test
    ${target_name}
    GTest::gtest_main
)

target_include_directories(
    libindexer_test
    PRIVATE
    ${target_name}   
)

gtest_discover_tests(libindexer_test)