#include "cd.h"

bool change_directory(Shell& shell, std::string new_path) {

  shell.update_directory(new_path);

  return true;
}
