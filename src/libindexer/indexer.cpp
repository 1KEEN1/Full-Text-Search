#include <libindexer/indexer.hpp>

namespace indexer {

std::string string_to_hash(const std::string &string) {
  std::string hash_string;
  picosha2::hash256_hex_string(string, hash_string);
  return hash_string.substr(0, 6);
}

void indexer::IndexBuilder::add_document(int documentId, std::string text) {
  indexStruct.docs[documentId] = text;

  // Making terms.
  std::vector<std::pair<std::string, int>> ngrams =
      testParser.parse(text); // Making ngrams from text.
  std::unordered_map<int, std::vector<std::pair<std::string, int>>>
      terms; // Making terms from ngrams.
  terms[documentId] = ngrams;

  // Pushing data for entries into structure.
  for (const auto &term : terms) {
    for (const auto &pair : term.second) {
      indexStruct.entries[pair.first][term.first].push_back(pair.second);
    }
  }
  ngrams.clear();
  terms.clear();
}

void indexer::TextIndexWriter::write(std::string path, const Index &index) {
  std::filesystem::path indexPath = path + "/index";
  std::filesystem::create_directories(indexPath);

  std::filesystem::path docsPath = indexPath / "docs";
  std::filesystem::create_directories(docsPath);

  std::filesystem::path entriesPath = indexPath / "entries";
  std::filesystem::create_directories(entriesPath);

  // Output of docs into file.
  for (const auto &[docId, doc] : index.docs) {
    std::filesystem::path filePath =
        docsPath / (std::to_string(docId) + ".txt");
    std::ofstream file(filePath);
    file << doc;
    file.close();
  }

  // Output of entries into file.
  for (const auto &[term, entries] : index.entries) {
    const auto hash_term = string_to_hash(term);
    std::filesystem::path filePath = entriesPath / (hash_term + ".txt");
    std::ofstream file(filePath, std::ios::app);
    std::stringstream string_entries;
    string_entries << term << " " << entries.size() << " ";
    for (const auto &[document_id, text_positions] : entries) {
      string_entries << document_id << " " << text_positions.size() << " ";
      for (const auto &text_position : text_positions) {
        string_entries << text_position << " ";
      }
    }
    file << string_entries.str() << "\n";
  }
}

} // namespace indexer