#include <gtest/gtest.h>

#include <libparser/parser.hpp>
#include <pugixml.hpp>

class ParserTest : public ::testing::Test {
protected:
  void SetUp() override {
    pugi::xml_document doc;
    auto declarationNode = doc.append_child(pugi::node_declaration);
    declarationNode.append_attribute("version") = "1.0";
    declarationNode.append_attribute("encoding") = "utf-8";
    declarationNode.append_attribute("standalone") = "yes";

    auto root = doc.append_child("fts");
    auto parser_node = root.append_child("parser");
    parser_node.append_attribute("ngram_min_length") = "3";
    parser_node.append_attribute("ngram_max_length") = "6";
    auto stop_words = parser_node.append_child("stop_words");
    stop_words.append_child("word")
        .append_child(pugi::node_pcdata)
        .set_value("and");
    stop_words.append_child("word")
        .append_child(pugi::node_pcdata)
        .set_value("dr");
    stop_words.append_child("word")
        .append_child(pugi::node_pcdata)
        .set_value("mr");
    doc.save_file("config.xml", PUGIXML_TEXT(" "));
  }
  void TearDown() override { std::remove("config.xml"); }
};

TEST_F(ParserTest, CheckConfigFile) {
  ASSERT_NO_THROW({
    auto parser = new common::NgramParser("config.xml");
    delete parser;
  });
}

TEST_F(ParserTest, constructor) {
  int expected_min_ngram_length = 3, expected_max_ngram_length = 6;
  common::NgramParser testParser("config.xml");

  ASSERT_EQ(testParser.getMinNgram(), expected_min_ngram_length);
  ASSERT_EQ(testParser.getMaxNgram(), expected_max_ngram_length);
}

TEST_F(ParserTest, makeNGrams) {
  std::vector<std::pair<std::string, int>> expected_ngrams = {
      {"jek", 0},    {"jeky", 0}, {"jekyl", 0},
      {"jekyll", 0}, {"hyd", 1},  {"hyde", 1}};
  common::NgramParser testParser;

  ASSERT_EQ(testParser.parse("Dr. Jekyll and Mr. Hyde"), expected_ngrams);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}