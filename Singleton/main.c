#include <stdio.h>
#include <stdlib.h>

#include "singleton.h"


int
main(void)
{
    const Singleton * t = singleton();

    printf("%s %d\n", singleton_name(t), singleton_age(t));

    return EXIT_SUCCESS;
}

