#include <stdio.h>
#include <stdlib.h>

typedef struct {
   int age;
}Animal;


int animal_age(Animal * self) {
    return self->age;
}


typedef struct {
    Animal anima;
    char * name;
}Human;






    
int main(void) {


    printf("Programe exit..\n");
    return EXIT_SUCCESS;
}


