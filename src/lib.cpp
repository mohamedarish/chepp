#include "lib.h"
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void change_dir_internal(const std::string& new_path) {
  if (chdir(new_path.c_str()) != 0) {
    throw std::runtime_error("Failed to change directory to " + new_path);
  }
}

std::string join_path(const std::string& user_input,
                      const std::string& old_path) {
  if (user_input.empty()) {
    throw std::runtime_error("cd error: Empty path provided as input");
  }

  if (user_input.starts_with(PATH_SEPARATOR)) {
    return user_input;
  }

  if (old_path.ends_with(PATH_SEPARATOR)) {
    return old_path + user_input;
  }

  return old_path + PATH_SEPARATOR + user_input;
}

DirectoryStatus
file_or_directory_exists_in_directory(const std::string& full_path) {
  struct stat fileinfo;

  if (stat(full_path.c_str(), &fileinfo) == 0) {
    if (S_ISREG(fileinfo.st_mode)) {
      return DirectoryStatus::DirectoryIsFile;
    } else if (S_ISDIR(fileinfo.st_mode)) {
      return DirectoryStatus::DirectoryExists;
    } else {
      return DirectoryStatus::DirectoryExistsButUnknownFormat;
    }
  } else {
    return DirectoryStatus::DirectoryDoesNotExist;
  }
}
