#include "inventory.h"

#define MAX_ITEMS 0xFF

#include <string.h>
#include <stdlib.h>

static PIECE *inventory[MAX_ITEMS];
static PIECE **inv_ptr = inventory;

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
)
{
    PIECE *ret = (PIECE*) malloc(1 * sizeof(PIECE));
    ret->type = type;
    ret->name = strdup(description);
    ret->author = strdup(author);
    ret->releaseYear = releaseYear;
    ret->totalHeld = totalHeld;
    ret->totalOut = totalOut;
    ret->description = strdup(description);
    ret->readingLevel = readingLevel;
    ret->numPages = numPages;
    ret->checkoutFee = checkoutFee;
    ret->lostFee = lostFee;

    size_t size = (totalHeld + totalOut) * sizeof(HOLDER);
    ret->holders = (HOLDER*) malloc(size);
    if(ret->holders == NULL)
    {
        free((void*) ret);
        ret = NULL;
        return NULL;
    }

    (*inv_ptr) = ret;
    inv_ptr++;

    return ret;
}

const int amend_inventory_amount(PIECE *piece, const int totalHeld, const int totalOut)
{
    if(piece == NULL)
        return -1;
    
    piece->totalHeld = totalHeld;
    piece->totalOut = totalOut;

    size_t size = (totalHeld + totalOut) * sizeof(HOLDER);
    piece->holders = (HOLDER*) realloc((void*) piece->holders, size);
    if(piece->holders == NULL)
        return -1;

    return 0;
}

const int clean_inventory(void)
{
    int i = 0;
    size_t size = (size_t)(inventory - inv_ptr);

    for(; i < size; i++)
    {
        free((void*) inventory[i]);
        inventory[i] == NULL;
    }

    return 0;
}