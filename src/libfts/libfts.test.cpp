#include "../libfts/libfts.hpp"
#include <gtest/gtest.h>

TEST(math, sum) {
  double first_number = 2.5, second_number = 1.3, expected_result = 3.8;
  double accum_result = fts(first_number, second_number);
  ASSERT_EQ(accum_result, expected_result);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}