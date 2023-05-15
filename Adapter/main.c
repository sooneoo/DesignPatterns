#include <stdio.h>
#include <stdlib.h>


/*
** Origin function from external interface
*/
double
average(
    size_t length
    , double * array)
{
    double value = 0;

    for(size_t i = 0; i < length; i++)
        value += array[i];

    return value / length;
} 


/************** adapter layer ***************/

typedef struct
{
    size_t length;
    double * array;
}Vector;


/*
** this function is able to cover changes in the extern library api or change api for easier ussage. 
*/
double
vector_average(Vector vector)
{
    return average(vector.length, vector.array);
}


int 
main(void)
{
    double array[5] = {1,5,3,4,8};

    Vector vector = (Vector){sizeof(array)/sizeof(*array), array};

    printf(
        "%f | %f\n"
        , average(sizeof(array)/sizeof(*array), array)
        , vector_average(vector));

    return EXIT_SUCCESS;
}   
