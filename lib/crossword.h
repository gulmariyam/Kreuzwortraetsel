
#ifndef CROSSWORD_CROSSWORD_H
#define CROSSWORD_CROSSWORD_H

#endif //CROSSWORD_CROSSWORD_H

#include <stdio.h>
#include <string.h>

#include "list.h"
#include "word.h"

typedef struct {
    charList *char_row;	// crossword = liste von Zeilen von char
    countList *count_hor;	// count_hor = liste von Zeilen	von ints	[ , , , , ] -> [ , , , , ] -> [ , , , , ] -> [ , , , , ] -> ...
    countList *count_ver;	// count_hor
    int num_rows;
} crossword;

int get_count(int, int , crossword* , int);
void inc_count(int,int,crossword*,int,int);
char get_letter(int, int , crossword *);
void set_letter(int, int, char, crossword*);
int can_insert_word(crossword*,word*,int,int,int,int);
int insertWord(crossword*,int,int,word*,int);
void delete_word(crossword*,word*,int,int);
void crossword_append_row(crossword*);
void print_crossword_from_word_list(crossword*cross, FILE*ausgabe, word_list*);
int generate_crossword_from_list(word_list*,crossword*,int,int);
void free_crossword(crossword*cross);
crossword*init_crossword(void);

