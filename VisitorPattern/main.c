#include <stdio.h>
#include <stdlib.h>


typedef void(*Thunk)(void);

typedef struct {
    Thunk accept;
}Object; 


typedef struct Visitor Visitor;


typedef struct {
    Object object;
    float a, b, c;    
} Triangle;


int main(void) {

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}








