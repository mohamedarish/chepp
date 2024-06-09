#include "tokenizer.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<char*> string_tokenizer(const std::string& string, char delimiter) {
  std::vector<char*> split_strings{};

  size_t i{};

  while (i < string.length()) {
    std::string current{};
    while (string[i] != delimiter) {
      current.push_back(string[i]);
      i++;
    }

    split_strings.push_back(strdup(current.c_str()));
    i++;
  }

  return split_strings;
}
