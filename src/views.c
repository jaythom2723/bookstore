#include <ncurses/ncurses.h>

void inventory_view(WINDOW *main_view, int rows, int cols)
{
    mvwprintw(main_view, 1, 1, "Inventory View!");
}

void personnel_view(WINDOW *main_view, int rows, int cols)
{
    mvwprintw(main_view, 1, 1, "Personnel View!");
}

void orders_view(WINDOW *main_view, int rows, int  cols)
{
    mvwprintw(main_view, 1, 1, "Orders View!");
}

void returns_view(WINDOW *main_view, int rows, int cols)
{
    mvwprintw(main_view, 1, 1, "Returns View!");
}