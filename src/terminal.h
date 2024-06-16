#ifndef TERMINAL_H

#define TERMINAL_H

#include "shell.h"
#include <termios.h>

class Terminal {
private:
  Shell m_shell;
  struct termios m_original_termios;

public:
  Terminal(Shell& shell, struct termios& original_termios);
  ~Terminal();

  Shell shell() { return m_shell; }

  void update_directory(const std::string& new_directory);

  std::string read_user_input();

  void print_output(const std::string& output);

  void update_cursor_position();
};

#endif // !TERMINAL_H
