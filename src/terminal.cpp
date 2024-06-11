#include "terminal.h"
#include "cursor.h"
#include "lib.h"
#include <format>
#include <iostream>
#include <sstream>
#include <sys/termios.h>

Terminal::Terminal(Shell shell) : m_shell{shell} {
  struct termios original_termios;
  m_original_termios = original_termios;
  enable_raw_mode(m_original_termios);

  /*get_cursor_position(original_termios, m_x, m_y);*/
}

Terminal::~Terminal() { disable_raw_mode(m_original_termios); }

std::string Terminal::read_user_input() { return "nothing"; }

void Terminal::print_output(const std::string& output) {
  std::cout << output << m_x << ' ' << m_y << ' ';
}

void Terminal::update_cursor_position() {
  get_cursor_position(m_original_termios, m_x, m_y);
}

void Terminal::update_directory(const std::string& new_directory) {
  shell().update_directory(new_directory);
}
