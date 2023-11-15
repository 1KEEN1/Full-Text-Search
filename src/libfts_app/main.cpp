#include <cxxopts.hpp>
#include <iostream>

#include <libfts/libfts.hpp>

int main(int argc, char **argv) {
  cxxopts::Options options("sum");

  try {
    options.add_options()("first", "First value", cxxopts::value<double>())(
        "second", "Second value", cxxopts::value<double>());

    auto result = options.parse(argc, argv);

    if ((result.count("first") != 1) || (result.count("second") != 1)) {
      std::cout << options.help() << std::endl;
      return 0;
    }

    auto firstNumber = result["first"].as<double>();
    auto secondNumber = result["second"].as<double>();

    std::cout << fts(firstNumber, secondNumber) << std::endl;
  } catch (const std::exception &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
}