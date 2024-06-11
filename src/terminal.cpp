#include "terminal.h"

std::string Terminal::read_user_input() {
  std::string user_input{};

  int ch;
  while ((ch = getch()) != '\n') {
    switch (ch) {
    case KEY_LEFT:
      if (this->m_x > 0) {
        (this->m_x)--;
        move(this->m_y, this->m_x);
      }
      break;
    case KEY_RIGHT:
      (this->m_x)++;
      move(this->m_y, this->m_x);
      break;
    case KEY_BACKSPACE:
      if (this->m_x > 0) {
        (this->m_x)--;
        delch();
      }
      break;
    default:
      user_input.insert(static_cast<unsigned long>((this->m_x)++), 1,
                        static_cast<char>(ch));
      std::string output{};
      output.push_back(static_cast<char>(ch));
      this->print_output(output);
      break;
    }
  }

  this->m_x = 0;

  return user_input;
}

void Terminal::print_output(const std::string& output) {
  mvaddstr((this->m_x)++, (this->m_y), output.c_str());
}

void Terminal::update_directory(const std::string& new_directory) {
  this->shell().update_directory(new_directory);
}
