#ifndef _DUST_TRIE_HPP_
#define _DUST_TRIE_HPP_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace dust_structures
{
  /**
   * A trie is a tree where each letter of input strings are
   * stored letter by letter in a linked series of nodes.
   */
  class DustTrie
  {
  public:
    DustTrie();
    ~DustTrie();

    /**
     * @brief Add a string to the trie.
     * @param entry The entry to add to the trie
     * @return A bool, true is the entry was added, false if already existed
     */
    bool AddWord(const std::string& word);

    /**
     * @brief Lookup a string and return all entries with the lookup prefix
     * @param prefix The prefix to lookup
     * @return A vector<string> containing all the potential entries stemming from this prefix
     */
    std::vector<std::string> LookUp(const std::string& prefix);

    /**
     * @brief Check if this entry exists as a word within the trie
     * @param entry The entry to check
     * @return A bool representing whether or not this entry exists as a word in the trie
     */
    bool IsWord(const std::string& entry);
    
  private:
    struct Node;

    const std::unique_ptr<struct Node>* findNode(
      const std::unique_ptr<struct Node>& node,
      const std::string& search);
    bool addWord(std::unique_ptr<struct Node>& node, const std::string& word);
    bool isWord(const std::unique_ptr<struct Node>& node, const std::string& entry);
    void collectWords(
      const std::unique_ptr<struct Node>& node,
      std::string wordSoFar,
      std::vector<std::string>& words);

  private:
    struct Node
    {
      bool is_word;
      std::unordered_map<char, std::unique_ptr<struct Node>> leaves;
    };

    std::unique_ptr<struct Node> root_;
  };
}

#endif /* _DUST_TRIE_HPP_ */
