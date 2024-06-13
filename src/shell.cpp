#include "shell.h"
#include "lib.h"
#include <iostream>

Shell::Shell() {
  std::string current_directory = get_current_directory();
  change_dir_internal(current_directory);
  m_directory = current_directory;

  std::string prompt{"${USER}@${HOST} [${DIRECTORY}] > "};
  m_left = prompt;
}

void Shell::update_directory(const std::string& new_directory) {
  if (new_directory == ".") {
    return;
  }

  if (new_directory == "..") {
    if (m_directory == "/") {
      throw std::runtime_error("cd error: Cannot cd back from '/'");
    }
    std::string old_directory{m_directory};

    while (old_directory.length() > 0 && !old_directory.ends_with('/')) {
      old_directory.pop_back();
    }
    old_directory.pop_back();

    if (old_directory.empty()) {
      old_directory = "/";
    }

    m_directory = old_directory;

  } else {
    const std::string new_path = join_path(new_directory, m_directory);
    switch (file_or_directory_exists_in_directory(new_path)) {
    case DirectoryStatus::DirectoryExists:
      m_directory = new_path;
      break;
    case DirectoryStatus::DirectoryIsFile:
      std::cerr << "cd error: \"" << new_path
                << "\" is not a directory but a file" << std::endl;
      return;
      break;
    case DirectoryStatus::DirectoryExistsButUnknownFormat:
      std::cerr
          << "cd error: \"" << new_path
          << "\" is not a directory but the filetype could not be identified"
          << std::endl;
      return;
      break;
    case DirectoryStatus::DirectoryDoesNotExist:
      std::cerr << "cd error: \"" << new_path << "\" does not exist"
                << std::endl;
      return;
      break;
    }
  }

  try {
    change_dir_internal(m_directory);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

std::string Shell::prompt() {
  std::string prompt = m_left;
  size_t user_pos = prompt.find("${USER}");
  prompt.replace(user_pos, 7, get_username_of_running_user());
  size_t host_pos = prompt.find("${HOST}");
  prompt.replace(host_pos, 7, get_hostname_of_running_host());
  size_t directory_pos = prompt.find("${DIRECTORY}");
  prompt.replace(directory_pos, 12, m_directory);

  return prompt;
}
