cmake_minimum_required(VERSION 3.22)

project(app)


#------------#
#-Clang-Tidy-#
#------------#
find_program(CLANG_TIDY_EXE NAMES clang-tidy-16 clang-tidy)
if (NOT CLANG_TIDY_EXE)
  message(WARNING "clang-tidy not found.")
else()
  execute_process(
    COMMAND ${CLANG_TIDY_EXE} --version
    OUTPUT_VARIABLE CLANG_TIDY_VERSION)
    message("clang-tidy found:\n" ${CLANG_TIDY_VERSION})
  endif()


#----------------#
#-SubDirectories-#
#----------------#
add_subdirectory(external)
add_subdirectory(src)


#------------#
#-GoogleTest-#
#------------#
enable_testing()

add_executable(
  libfts_test
  src/libfts/libfts.test.cpp src/libfts/libfts.cpp
)
target_link_libraries(
  libfts_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(libfts_test)