#include "tokenizer.h"
#include <cstring>
#include <string>
#include <vector>

std::vector<char*> command_tokenizer(const std::string& command_input) {
  std::vector<char*> split_strings{};

  size_t i{};

  while (i < command_input.length()) {
    std::string current{};
    if (command_input[i] == '\"') {
      current.push_back(command_input[i++]);

      while (command_input[i] != '\"') {
        current.push_back(command_input[i++]);
      }
    } else if (command_input[i] == '\'') {
      current.push_back(command_input[i++]);
    } else {
      while (command_input[i] != ' ') {
        current.push_back(command_input[i++]);
      }
    }

    split_strings.push_back(strdup(current.c_str()));
    i++;
  }

  return split_strings;
}
