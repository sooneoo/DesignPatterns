/*
** NULL pointer is potencionaly dangerous, because accessing NULL pointer can 
** occure runtime error by memory corruption
** Therefore is convention to check if given pointer is not NULL.
** Another way to treat this runtime state is to define non-NULL default pointer for given pointer which 
** can't case memory corruption.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    size_t size;
    const char * c_str;
}Text;


Text text_empty = {0};


#define text(T) (Text){.size = strlen((T)), .c_str = (T)}


void text_show(Text * text) {
    if(text->size > 0 && text->c_str != NULL) {
        printf("Text: %ld | %s\n", text->size, text->c_str);
    } else {
        printf("empty string\n");
    }
}


int main(void) {
    Text t1 = text("Hello World!");

    text_show(&t1);
    text_show(&text_empty);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}

