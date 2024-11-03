#include "main_view.h"

#include "sidebar.h"

#include <stdio.h>
#include <stdlib.h>

static int height, width;
static VIEWSCREEN cur_view = INVENTORY;

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

void destroy_main_view(WINDOW *main_view)
{
    wborder(main_view, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(main_view);
    delwin(main_view);
}