#include <ncursesw/ncurses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys.h"
#include "sidebar.h"
#include "main_view.h"

int rows, cols;
// 0: sidebar input (up and down arrows change sidebar cursor and main window contents)
// 1: main window inputs (arrows move the cursor to different items)
int cur_input_mode = 0;
int running = 1;

WINDOW *sidebar;
WINDOW *view;

void _initialize(void);
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

    sidebar = create_sidebar(rows, cols);
    view = create_main_view(rows, cols);
    keypad(sidebar, TRUE);
    keypad(view, TRUE);
    nodelay(stdscr, TRUE);
    nodelay(sidebar, TRUE);
    nodelay(view, TRUE);
}

void _print_function_ops(void)
{
    mvprintw(rows - 1, 0, "F1> Exit;");
    mvprintw(rows - 1, strlen("F1> Exit;"), "F2> Input Mode;");
    refresh();
}

void _destroy_window(WINDOW *window)
{
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}