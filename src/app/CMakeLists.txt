add_executable(app main.cpp ../libfts/libfts.cpp)

target_include_directories(app PUBLIC cxxopts)
target_link_libraries(app PRIVATE cxxopts)

set_target_properties(
  app
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    CXX_CLANG_TIDY ${CLANG_TIDY_EXE})

if(MSVC)
  target_compile_options(app PRIVATE /W4 /WX)
else()
  target_compile_options(
    app
    PRIVATE
      -Wall
      -Wextra
      -Werror
      -pedantic)
endif()