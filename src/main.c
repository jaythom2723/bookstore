#include <ncursesw/ncurses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "keys.h"
#include "sidebar.h"
#include "main_view.h"

#define NUM_OPTIONS 2

int rows, cols;
// 0: sidebar input (up and down arrows change sidebar cursor and main window contents)
// 1: main window inputs (arrows move the cursor to different items)
int cur_input_mode = 0;
int running = 1;

extern int sb_height, sb_width;
extern int mv_height, mv_width;

WINDOW *sidebar;
WINDOW *view;

static const char *options[NUM_OPTIONS] = {
    "F1> Exit;",
    "F2> Input Mode;"
};

void _initialize(void);
/// @brief create an ncurses window
/// @param sw Start Width
/// @param sh Start Height
/// @param x x position of the window
/// @param y y position of the window
/// @param rw Returned Width
/// @param rh Returned Height
/// @return an ncurses window
WINDOW *_create_window(const int sw, const int sh, const int x, const int y, int *rw, int *rh);
void _destroy_window(WINDOW *window);
void _print_function_ops(void);
void _change_input_mode(int *ch);
void _handle_special_characters(const int ch);

int main(void)
{
    int ch;
    _initialize();

    while(running == 1)
    {
        _print_function_ops();

        wrefresh(sidebar);
        box(sidebar, 0, 0);

        wrefresh(view);
        box(view, 0, 0);

        if(cur_input_mode == 0)
        {
            change_cursor(sidebar, ch);
            print_options(sidebar);
            wrefresh(sidebar);
        }

        _change_input_mode(&ch);
        _handle_special_characters(ch);
        change_view(get_active_option());

        CLEAR_WINDOW(view);
        show_view(view);

        mvprintw(rows - 1, cols - 2, "%d", ch);
        refresh();
    }

    _destroy_window(sidebar);
    _destroy_window(view);
    endwin();

    return 0;
}

void _change_input_mode(int *ch)
{
    switch(cur_input_mode)
    {
        case 0:
            (*ch) = wgetch(sidebar);
            break;
        case 1:
            (*ch) = wgetch(view);
            break;
    }
}

void _handle_special_characters(const int ch)
{
    if(ch == CKEY_F1)
        running = 0;
    if(ch == CKEY_F2)
    {
        if(cur_input_mode >= 1)
            cur_input_mode = 0;
        else
            cur_input_mode = 1;
    }
}

void _initialize(void)
{
    initscr();
    if(has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color!\n");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);    
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    getmaxyx(stdscr, rows, cols);

    sidebar = _create_window(
        15, 
        rows - 1, 
        0, 
        0, 
        &sb_width, 
        &sb_height
    );
    
    view = _create_window(
        cols - sb_width - 2, 
        rows - 1, 
        sb_width + 1, 
        0, 
        &sb_width, 
        &sb_height
    );

    keypad(sidebar, TRUE);
    keypad(view, TRUE);
    nodelay(stdscr, TRUE);
    nodelay(sidebar, TRUE);
    nodelay(view, TRUE);
}

void _print_function_ops(void)
{
    int i = 0;
    int xoff = 0; // x offset
    for(; i < NUM_OPTIONS; i++)
    {
        if (i - 1 >= 0)
            xoff = strlen(options[i - 1]);

        mvprintw(rows - 1, xoff, options[i]);
    }

    refresh();
}

void _destroy_window(WINDOW *window)
{
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}

WINDOW *_create_window(const int sw, const int sh, const int x, const int y, int *rw, int *rh)
{
    (*rw) = sw;
    (*rh) = sh;

    WINDOW *win = newwin(sh, sw, y, x);
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