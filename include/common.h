#ifndef COMMON_H
#define COMMON_H

#define CLEAR_WINDOW(window) werase(window); box(window, 0, 0)

typedef struct {
    int year;
    int month;
    int day;
} DATE;

#endif // COMMON_H