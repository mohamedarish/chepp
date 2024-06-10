#include "shell.h"
#include "colors.h"
#include "lib.h"
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

Shell::Shell(const std::string& left, const std::string& directory)
    : m_left{left}, m_directory{directory} {
  change_dir_internal(directory);
}

void Shell::update_directory(const std::string& new_directory) {
  if (new_directory == ".") {
    return;
  }

  if (new_directory == "..") {
    if (this->m_directory == "/") {
      throw std::runtime_error("cd error: Cannot cd back from '/'");
    }
    std::string old_directory{this->m_directory};

    while (old_directory.length() > 0 && !old_directory.ends_with('/')) {
      old_directory.pop_back();
    }
    old_directory.pop_back();

    this->m_directory = old_directory;

  } else {
    const std::string new_path = join_path(new_directory, this->m_directory);

    this->m_directory = new_path;
  }

  try {
    change_dir_internal(this->m_directory);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

std::string Shell::prompt() {

  std::string prompt_value{
      std::string(RED + "username" + RESET) + '@' +
      std::string(GREEN + "hostname" + RESET) + " > " +
      std::string(YELLOW + this->m_directory.c_str() + RESET) + ' '};

  return prompt_value;
}
