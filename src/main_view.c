#include "main_view.h"

#include "sidebar.h"

#include <stdio.h>
#include <stdlib.h>

#define NUM_VIEWS 4

extern void inventory_view(WINDOW *main_view, int rows, int cols);
extern void personnel_view(WINDOW *main_view, int rows, int cols);
extern void orders_view(WINDOW *main_view, int rows, int cols);
extern void returns_view(WINDOW *main_view, int rows, int cols);

int mv_height, mv_width;
static VIEWSCREEN cur_view = INVENTORY;
static VIEW views[NUM_VIEWS] = {
    &inventory_view,
    &personnel_view,
    &orders_view,
    &returns_view
};


void show_view(WINDOW *main_view)
{
    (*(views[cur_view]))(main_view, mv_height, mv_width);
}

VIEWSCREEN get_current_view(void)
{
    return cur_view;
}

void change_view(VIEWSCREEN view_screen)
{
    cur_view = view_screen;
}
