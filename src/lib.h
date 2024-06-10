#ifndef LIB_H

#define LIB_H

#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS
const char PATH_SEPARATOR = '\\';
#else
#define OS_UNIX
const char PATH_SEPARATOR = '/';
#endif

enum class DirectoryStatus {
  DirectoryExists,
  DirectoryIsFile,
  DirectoryExistsButUnknownFormat,
  DirectoryDoesNotExist,
};

void change_dir_internal(const std::string&);

std::string join_path(const std::string&, const std::string&);

DirectoryStatus file_or_directory_exists_in_directory(const std::string&);

#endif // !LIB_H
