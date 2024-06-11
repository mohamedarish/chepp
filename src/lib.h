#ifndef LIB_H

#define LIB_H

#include <cstdlib>
#include <string>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
const char PATH_SEPARATOR = '/';

enum class DirectoryStatus {
  DirectoryExists,
  DirectoryIsFile,
  DirectoryExistsButUnknownFormat,
  DirectoryDoesNotExist,
};

void change_dir_internal(const std::string&);

std::string join_path(const std::string&, const std::string&);

DirectoryStatus file_or_directory_exists_in_directory(const std::string&);

std::string get_username_of_running_user();

std::string get_hostname_of_running_host();

std::string get_current_directory();

std::string replace_tokens(std::string&);

#endif // !LIB_H
