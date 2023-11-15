set(target_name libfts_app)
add_executable(${target_name} main.cpp ../libfts/libfts.cpp)

target_include_directories(${target_name} PUBLIC cxxopts)
target_link_libraries(${target_name} PRIVATE cxxopts libfts)

set_target_properties(
  ${target_name}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    CXX_CLANG_TIDY ${CLANG_TIDY_EXE})

if(MSVC)
  target_compile_options(${target_name} PRIVATE /W4 /WX)
else()
  target_compile_options(
    ${target_name}
    PRIVATE
      -Wall
      -Wextra
      -Werror
      -pedantic)
endif()