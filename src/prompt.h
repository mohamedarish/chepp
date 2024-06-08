#ifndef PROMPT_H

#define PROMPT_H

#include <iostream>
#include <string>

class Prompt {
  private:
    const std::string m_left{};
    const std::string m_right{};
    std::string m_directory{};

  public:
    Prompt(const std::string& left, const std::string& right,
           const std::string& directory)
        : m_left{left}, m_right{right}, m_directory{directory} {}

    void update_directory(std::string_view new_directory);
};

#endif // !PROMPT_H
