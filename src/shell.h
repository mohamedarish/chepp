#ifndef SHELL_H

#define SHELL_H

#include <iostream>
#include <string>
#include <string_view>

class Shell {
private:
  const std::string m_left{};
  /*const std::string m_right{};*/ // This is an advanced feature to be added
                                   // after completing the shell execution
                                   // pipeline
  std::string m_directory{};

public:
  Shell(const std::string& left, const std::string& directory)
      : m_left{left}, m_directory{directory} {}

  void update_directory(std::string_view new_directory);

  constexpr std::string_view prompt() { return m_left; }
};

#endif // !PROMPT_H
