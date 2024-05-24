/*
** function interface works as promise of implemented functions which 
** given object has implemented
** This function is possible to call in unit way by the same name for all type of objects
** This makes better abstraction in program
*/
#include <stdio.h>
#include <stdlib.h>


/*
** Interface declaration in from of Virtual function table (VTab)
*/
typedef struct  {
    void(*greed)(void);
    void(*say_goodbye)(void);
}VTab;


/*
** simple macros for unit the virtual functions name
*/
#define greed(T) ((T)->vtab.greed())
#define say_goodbye(T) ((T)->vtab.say_goodbye())


/*
** First object implementing VTab interface
*/
typedef struct {
    VTab vtab;
    /* another possible parameters */
}English;


/*
** implementation of virtual functions for English structure
*/
static void en_greed(void) {
    printf("Hello there.\n");
}


static void en_say_goodbye(void) {
    printf("good bye.\n");
}

// simple constructor for English structure
#define english (English){.vtab={en_greed, en_say_goodbye}}


/*
** Second object implementing VTab interface
*/
typedef struct {
    VTab vtab;
    /* another possible parameters */
}Deutch;


/*
** implementation of virtual functions for Deutch structure
*/
static void de_greed(void) {
    printf("Hallo, wie geht es?\n");
}


static void de_say_goodbye(void) {
    printf("Auf wiedersehen.\n");
}


// simple constructor for Deutch structure
#define deutch (Deutch){.vtab={de_greed, de_say_goodbye}}


int main(void) {
    // Creating of objects
    English en = english;
    Deutch de  = deutch;

    // calling interface functions
    greed(&en);
    greed(&de);

    say_goodbye(&en);
    say_goodbye(&de);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}




