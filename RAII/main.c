#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_alloc.h"


typedef struct {
    Alloc * env;
    size_t ndim;
    size_t * shape;
    int * data;
} Tensor;


size_t Tensor_Size(size_t ndim, size_t * shape) {
    size_t size = shape[0];

    for(size_t i = 1; i < ndim; i++) {
        size *= shape[i];
    }

    return size;
}


/*
 * Tensor from this constructor owns data attribute
 */
Tensor Tensor_New(size_t ndim, size_t * shape) {
    size_t size = Tensor_Size(ndim, shape);
    size_t memsize = (sizeof(int) * size) + (sizeof(size_t) * ndim);

    /*
     * allocation of tensor memory environment
     */
    Alloc * env = StackAlloc_New(memsize);

    /*
     * initialization of Tensor object
     */
    Tensor t = {
        .env = env
        , .ndim = ndim
        , .shape = new(env, sizeof(size_t) * ndim)
        , .data = new(env, sizeof(int) * size)
    };

    memcpy(t.shape, shape, sizeof(size_t) * ndim);
    
    return t;
}


/*
 * Tensor from this constructor don't owns data attribute
 */
Tensor Tensor_FromArray(size_t ndim, size_t * shape, int * data) {
    size_t memsize = (sizeof(size_t) * ndim);

    /*
     * allocation of tensor memory environment
     */
    Alloc * env = StackAlloc_New(memsize);

    /*
     * initialization of Tensor object
     */
    Tensor t = {
        .env = env
        , .ndim = ndim
        , .shape = new(env, sizeof(size_t) * ndim)
        , .data = data
    };

    memcpy(t.shape, shape, sizeof(size_t) * ndim);
    
    return t;
}


/*
 * Destructor for Tensor instance, it doesn't matter if the attributes are own by tensor, 
 * every memory used by tensor is managed by Alloc memory manager which acts as memory environment
 */
void Tensor_Delete(Tensor t) {
    if(t.env != NULL) {
        free(t.env);
    }
}


/*
 * helper function for dump matrix tensor
 */
static inline void show_matrix(Tensor t) {
    printf("[");
    for(size_t i = 0; i < t.shape[0]; i++) {
        printf(i == 0 ? "[" : "\n [");
        for(size_t j = 0; j < t.shape[1]; j++) {
            printf(j == 0 ? "%d" : " %d", t.data[i * t.shape[1] + j]);
        }
        printf("]");
    }
    printf("]\n");
}


int main(void) {
    Tensor t = Tensor_FromArray(2, (size_t[]){2, 2}, (int[]){1, 2, 3, 4});
    show_matrix(t);
    Tensor_Delete(t);

    printf("Programe exit..\n");
    return EXIT_SUCCESS;
}





