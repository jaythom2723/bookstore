#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <ncurses/ncurses.h>

typedef enum {
    INVENTORY,
    PERSONNEL,
    ORDERS,
    RETURNS
} VIEWSCREEN;

typedef void (*VIEW)(WINDOW *main_view, int rows, int cols);

WINDOW *create_main_view(int rows, int cols);

void show_view(WINDOW *main_view);

VIEWSCREEN get_current_view(void);
void change_view(VIEWSCREEN view_screen);

#endif // MAIN_VIEW_H