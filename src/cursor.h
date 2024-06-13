#ifndef CURSOR_H

#define CURSOR_H

#define MOVE_LEFT "\033[D";
#define MOVE_RIGHT "\033[C";
#define SAVE_CURSOR "\033[s";
#define RESTORE_CURSOR "\033[u";
#define CLEAR_LINE "\033[K";

void move_cursor_left(int);

void move_cursor_right(int);

void get_cursor_position(int&, int&);

#endif // !CURSOR_H
