#ifndef LIB_H

#define LIB_H

#include <string>
#include <termios.h>

const char PATH_SEPARATOR = '/';

enum class DirectoryStatus {
  DirectoryExists,
  DirectoryIsFile,
  DirectoryExistsButUnknownFormat,
  DirectoryDoesNotExist,
};

void change_dir_internal(const std::string& new_path);

std::string join_path(const std::string& user_input,
                      const std::string& old_path);

DirectoryStatus
file_or_directory_exists_in_directory(const std::string& full_path);

std::string get_username_of_running_user();

std::string get_hostname_of_running_host();

std::string get_current_directory();

// Replace tokens for making prompts interactive
/*std::string replace_tokens(std::string&);*/

void enable_raw_mode(struct termios& original_termios);

void disable_raw_mode(struct termios& original_termios);

void replace_colors(std::string& prompt);

#endif // !LIB_H
