#include <stdio.h>
#include <stdlib.h>


typedef struct Animal {
    void (*__sound__)(struct Animal *);
    void (*__finalize__)(struct Animal *);
} Animal;


#define animal_sound(T) (T)->__sound__((T))
#define animal_finalize(T) (T)->__finalize__((T))


void animal_do_sound(Animal * self, size_t n) {
    if(self->__sound__ != NULL) {
        for(size_t i = 0; i < n; i++) {
            animal_sound(self);
        }
    }
}


typedef struct {
    Animal animal;
    const char * sound;
} Cat; 


static void cat_sound(Cat * self) {
    printf("%s\n", self->sound);
}


Animal * cat_new(void) {
    Cat * cat = malloc(sizeof(Cat));

    *cat = (Cat) {
        .animal = {
            .__sound__ = (void(*)(Animal*)) cat_sound
            , .__finalize__ = (void(*)(Animal*)) free
        }
        , "miau"
    };

    return (Animal*) cat;
}


int main(void) {
    Animal * cat_animal = cat_new();

    animal_do_sound(cat_animal, 5);

    animal_finalize(cat_animal);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}


