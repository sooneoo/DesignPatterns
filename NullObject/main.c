/*
** NULL pointer is potencionaly dangerous, because accessing NULL pointer can 
** occure runtime error by memory corruption
** Therefore is convention to check if given pointer is not NULL.
** Another way to treat this runtime state is to define non-NULL default pointer for given pointer which 
** can't case memory corruption.
*/

#include <stdio.h>
#include <stdlib.h>


static char * nullptr = "(null)"


char * 
repr(int value)
{
    if(value < 100)
    {
        
    }
}






int
main(void)
{
    printf("Program exit..\n");

    return EXIT_SUCCESS;
}

