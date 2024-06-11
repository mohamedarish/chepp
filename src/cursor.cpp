#include "cursor.h"

void move_cursor_left(int n) {
  for (int i = 0; i < n; ++i) {
    std::cout << MOVE_LEFT;
  }
}

void move_cursor_right(int n) {
  for (int i = 0; i < n; ++i) {
    std::cout << MOVE_RIGHT;
  }
}

void insert_text(char* buffer, int& buffer_size, char c, int& cursor_position) {
  for (int i = buffer_size; i > cursor_position; --i) {
    buffer[i] = buffer[i - 1];
  }

  buffer[cursor_position++] = c;

  buffer_size++;

  std::cout << c;
  move_cursor_right(1);

  std::cout << buffer + cursor_position;

  move_cursor_left(buffer_size - cursor_position);
}

void get_cursor_position(int& x, int& y) {
  std::cout << "\033[6n";
  std::cout.flush();

  char buf;
  int index = 0;
  char response[32] = {'\0'};

  while (true) {
    std::cin.get(buf);
    if (buf == 'R')
      break;
    response[index++] = buf;
  }
  int row{}, column{};
  sscanf(response, "\033[%d;%d", &row, &column);
  x = column;
  y = row;
}
