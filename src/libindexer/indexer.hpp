#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <libparser/parser.hpp>
#include <picosha2.h>
#include <string>
#include <unordered_map>
#include <vector>

using DocId = int;
using Text = std::string;
using Term = std::string;
using Positions = std::vector<int>;
using TermInfo = std::unordered_map<DocId, Positions>;

namespace indexer {
struct Index {
  std::unordered_map<DocId, Text> docs;
  std::unordered_map<Term, TermInfo> entries;
};

class IndexWriter {
public:
  virtual void write(std::string path, const Index &index) = 0;
};

class TextIndexWriter : public IndexWriter {
public:
  void write(std::string path, const Index &index) override;
};

class IndexBuilder {
private:
  Index indexStruct;

public:
  common::NgramParser testParser;

  void add_document(int documentId, std::string text);
  inline Index index() { return indexStruct; }

  IndexBuilder() = default;
};

std::string string_to_hash(const std::string &string);
} // namespace indexer