#include <libparser/parser.hpp>

namespace common {

common::NgramParser::NgramParser(const std::string &p_configPath)
    : ConfigPath(std::move(p_configPath)) {
  pugi::xml_document configDocument;

  configDocument.load_file(ConfigPath.c_str());

  const pugi::xml_node parserNode = configDocument.child("fts").child("parser");
  min_ngram_length = parserNode.attribute("ngram_min_length").as_int();
  max_ngram_length = parserNode.attribute("ngram_max_length").as_int();

  if (!configDocument.load_file(ConfigPath.c_str())) {
    std::cout << "Failed to load config.xml" << std::endl;
  }

  const pugi::xml_node stopWordsNode =
      configDocument.select_node("/fts/parser/stop_words").node();

  if (stopWordsNode != nullptr) {
    for (const pugi::xml_node wordNode : stopWordsNode.children("word")) {
      stopWords.emplace_back(wordNode.text().get());
    }
  }
}

common::NgramParser::NgramParser() : NgramParser("config.xml") {}

std::vector<std::pair<std::string, int>>
common::NgramParser::parse(std::string p_text) {
  // Get string to lower case.
  std::transform(p_text.begin(), p_text.end(), p_text.begin(), tolower);

  // Remove all punctuation symbols.
  auto it = std::remove_if(p_text.begin(), p_text.end(),
                           [](char c) { return std::ispunct(c); });
  p_text.erase(it, p_text.end());

  // Split words by spaces.
  std::string word;
  for (const char ch : p_text) {
    if (!std::isspace(ch)) {
      word.push_back(ch);
    } else {
      if (!word.empty()) {
        textWords.push_back(std::move(word));
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    textWords.push_back(std::move(word));
  }

  // Remove all stop words from a vector of words.
  std::vector<std::string> wordsWithoutStopWords;
  for (const std::string &word : textWords) {
    if (std::find(stopWords.begin(), stopWords.end(), word) ==
        stopWords.end()) {
      wordsWithoutStopWords.push_back(word);
    }
  }
  textWords = wordsWithoutStopWords;

  // Make ngrams.
  int counter = 0;
  std::vector<std::pair<std::string, int>> nGrams;
  for (const std::string &word : textWords) {
    for (int i = min_ngram_length;
         i <= std::min(max_ngram_length, static_cast<int>(word.length()));
         i++) {
      const std::string substr = word.substr(0, i);
      nGrams.emplace_back(substr, counter);
    }
    counter++;
  }

  textWords.clear();

  return nGrams;
}
} // namespace common