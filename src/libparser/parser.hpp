#pragma once
#include <iostream>
#include <vector>

namespace common {
class Parser {
public:
  virtual std::vector<std::pair<std::string, int>>
  parse(std::string p_text) = 0;
  Parser() = default;
  Parser(const Parser &other) = default;
  Parser(Parser &&other) = default;
  Parser &operator=(Parser &&other) = default;
  virtual ~Parser() = default;
};

class NgramParser : public Parser {
private:
  std::string text;
  std::string ConfigPath;
  std::vector<std::string> stopWords;
  std::vector<std::string> textWords;
  std::vector<std::pair<std::string, int>> nGrams;
  int min_ngram_length = 0;
  int max_ngram_length = 0;

public:
  explicit NgramParser(const std::string &p_configPath);
  NgramParser();
  ~NgramParser() override{};
  inline int getMinNgram() { return min_ngram_length; }
  inline int getMaxNgram() { return max_ngram_length; }
  inline std::vector<std::string> getTextWords() { return textWords; }
  inline std::vector<std::pair<std::string, int>> getNGrams() { return nGrams; }
  std::vector<std::pair<std::string, int>> parse(std::string p_text) override;
};
} // namespace common