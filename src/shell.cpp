#include "shell.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>

void Shell::update_directory(std::string_view new_directory) {
  if (new_directory == ".") {
    return;
  }

  if (new_directory == "..") {
    std::string old_directory{this->m_directory};

    while (old_directory.length() > 0 && !old_directory.ends_with('/')) {
      old_directory.pop_back();
    }

    return;
  }

  this->m_directory = new_directory;
}
