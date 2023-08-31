/*
** Opaque pointer is used for prevent direct attribute access, 
** or isolating dependencies for given structure 
** Opaque pointer is usualy done dynamicaly on heap with malloc/free but, it is
** also possible to do it on stack but, it is nececary to know how many instancies are used
** in program to allocate enaught of memory during compilation
*/
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"


int 
main(void)
{
    /*
    ** Opaque pointer, its attributes are not known and also its byte size,
    ** because compiler have no aditional informations, it knows only type declaration
    */
    OpaqueStruct * t = opaque_struct_new(15);

    if(t == NULL)
    {
        fprintf(stderr, "OpaqueStruct allocation error!\n");
        return EXIT_FAILURE;
    }

    printf("init n: %d\n", opaque_struct_n(t));

    /*
    ** every operations with opaque pointer are done via public function interface
    ** so internal atributes are protected against to access
    */
    if(opaque_struct_update(t, 8) == false)
    {
        // runtime exception, but program can stil run 
        fprintf(stderr, "OpaqueStruct bad value of 'n'!\n");
    }
    else
        printf("updated n: %d\n", opaque_struct_n(t));
    
    if(opaque_struct_update(t, 22) == false)
        fprintf(stderr, "OpaqueStruct bad value of 'n'!\n");
    else
        printf("updated n: %d\n", opaque_struct_n(t));

    /*
    ** Opaque pointer can initilized either dynamicaly or can be 
    ** initialized staticaly as global variable in file where it is defined -> Singleton
    */
    opaque_struct_delete(t);

    printf("Program exit..\n");
    
    return EXIT_SUCCESS;
}


