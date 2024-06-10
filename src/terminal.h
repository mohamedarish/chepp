#ifndef TERMINAL_H

#define TERMINAL_H

#include "shell.h"
#include <sys/types.h>

#ifdef _WIN32
#include <curses.h>
#include <iostream>
#include <string>
#else
#include <iostream>
#include <ncurses.h>
#include <string>
#endif

class Terminal {
private:
  int m_x{}, m_y{};
  Shell m_shell;

public:
  Terminal(int x, int y, Shell shell) : m_x{x}, m_y{y}, m_shell{shell} {
#ifdef _WIN32
    initscr();
#else
    initscr();
#endif
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    start_color();
    use_default_colors();
  }

  ~Terminal() {
    clear();

    refresh();
    getch();
    endwin();
  }

  Shell shell() { return m_shell; }

  int get_x() { return m_x; }
  int get_y() { return m_y; }

  void update_directory(const std::string&);

  void move_x(int new_x) { m_x = new_x; }
  void move_y(int new_y) { m_y = new_y; }

  std::string read_user_input();

  void print_output(const std::string&);
};

#endif // !TERMINAL_H
