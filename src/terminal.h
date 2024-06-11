#ifndef TERMINAL_H

#define TERMINAL_H

#include "curses.h"
#include "shell.h"
#include <sys/termios.h>
#include <sys/types.h>
#include <termios.h>

#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

class Terminal {
private:
  int m_x{}, m_y{}, m_height{}, m_width{};
  Shell m_shell;
  struct termios m_original_termios;

public:
  Terminal(Shell shell);
  ~Terminal();

  Shell shell() { return m_shell; }

  int get_x() { return m_x; }
  int get_y() { return m_y; }

  void update_directory(const std::string&);

  void move_x(int new_x) { m_x = new_x; }
  void move_y(int new_y) { m_y = new_y; }

  std::string read_user_input();

  void print_output(const std::string&);

  void update_cursor_position();
};

#endif // !TERMINAL_H
