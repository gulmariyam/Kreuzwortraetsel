#include "list.h"

charList* init_charList() {
    charList* element = malloc(sizeof(charList));
    element->row = malloc(20*sizeof(char));
    for(int i = 0; i < 20; i++) {
        element->row[i] = ' ';
    }
    element->next = NULL;

    return element;
}

countList* init_countList() {
    countList* element = malloc(sizeof(countList));
    element->row = malloc(20*sizeof(int));
    for(int i = 0; i < 20; i++) {
        element->row[i] = 0;
    }
    element->next = NULL;

    return element;
}

void freigeben_countList(countList* head) {
    countList* next;
    while(head != NULL) {
        free(head->row);
        next = head->next;
        free(head);
        head = next;
    }
}

void freigeben_charList(charList* head) {
    charList* next = NULL;
    while(head != NULL) {
        free(head->row);
        next = head->next;
        free(head);
        head = next;
    }
}

void countList_append_row(countList*head){
    while(head->next != NULL){
        head = head->next;
    }
    head->next = init_countList();
}

void charList_append_row(charList*head){
    while(head->next != NULL){
        head = head->next;
    }
    head->next = init_charList();
}

