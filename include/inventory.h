#ifndef INVENTORY_H
#define INVENTORY_H

#include "common.h"

typedef enum {
    BOOK, 
    AUDIO_BOOK, 
    PASS
} PIECETYPE;

typedef struct {
    const char *name;
    int age;
    DATE dateToReturn;
} HOLDER;

typedef struct inventory_piece
{
    PIECETYPE type;
    const char *name;
    const char *author;
    int releaseYear;
    int totalHeld;
    int totalOut;
    const char *description; 
    char readingLevel;
    int numPages;
    float checkoutFee;
    float lostFee;
    HOLDER *holders;
} PIECE;

PIECE *create_inventory_item(
    const PIECETYPE type, 
    const char *name, 
    const char *author, 
    const int releaseYear, 
    const int totalHeld, 
    const int totalOut, 
    const char *description, 
    const char readingLevel, 
    const int numPages, 
    const float checkoutFee, 
    const float lostFee
);
const int amend_inventory_amount(PIECE *piece, const int totalHeld, const int totalOut);

const int clean_inventory(void);

#endif // INVENTORY_H