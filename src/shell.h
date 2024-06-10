#ifndef SHELL_H

#define SHELL_H

#include "colors.h"
#include <cstring>
#include <iostream>
#include <string>

class Shell {
private:
  const std::string m_left{};
  /*const std::string m_right{};*/ // This is an advanced feature to be added
                                   // after completing the shell execution
                                   // pipeline
  std::string m_directory{};

public:
  Shell(const std::string&, const std::string&);

  void update_directory(const std::string&);

  std::string prompt();
};

#endif // !PROMPT_H
