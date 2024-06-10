#include "tokenizer.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<char*> command_tokenizer(const std::string& string) {
  std::vector<char*> split_strings{};

  size_t i{};

  while (i < string.length()) {
    std::string current{};
    if (string[i] == '\"') {
      current.push_back(string[i++]);

      while (string[i] != '\"') {
        current.push_back(string[i++]);
      }
    } else if (string[i] == '\'') {
      current.push_back(string[i++]);
    } else {
      while (string[i] != ' ') {
        current.push_back(string[i++]);
      }
    }

    split_strings.push_back(strdup(current.c_str()));
    i++;
  }

  return split_strings;
}
