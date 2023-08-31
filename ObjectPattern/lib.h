#ifndef _LIB_H_
#define _LIB_H_


/*
** class/structure definition which groups related data together 
*/
typedef struct
{
    int a;
    int b;
}Class;


/*
** simple constructor based on C initializers
*/
#define Class(...)(Class){__VA_ARGS__}


/*
** method declaration
*/
int
class_sum(Class * self);


#endif

