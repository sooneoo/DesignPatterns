#include <stdio.h>
#include <stdlib.h>


typedef struct {
    void (*sayHi)(void);
}Interface;


typedef struct {
    Interface greed;
}English;


void say_english(void) {
    printf("Hello\n");
}


typedef struct {
    Interface greed;
}German;


void say_german(void) {
    printf("Guten tag\n");
}


int main(void) {
    German german = {.say_german};


    printf("Program exit..\n");

    return EXIT_SUCCESS;
}
