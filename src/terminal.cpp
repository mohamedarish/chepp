#include "terminal.h"
#include "cursor.h"
#include "lib.h"
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

Terminal::Terminal(Shell& shell, struct termios& original_termios)
    : m_shell{shell}, m_original_termios(original_termios) {
  enable_raw_mode(m_original_termios);
}

Terminal::~Terminal() { disable_raw_mode(m_original_termios); }

std::string Terminal::read_user_input() {
  std::string command{};
  unsigned long cursor = 0;
  while (true) {
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    if (c == 127) {
      if (cursor > 0) {
        cursor--;
        command.pop_back();
        print_output("\b \b");
      } else {
        print_output("\a");
      }
    } else if (c == '\r' || c == '\n') {
      print_output(std::string(1, '\n'));
      break;
    } else if (c == '\x1b') {
      char seq[2];
      if (read(STDIN_FILENO, &seq[0], 1) == -1)
        continue;
      if (read(STDIN_FILENO, &seq[1], 1) == -1)
        continue;

      if (seq[0] == '[') {
        switch (seq[1]) {
        case 'A':
          // TODO: Implement history
          break;
        case 'B':
          // TODO: Implement history
          break;
        case 'C':
          if (cursor < command.length()) {
            cursor += 1;
            move_cursor_right(1);
          }
          break;
        case 'D':
          if (cursor > 0) {
            cursor -= 1;
            move_cursor_left(1);
          }
          break;
        }
      }
    } else {
      print_output(std::string(1, c));
      /*if (cursor < command.length()) {*/
      /*  print_output(command.substr(cursor));*/
      /*  move_cursor_left(static_cast<int>(command.length() - cursor -
         1));*/
      /*command.insert(cursor, &c);*/
      /*} else {*/
      command.push_back(c);
      /*}*/
      cursor++;
    }
  }
  return command;
}

void Terminal::print_output(const std::string& output) {
  std::cout << output;
  std::cout.flush();
}

void Terminal::update_directory(const std::string& new_directory) {
  m_shell.update_directory(new_directory);
}
