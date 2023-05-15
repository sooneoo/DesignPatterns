/**
** Návrhový vzor Factory (Továrna) slouží jako inicializátor pro nějakou obecnou 
** třídu/strukturu tak aby k tomu nemuselo docházet na konkrétním místě. Díky tomu 
** je kód čistší a kratší protože je osvobozen od často se opakující inicializace/konstrukce
** a daná část obsahuje opravdu jen kód který souvisí s jejím učelem
*/
#include <stdio.h>
#include <stdlib.h>


/*
** ID třídy určitující obsah
*/
typedef enum
{
    ANIMAL_DOG_ID
    , ANIMAL_CAT_ID
    , ANIMAL_CHICKEN_ID
}StructID;


/*
** Deklarace třídy
*/ 
typedef struct
{
    StructID ID;
    const char * name;
    const char * sound;
}Animal;

/*
** Jedoduchý obecný konstruktor
*/
#define Animal(...)(Animal){__VA_ARGS__}


/*
** Převod struktury na jméno podle hodnoty vnitřního ID
*/
#define AnimalName(T)                           \
    T->ID == ANIMAL_DOG_ID ?     "Dog" :        \
    T->ID == ANIMAL_CAT_ID ?     "Cat" :        \
    T->ID == ANIMAL_CHICKEN_ID ? "Chicken":     \
                                 "Animal"
/*
** Metoda která pracuje s vnitřními proměnnými struktury Animal
*/
void
animal_make_sound(Animal * self)
{
    printf(
        "%s %s  makes: %s\n"
        , AnimalName(self)
        , self->name
        , self->sound);
}

/************************* Factory ***********************/
/*
** Konstruktory, které naplní datovou strukturu určitými daty v závislosti
** na typu konstrukce plus inicializace specifickými vstupními daty
*/


Animal 
animal_dog(const char * name)
{
    return Animal(ANIMAL_DOG_ID, name, "haf haf");
}


Animal
animal_cat(const char * name)
{
    return Animal(ANIMAL_CAT_ID, name, "miau miau");    
}


Animal
animal_chicken(const char * name)
{
    return Animal(ANIMAL_CHICKEN_ID, name, "pip pip");
}


int
main(void)
{
    Animal chicken = animal_chicken("Kvoky");
    Animal dog     = animal_dog("Rex");
    Animal cat     = animal_cat("Camil");

    animal_make_sound(&chicken);
    animal_make_sound(&dog);
    animal_make_sound(&cat);

    return EXIT_SUCCESS;
}
