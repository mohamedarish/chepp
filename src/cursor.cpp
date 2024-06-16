#include "cursor.h"
#include <iostream>

void move_cursor_left(int spaces) {
  for (int i = 0; i < spaces; ++i) {
    std::cout << MOVE_LEFT;
  }
  std::cout.flush();
}

void move_cursor_right(int spaces) {
  for (int i = 0; i < spaces; ++i) {
    std::cout << MOVE_RIGHT;
  }
  std::cout.flush();
}
