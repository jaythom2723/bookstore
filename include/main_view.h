#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <ncurses/ncurses.h>

typedef enum {
    INVENTORY,
    PERSONNEL,
    ORDERS,
    RETURNS
} VIEWSCREEN;

WINDOW *create_main_view(int rows, int cols);
void destroy_main_view(WINDOW *main_view);

#endif // MAIN_VIEW_H