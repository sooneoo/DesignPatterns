/*
** Generic data structure
** Generic data structure are used for bindig relevant data together, 
** but one or more data types can be specific to use case
** With hidden header is possible to generalize the data structure.
** This kind of structure can be allocated either dynamicaly with malloc/free or with custom allocator
**
** This is variation of opaque pointer design pattern
**
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
** hidden header definition
*/
typedef struct
{
    size_t length;
    size_t dtype;
}Vector;


/*
** helper macro for recognition from regular array
*/
#define Vector(T) T


/*
** helper macro for easy casting into Vector header and make available the attributes
*/
#define VECTOR(T) (T == NULL ? NULL : (Vector*) T-1)


/*
** constructor for generic array
*/
Vector(void) *
vector_new(
    size_t dtype
    , size_t length)
{
    if(dtype == 0 || length == 0)
        return NULL;

    Vector * self = malloc(sizeof(Vector) + (dtype*length));

    *self = (Vector) {length, dtype};

    // shifting to generic data part
    return self + 1;
}


#define vector(dtype, length) \
    vector_new(sizeof(dtype), length)


Vector(void) *
vector_new_from_array(
    size_t dtype
    , size_t length
    , void * array)
{
    size_t memsize = dtype * length;

    Vector * self = malloc(sizeof(Vector) + memsize);

    *self = (Vector) {length, dtype};
    memcpy(self+1, array, memsize);

    // shifting to generic data part
    return self + 1;
}


/*
** This macro can be used only for arrays allocated in stack memory, 
** because there is known memory size at compile time!
** 
*/ 
#define vector_from_array(array) \
    vector_new_from_array(sizeof(*array), sizeof(array)/sizeof(*array), array)


void
vector_delete(Vector * self)
{
    if(self != NULL)
        free(self);
}


int
main(void)
{
    /*
    ** allocation of generic array 
    */
    Vector(int) * v_i = vector_from_array(((int[]) {1, 2, 3, 4, 5}));
    Vector(float) * v_f = vector_from_array(((float[]) {1.5, 2.7, 3.8, 4.2, 5}));

    /*
    ** printing out the array data part and accessing 
    ** the length attribute of the Vector struct with the same way in both cases
    */ 
    printf("int array: {");
    for(size_t i = 0; i < VECTOR(v_i)->length; i++)
        printf(i == 0 ? "%d" :  ", %d", v_i[i]);
    printf("}\n");

    printf("float array: {");
    for(size_t i = 0; i < VECTOR(v_f)->length; i++)
        printf(i == 0 ? "%f" :  ", %f", v_f[i]);
    printf("}\n");

    /*
    ** deleting the memory
    */
    vector_delete(VECTOR(v_i));
    vector_delete(VECTOR(v_f));

    /*
    ** NULL pointer protection
    */
    vector_delete(VECTOR(NULL));

    printf("Program exit..\n");

    return EXIT_SUCCESS;
}







