#include "sidebar.h"

#include "keys.h"

#include <stdlib.h>
#include <string.h>

#define MAX_OPTIONS 15

int sb_height, sb_width;
static int cursor = 0;
static int active = 0;
static int last_cursor = 0;

char *options[MAX_OPTIONS] = {
    "Inventory    ",
    "Personnel    ",
    "Orders       ",
    "Returns      "
};

void change_cursor(WINDOW *sidebar, int key)
{
    switch(key)
    {
        case CKEY_UARROW:
            if(cursor - 1 < 0)
                cursor = 0;
            else
                cursor--;
            break;
        case CKEY_DARROW:
            if(cursor + 1> MAX_OPTIONS || options[cursor + 1] == NULL)
                cursor = cursor;
            else
                cursor++;
            break;
        case CKEY_ENTER:
            active = cursor;
            break;
    }

    if(last_cursor != cursor)
    {
        wclear(sidebar);
        box(sidebar, 0, 0);
        print_options(sidebar);
        wrefresh(sidebar);
        last_cursor = cursor;
    }
}

void print_options(WINDOW *sidebar)
{
    int i = 0;

    for(; i < MAX_OPTIONS; i++)
    {
        if(options[i] == NULL)
            break;

        if(cursor == i) wattron(sidebar, COLOR_PAIR(1));
        
        if(active == i)
        {
            mvwprintw(sidebar, i + 1, 1, options[i]);
            mvwprintw(sidebar, i + 1, strlen(options[i]), ">");
        } else
        {
            mvwprintw(sidebar, i + 1, 1, options[i]);
        }

        if(cursor == i) wattroff(sidebar, COLOR_PAIR(1));
    }
}

int get_active_option(void)
{
    return active;
}