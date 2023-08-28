#ifndef _LIB_H_
#define _LIB_H_


#include <stdbool.h>


/*
** Opaque structure declaration
** This declaration is public and it is only thing what compiler knows about
** this structure
*/
typedef struct OpaqueStruct OpaqueStruct;


/*
** Constructor for OpaqueStructure
*/
OpaqueStruct *
opaque_struct_new(int n);


/********************** public interface for working with opaque pointer structure ********************/

bool
opaque_struct_update(
    OpaqueStruct * self
    , int n);


int
opaque_struct_n(OpaqueStruct * self);


void
opaque_struct_delete(OpaqueStruct * self);

#endif
