#include <gtest/gtest.h>

#include <libindexer/indexer.hpp>
#include <picosha2.h>

class IndexTest : public ::testing::Test {
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
    stop_words.append_child("word")
        .append_child(pugi::node_pcdata)
        .set_value("the");
    doc.save_file("config.xml", PUGIXML_TEXT(" "));
  }

  void TearDown() override { std::remove("config.xml"); }
};

TEST_F(IndexTest, fileTest) {
  indexer::IndexBuilder testBuilder;
  indexer::TextIndexWriter testWriter;

  testBuilder.add_document(199903, "The Matrix");
  testBuilder.add_document(200305, "The Matrix Reloaded");
  testBuilder.add_document(200311, "The Matrix Revolutions");

  testWriter.write(".", testBuilder.index());
  indexer::Index testStructure = testBuilder.index();

  std::unordered_map<int, std::string> expectedDocs = {
      {199903, "The Matrix"},
      {200305, "The Matrix Reloaded"},
      {200311, "The Matrix Revolutions"}};
  std::unordered_map<int, std::string> docs = testStructure.docs;

  std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>>
      expectedEntries = {
          {"mat", {{200311, {0}}, {200305, {0}}, {199903, {0}}}},
          {"matr", {{200311, {0}}, {200305, {0}}, {199903, {0}}}},
          {"matri", {{200311, {0}}, {200305, {0}}, {199903, {0}}}},
          {"matrix", {{200311, {0}}, {200305, {0}}, {199903, {0}}}},
          {"reload", {{200305, {1}}}},
          {"rel", {{200305, {1}}}},
          {"relo", {{200305, {1}}}},
          {"reloa", {{200305, {1}}}},
          {"revo", {{200311, {1}}}},
          {"rev", {{200311, {1}}}},
          {"revol", {{200311, {1}}}},
          {"revolu", {{200311, {1}}}}};
  std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>>
      entries = testStructure.entries;

  ASSERT_EQ(expectedDocs, docs);
  ASSERT_EQ(expectedEntries, entries);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}