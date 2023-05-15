#include "singleton.h"
#include <stddef.h>


/*
** Constructor for Singleton structure
*/
#define Singleton(...) (Singleton){__VA_ARGS__}


/*
** Structure definition
*/
struct Singleton
{
    const char * name;
    int age;
};


/*
** static global instance of Singleton strucutre which will be shared in other parts of the project
*/
static Singleton instance;


/*
** Singleton constructor with lazy initialization 
*/
const Singleton * 
singleton(void)
{
    static Singleton * ptr_singleton = NULL;

    if(ptr_singleton == NULL)
    {
        instance      = Singleton("Marta", 32);
        ptr_singleton = &instance;
    }

    return ptr_singleton;
}


/******************* access methods ***********************/

const char *
singleton_name(const Singleton * self)
{
    return self->name;
}


int 
singleton_age(const Singleton * self)
{
    return self->age;
}



