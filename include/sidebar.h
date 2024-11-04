#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <ncurses/ncurses.h>

void change_cursor(WINDOW *sidebar, int key);
void print_options(WINDOW *sidebar);

WINDOW *create_sidebar(int rows, int cols);

int get_sidebar_width(void);
int get_active_option(void);

#endif // SIDEBAR_H