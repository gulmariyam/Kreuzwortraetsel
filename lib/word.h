
#ifndef CROSSWORD_WORD_H
#define CROSSWORD_WORD_H

#endif //CROSSWORD_WORD_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char*str;
    int x;  // x-koordinate des Anfangsbuchstabens im Crossword
    int y;  // y-koordinate des Anfangsbuchstabens im Crossword
    int hor; // Ausrichtung im crossword (Vertikal oder Horizontal)
}word;

typedef struct word_list {
    word*w;
    struct word_list*next;
} word_list;

word_list*init_word_list(char*, int hor);
int split_buf(char*, char*, char*);
void clean_buf(char*,int);
word_list* woerter_einlesen(FILE*);
int split_buf(char*, char*, char*);
void wort_list_freigeben(word_list*);
int find_max_word_len(word_list*);
int word_list_len(word_list*);
void word_freigeben(word*w);
