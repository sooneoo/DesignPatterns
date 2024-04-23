#include "stack_alloc.h"

#include <stdlib.h>


typedef struct {
    Alloc alloc;
    char * head;
}StackAlloc;


void * __new(StackAlloc * self, size_t size) {
    void * ptr = self->head;
    self->head += size;
    return ptr;   
}


void __delete(StackAlloc * self, void * ptr) {
    size_t size = self->head - ((char*) ptr);
    self->head -= size;
}


Alloc * StackAlloc_New(size_t size) {
    StackAlloc * stack = malloc(sizeof(StackAlloc) + size);

    *stack = (StackAlloc) {
        .alloc = {.new = (void*(*)(Alloc*, size_t)) __new, .delete = (void(*)(Alloc*, void*)) __delete}
        , .head = ((char*) stack) + sizeof(StackAlloc)
    };

    return (Alloc*) stack;
}




