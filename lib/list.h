

#ifndef CROSSWORD_LIST_H
#define CROSSWORD_LIST_H

#endif //CROSSWORD_LIST_H

#include <stdlib.h>

typedef struct charList {
    char* row; // malloc
    struct charList* next;
} charList;

typedef struct countList {
    int* row;
    struct countList* next;
} countList;


charList* init_charList(void);
countList* init_countList(void);
void countList_append_row(countList*);
void charList_append_row(charList*);
void freigeben_countList(countList*);
void freigeben_charList(charList*);
