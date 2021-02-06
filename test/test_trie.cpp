#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <trie.hpp>

#include <algorithm>
#include <vector>

TEST_CASE("test_empty_check")
{
  dust_structures::DustTrie trie;
  bool is_word = trie.IsWord("");
  CHECK(is_word == false);
  is_word = trie.IsWord("test");
  CHECK(is_word == false);
}

TEST_CASE("test_double_add")
{
  dust_structures::DustTrie trie;
  bool added = trie.AddWord("test");
  CHECK(added == true);
  added = trie.AddWord("test");
  CHECK(added == false);
}

TEST_CASE("test_add_and_check")
{
  dust_structures::DustTrie trie;
  bool added = trie.AddWord("test");
  bool is_word = trie.IsWord("test");
  CHECK(added == true);
  CHECK(is_word == true);
}

TEST_CASE("test_lookup_empty")
{
  dust_structures::DustTrie trie;
  std::vector<std::string> words = trie.LookUp("");
  CHECK(words.size() == 0);
}

TEST_CASE("test_lookup_single_word")
{
  dust_structures::DustTrie trie;
  trie.AddWord("test");
  std::vector<std::string> words = trie.LookUp("");
  
  REQUIRE(words.size() == 1);
  CHECK(words[0] == "test");

  words = trie.LookUp("te");
  REQUIRE(words.size() == 1);
  CHECK(words[0] == "test");

  words = trie.LookUp("test");
  REQUIRE(words.size() == 1);
  CHECK(words[0] == "test");

  words = trie.LookUp("nonexistent");
  CHECK(words.size() == 0);
}

TEST_CASE("test_lookup_multi_word")
{
  std::vector<std::string> test_words = {"test","testward","testing","tests","tested","testable"};
  
  dust_structures::DustTrie trie;
  for (const auto& word : test_words) {
    trie.AddWord(word);
  }

  std::vector<std::string> words = trie.LookUp("test");
  CHECK(words.size() == 6);
  for (const auto& word : test_words) {
    CHECK(std::find(words.begin(), words.end(), word) != words.end());
  }
}
