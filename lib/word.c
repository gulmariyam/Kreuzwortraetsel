
#include "word.h"
const int BUFLEN = 101;

word_list*init_word_list(char*word_str, int hor){
    word*w = malloc(sizeof(word));
    w->str = word_str;
    w->x = -1;
    w->y = -1;
    w->hor = hor;

    word_list*elem = malloc(sizeof(word_list));
    elem->w = w;
    elem->next = NULL;

    return elem;
}

void word_freigeben(word*w){
    free(w->str);
    free(w);
}

void wort_list_freigeben(word_list*head){
    word_list*elem = head;
    while(head!=NULL){
        word_freigeben(head->w);
        elem = head->next;
        free(head);
        head=elem;
    }
}

void clean_buf(char*buf,int len){
    for(int i = 0; i < len; i++){
        buf[i] = ' ';
    }
}

word_list* woerter_einlesen(FILE *eingabe)
{
    char buf[BUFLEN];   // buf enthält 99 Zeichen. buf[99] enthält '\0', da buf ein string ist
    char ausrichtung;
    int err = 0;
    word_list*head = NULL;
    word_list*last = NULL;

    clean_buf(buf,BUFLEN);

    while(fgets(buf,BUFLEN,eingabe)) {          // Zeile einlesen
        char*wort = malloc((BUFLEN-2)*sizeof(char));    // String initialisieren
        clean_buf(wort,BUFLEN-2);

        err = split_buf(buf,wort,&ausrichtung);   // wort ist string und nicht nur eine Zeichenkette

        if(err >= 1 ){
            if(head != NULL)
            	wort_list_freigeben(head);
            free(wort);
            return NULL;
        }

        if(head == NULL) {
            if(ausrichtung == 'h') {
                head = init_word_list(wort, 1);
                last = head;
            }
            else if(ausrichtung == 'v') {
                head = init_word_list(wort, 0);
                last = head;
            }
        }
        else {
            if(ausrichtung == 'h') {
                last->next = init_word_list(wort, 1);
                last = last->next;
            }
            else if(ausrichtung == 'v') {
                last->next = init_word_list(wort, 0);
                last = last->next;
            }
        }

    }

    return head;
}

int split_buf(char*buf, char*wort, char*ausrichtung){
    int err = 0;
    int i = 0;

    // Zuerst Wort einlesen
    while(buf[i] != ' ' && buf[i] != '\0'){
        wort[i] = buf[i];
        i++;
    }
    wort[i] = '\0';

    // Dann Ausrichtung
    if(i+1 < strlen(buf) && buf[i] == ' ' ){
        *ausrichtung = buf[i+1];

        if(i+2 < strlen(buf) && !(buf[i+2] == ' ' || buf[i+2] == '\n')){
            // Faslche Eingabe: ausrichtung darf nur ein Zeichen sein
            //char debug_c = buf[i+2];
            err = 1;
        }
    }
    else{
        // Falsche Eingabe: Ausrichtung nicht definiert
        *ausrichtung = '\0';
        err = 1;
    }

    if(*ausrichtung != 'v' && *ausrichtung != 'h'){
        //Faslche Eingabe : Ausrichtung falsch definiert
        err = 1;
    }

    return err;
}

int find_max_word_len(word_list*head){
    int max = 0;
    while(head!=NULL){
        if(strlen(head->w->str) > max){
            max = strlen(head->w->str);
        }
        head = head->next;
    }
    return max;
}

int word_list_len(word_list*head){
    int count = 0;
    while(head != NULL){
        head = head->next;
        count++;
    }
    return count;
}
