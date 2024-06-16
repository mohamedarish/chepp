#ifndef SHELL_H

#define SHELL_H

#include <string>
class Shell {
private:
  std::string m_left{};
  /*const std::string m_right{};*/ // This is an advanced feature to be added
                                   // after completing the shell execution
                                   // pipeline
  std::string m_directory{};

public:
  Shell();

  void update_directory(const std::string& new_directory);

  std::string prompt();
};

#endif // !PROMPT_H
