#include "lib.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <sys/termios.h>
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

std::string get_username_of_running_user() {
  const char* username = getenv("USER");
  if (username == nullptr) {
    username = getenv("USERNAME");
  }
  return (username != nullptr) ? std::string(username) : "unknown";
}

std::string get_hostname_of_running_host() {
  char hostname[1024];
  if (gethostname(hostname, sizeof(hostname)) == 0) {
    return std::string(hostname);
  } else {
    return "unknown";
  }
}

std::string get_current_directory() {
  char buffer[PATH_MAX];
  if (getcwd(buffer, sizeof(buffer)) != nullptr) {
    return std::string(buffer);
  } else {
    throw std::runtime_error("Error getting current directory");
  }
}

void set_cursor_position(int row, int column) {
  std::cout << "\033[" << row << ";" << column << "H";
  std::cout.flush();
}

void enable_raw_mode(struct termios& original_termios) {
  tcgetattr(STDIN_FILENO, &original_termios);
  struct termios raw = original_termios;
  raw.c_lflag &= ~(static_cast<tcflag_t>(ICANON | ECHO));
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios& original_termios) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}
