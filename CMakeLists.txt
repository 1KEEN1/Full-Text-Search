cmake_minimum_required(VERSION 3.22)

project(app)

find_program(CLANG_TIDY_EXE NAMES clang-tidy-16 clang-tidy)
if (NOT CLANG_TIDY_EXE)
  message(WARNING "clang-tidy not found.")
else()
  execute_process(
    COMMAND ${CLANG_TIDY_EXE} --version
    OUTPUT_VARIABLE CLANG_TIDY_VERSION)
    message("clang-tidy found:\n" ${CLANG_TIDY_VERSION})
  endif()

  
add_subdirectory(external)

enable_testing()

add_subdirectory(src)