#include "main_view.h"

#include "sidebar.h"

#include <stdio.h>
#include <stdlib.h>

#define NUM_VIEWS 4

extern void inventory_view(WINDOW *main_view, int rows, int cols);
extern void personnel_view(WINDOW *main_view, int rows, int cols);
extern void orders_view(WINDOW *main_view, int rows, int cols);
extern void returns_view(WINDOW *main_view, int rows, int cols);

static int height, width;
static VIEWSCREEN cur_view = INVENTORY;
static VIEW views[NUM_VIEWS] = {
    &inventory_view,
    &personnel_view,
    &orders_view,
    &returns_view
};

WINDOW *create_main_view(int rows, int cols)
{
    height = rows - 1;
    width = cols - get_sidebar_width() - 2;

    WINDOW *win = newwin(height, width, 0, get_sidebar_width() + 1);
    if(win == NULL)
    {
        endwin();
        printf("Could not create the sidebar!\n");
        getc(stdin);
        exit(-5);
    }
    refresh();
    box(win, 0, 0);

    return win;
}

void show_view(WINDOW *main_view)
{
    (*(views[cur_view]))(main_view, height, width);
}

VIEWSCREEN get_current_view(void)
{
    return cur_view;
}

void change_view(VIEWSCREEN view_screen)
{
    cur_view = view_screen;
}

