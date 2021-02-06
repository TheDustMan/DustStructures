#include "trie.hpp"

namespace dust_structures
{
  DustTrie::DustTrie()
    : root_(std::make_unique<struct Node>())
  {}
  
  DustTrie::~DustTrie()
  {}

  bool DustTrie::addWord(std::unique_ptr<struct Node>& node, const std::string& entry)
  {
    if (entry.empty()) {
      return false;
    }

    char front = entry[0];
    bool added = false;
    if (node->leaves.find(front) == node->leaves.end()) {
      node->leaves[front] = std::make_unique<struct Node>();
      node->leaves[front]->is_word = false;
      added = true;
    }

    if (entry.size() > 1) {
      std::string rest = entry.substr(1);
      return this->addWord(node->leaves[front], rest);
    } else {
      node->leaves[front]->is_word = true;
    }

    return added;
  }

  bool DustTrie::AddWord(const std::string& entry)
  {
    return this->addWord(this->root_, entry);
  }

  const std::unique_ptr<struct DustTrie::Node>* DustTrie::findNode(
    const std::unique_ptr<struct Node>& node,
    const std::string& search)
  {
    if (search.empty()) {
      return &node;
    }

    if (node->leaves.find(search[0]) == node->leaves.end()) {
      // This search string doesn't exist in the trie
      return nullptr;
    }

    if (search.size() == 1) {
      return &node->leaves[search[0]];
    }

    std::string rest = search.substr(1);
    return this->findNode(node->leaves[search[0]], rest);
  }
  
  std::vector<std::string> DustTrie::LookUp(const std::string& prefix)
  {
    // Lookup the node for the prefix
    const std::unique_ptr<struct Node>* lookup = this->findNode(this->root_, prefix);
    if (lookup == nullptr) {
      return {};
    }

    // Do a depth-first traversal to collect words stemming from this node
    std::vector<std::string> words;
    this->collectWords(*lookup, prefix, words);

    return words;
  }

  void DustTrie::collectWords(
    const std::unique_ptr<struct Node>& node,
    std::string wordSoFar,
    std::vector<std::string>& words)
  {
    if (node->is_word) {
      words.push_back(wordSoFar);
    }

    for (const auto& kv_pair : node->leaves) {
      std::string nextWordSoFar = wordSoFar + kv_pair.first;
      this->collectWords(kv_pair.second, nextWordSoFar, words);
    }
  }

  bool DustTrie::isWord(const std::unique_ptr<struct Node>& node, const std::string& entry)
  {
    if (entry.empty() || node->leaves.find(entry[0]) == node->leaves.end()) {
      return false;
    } else if (entry.size() > 1) {
      return this->isWord(node->leaves[entry[0]], entry.substr(1));
    }
    return node->leaves[entry[0]]->is_word;
  }
  
  bool DustTrie::IsWord(const std::string& entry)
  {
    return this->isWord(this->root_, entry);
  }
}
