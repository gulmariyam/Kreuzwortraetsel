#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[]) {
    
    if(argc != 3){
    	return 1;
    }
    
    FILE*eingabe = fopen(argv[1], "r");

    if(eingabe == NULL){
    	return 2;
    }
    
    fseek(eingabe, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(eingabe);
    if (len <= 0) {
    	FILE*ausgabe = fopen(argv[2], "w");
    	fclose(ausgabe);
    	fclose(eingabe);
    	return 0;
    }
    
    rewind(eingabe);
    
    word_list*list = woerter_einlesen(eingabe);
    
    if(list == NULL){
    	fclose(eingabe);
    	return 3;
    }
    
    crossword*c = init_crossword();

    int max = find_max_word_len(list);
    int limit = max * word_list_len(list);

    int success = generate_crossword_from_list(list,c,limit,1);

    if(success){
        FILE*ausgabe = fopen(argv[2], "w");
        
        if(ausgabe == NULL){
            wort_list_freigeben(list);
            free_crossword(c);
            fclose(eingabe);
            return 2;
        }
        
        print_crossword_from_word_list(c,ausgabe, list);
        fclose(ausgabe);
    }
    
    else
    {
		wort_list_freigeben(list);
        free_crossword(c);
        fclose(eingabe);
   
        
		return 3;
	}
	

    wort_list_freigeben(list);
    free_crossword(c);


    fclose(eingabe);
    printf(" ____ %i ____\n", max);
    printf("%i", success);
    return 0;
}
