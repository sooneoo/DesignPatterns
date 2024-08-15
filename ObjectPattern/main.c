/*
** Object pattern is used for grouping related data together what makes code cleaner and
** minimizing side effects using global acces to global variables
*/

#include <stdio.h>
#include <stdlib.h>

#include "lib.h"


int main(void) {
    /*
     * creating instante of Class structure and initializing it with default values
     */
    Class obj = Class(2, 3); 

    /* 
     * calling Class structure method, it is only function which accepts 
     * Class pointer (or another types) as input parameter
     */
    printf("sum: %d\n", class_sum(&obj));  
    printf("Prorgam exit\n");

    return EXIT_SUCCESS;
}
