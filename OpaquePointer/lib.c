#include "lib.h"

#include <stdlib.h>


struct OpaqueStruct
{
    int n;
};


#define N_VALUE_CORRECT(N)((N) > 10) 


OpaqueStruct *
opaque_struct_new(int n)
{
    if(N_VALUE_CORRECT(n) == false)
        return NULL;

    OpaqueStruct * self = malloc(sizeof(OpaqueStruct));

    return self;
}


bool
opaque_struct_update(
    OpaqueStruct * self
    , int n)
{
    if(N_VALUE_CORRECT(n) == false)
        return false;

    self->n = n;

    return true;
}


int
opaque_struct_n(OpaqueStruct * self)
{
    return self->n;
}



void
opaque_struct_delete(OpaqueStruct * self)
{
    if(self != NULL)
        free(self);
}


