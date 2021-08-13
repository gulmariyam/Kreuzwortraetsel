#include "crossword.h"

// Wie viele Wörter (horizontal / vertikal) gehen durch die Koordinate x,y?
int get_count(int x, int y, crossword* cross, int hor){		// x,y >= 0
    countList*current = NULL;

    if(hor >= 1){
        current = cross->count_hor;
    }
    else{
        current = cross->count_ver;
    }

    for(int i = 0; i < x && current != NULL; i++){
        current = current->next;
    }

    if(current == NULL){
        return -1;
    }

    return current->row[y];
}

// Inkrementiere / Dekrementiere count der Wörter die Horizontal/Vertikal durch (x,y) gehen
// -2 < val < 2
void inc_count(int x, int y, crossword* cross, int val, int hor){
    if(x > cross->num_rows - 1 || x < 0 || y < 0 || y > 19)
    {
        return;
    }

    countList*cur = (hor >= 1) ? cross->count_hor : cross->count_ver;
    for(int i=0; i < x && cur!=NULL; i++){
        cur = cur->next;
    }

    if(cur == NULL) {
        return;
    }
    if(cur->row[y]+val >= 0){   // dürfen nicht unter 0 gehen
        cur->row[y]+= val;
    }
    else{
        cur->row[y] = 0;
    }
}

// Welcher buchstabe steht an der Koordinate x,y?
char get_letter(int x, int y, crossword *cross){
    if(x < 0 || y < 0 || y > 19){
        return '\0';
    }

    charList*cur = cross->char_row;

    for(int i = 0;i < x && cur != NULL; i++) {
        cur = cur->next;
    }

    if(cur == NULL){
        return '\0';
    }

    return cur->row[y];
}

//Setz Buchstabe an der Koordinate x,y
void set_letter(int x, int y, char letter, crossword *cross){
    charList* cur = cross->char_row;
    for(int i = 0; i < x && cur != NULL; i++){
        cur = cur->next;
    }

    if(cur!=NULL){
        cur->row[y] = letter;
    }
    else{
        return;
    }
}

// Prüfen, ob Wort eingefögt werden kann
int can_insert_word(crossword* cross, word*w, int horizontal, int x, int y, int is_first_word){
    int kreuzwort_gefunden = 0;

    int l_h = horizontal >= 1 ? 1 : 0;
    int l_v = horizontal >= 1 ? 0 : 1;

    if(y + l_h * (strlen(w->str)) > 20)
        return -1;

    for (int i = 0; i < strlen(w->str); i++){

            char buchstabe = w->str[i];
            char zelle = get_letter(x+ l_v*i,y + l_h*i,cross);
            char nachbar_oben = get_letter(x + l_v*i - 1,y + l_h*i,cross);
            char nachbar_unten = get_letter(x + l_v*i + 1,y + l_h*i,cross);
            char nachbar_links = get_letter(x + l_v*i,y + l_h*i - 1,cross);
            char nachbar_rechts = get_letter(x + l_v*i,y + l_h*i + 1,cross);

            int kreuzwort_hier = 0;
            int kreuzwort_rechts = 0;
            int kreuzwort_links = 0;
            int kreuzwort_unten = 0;
            int kreuzwort_oben = 0;

            int hier_frei = zelle == ' ' || zelle == '\0' ? 1 : 0;
            int unten_frei = (nachbar_unten == ' ' || nachbar_unten == '\0') ? 1 : 0 ;
            int oben_frei = (nachbar_oben == ' ' || nachbar_oben == '\0') ? 1 : 0 ;
            int links_frei = (nachbar_links == ' ' || nachbar_links == '\0') ? 1 : 0 ;
            int rechts_frei = (nachbar_rechts == ' ' || nachbar_rechts == '\0') ? 1 : 0 ;

            //int h = get_count(x+ l_v*i,y + l_h*i,cross,horizontal >= 1 ? 0 : 1);

            if(zelle == buchstabe && get_count(x+ l_v*i,y + l_h*i,cross,horizontal >= 1 ? 0 : 1) > 0){
                kreuzwort_hier = 1;
            }

            if(horizontal >= 1) {
                // das Wort soll horizontal ausgerichtet werden

                if(i>0 && nachbar_links == w->str[i-1] && get_count(x+ l_v*i,y + l_h*i - 1,cross,0) > 0){
                    kreuzwort_links = 1;
                }
                if(i<strlen(w->str)-1 && nachbar_rechts == w->str[i+1] && get_count(x+ l_v*i,y + l_h*i + 1,cross,0) > 0){
                    kreuzwort_rechts = 1;
                }


                if(kreuzwort_hier && rechts_frei && links_frei){
                    kreuzwort_gefunden = 1;
                    continue;
                }

                if(kreuzwort_links && hier_frei && rechts_frei && oben_frei && unten_frei){
                    continue;
                }

                if(kreuzwort_rechts && hier_frei && links_frei && oben_frei && unten_frei){
                    continue;
                }

                if(kreuzwort_rechts && kreuzwort_links && oben_frei && unten_frei){
                    continue;
                }

                if(hier_frei && unten_frei && oben_frei && rechts_frei && links_frei){
                    continue;
                }

                return -1;
            }
            else {
                // das Wort soll vertikal ausgerichtet werden
                if(i>0 && nachbar_oben == w->str[i-1] && get_count(x+ l_v*i - 1,y + l_h*i,cross,1) > 0){
                    kreuzwort_oben = 1;
                }
                if(i<strlen(w->str)-1 && nachbar_unten == w->str[i+1] && get_count(x+ l_v*i + 1,y + l_h*i,cross,1) > 0){
                    kreuzwort_unten = 1;
                }

                if(kreuzwort_hier && oben_frei && unten_frei){
                    kreuzwort_gefunden = 1;
                    continue;
                }

                if(hier_frei && kreuzwort_unten && rechts_frei && links_frei && oben_frei){
                    continue;
                }

                if(hier_frei && kreuzwort_oben && rechts_frei && links_frei && unten_frei){
                    continue;
                }

                if(hier_frei && kreuzwort_unten && kreuzwort_oben && links_frei && rechts_frei){
                    continue;
                }

                if(hier_frei && links_frei && rechts_frei && unten_frei && oben_frei){
                    continue;
                }

                return -1;
            }

    }

    if(kreuzwort_gefunden >= 1 || is_first_word >= 1 ){
        return 1;
    }
    else{
        return 0;
    }

}

// Wort einfügen
int insertWord(crossword*cross,int x,int y,word* w, int horizontal){
    // zuerst fehlende Zeilen anfügen
    int l_v = horizontal >= 1 ? 0 : 1;
    int l_h = horizontal >= 1 ? 1 : 0;

    // erst fehlende Zeilen einfügen
    for(int i = 0; i < x + l_v*(strlen(w->str)); i++){
        if(cross->num_rows <= i + 1){
            crossword_append_row(cross);
        }
    }

    for(int i = 0; i<strlen(w->str); i++){
        set_letter(x + l_v*i,y + l_h*i,w->str[i],cross);
        inc_count(x + l_v*i,y + l_h*i,cross,+1,horizontal);
    }

    w->x = x;
    w->y = y;
    
    return 0;
}

//Wort entfernen
void delete_word(crossword* cross, word* w, int x, int y) {
    int l_h = (w->hor) >= 1 ? 1 : 0;
    int l_v = (w->hor) >= 1 ? 0 : 1;

    for(int i=0; i<strlen(w->str); i++){

        inc_count(x + l_v*i, y + l_h*i,cross, -1, w->hor);

        if(get_count(x + l_v*i, y + l_h*i, cross, w->hor >= 1 ? 0 : 1) <= 0){
              // wenn keine wörter mit entgegensetzter Ausrichtung
              set_letter(x + l_v*i, y + l_h*i, ' ', cross);
        }
    }

    w->x = -1;
    w->y = -1;
}

crossword*init_crossword(){
    charList*char_row = init_charList();
    countList*count_hor = init_countList();
    struct countList*count_ver = init_countList();

    crossword*cross = malloc(sizeof(crossword));

    cross->char_row = char_row;
    cross->count_hor = count_hor;
    cross->count_ver = count_ver;
    cross->num_rows = 1;

    return cross;
}

void crossword_append_row(crossword*cross){
    countList_append_row(cross->count_ver);
    countList_append_row(cross->count_hor);
    charList_append_row(cross->char_row);
    cross->num_rows++;
}

void free_crossword(crossword*cross){
    freigeben_charList(cross->char_row);
    freigeben_countList(cross->count_ver);
    freigeben_countList(cross->count_hor);
    free(cross);
}

int generate_crossword_from_list(word_list*head,crossword*cross, int limit, int first_word){        // 100 * max(länge)
    if(head == NULL){
        return 1;
    }

    for(int x = 0; x<cross->num_rows && x <= limit; x++){
        for(int y = 0; y < 20; y++){
            if(can_insert_word(cross,head->w,head->w->hor,x,y,first_word) >= 1){
                insertWord(cross,x,y,head->w,head->w->hor);
                if(generate_crossword_from_list(head->next,cross,limit, 0) <= 0){  // Konnte Wort nicht einfügen
                    delete_word(cross,head->w,head->w->x,head->w->y);
                }
                else{
                    return 1;
                }
            }
        }
    }

    return 0;
}

void print_crossword_from_word_list(crossword*cross, FILE*ausgabe, word_list*l){
    charList*cur = cross->char_row;
    char*str = malloc(21*sizeof(char));

    for(int i= 0; i< word_list_len(l); i++){
        l = l->next;
    }

    for(int i = 0; i < cross->num_rows; i++){
        int not_empty = 0;

        for(int j = 0; j < 20; j++){
            str[j] = cur->row[j];
            if(str[j] != ' '){
                not_empty = 1;
            }
        }

        if(not_empty <= 0){
            break;
        }

        str[20] = '\0';

        fprintf(ausgabe,"%s\n", str);

        cur = cur->next;
    }

    free(str);


    //fprintf(ausgabe,)
}
