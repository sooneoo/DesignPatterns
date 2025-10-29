#include <stdio.h>
#include <stdlib.h>


typedef struct {
    size_t capacity;
    size_t index;
    char * mem_buff;
} Alloc;


void * new(Alloc * self, size_t memsize) {
    if((self->index + memsize) < self->capacity) {
        void * mem = &self->mem_buff[self->index];
        self->index += memsize;
        return mem;
    } else {
        return NULL;
    }
}


void reset(Alloc * self) {
    self->index = 0;
}


typedef struct {
    void * glyf;
} Font; 


typedef struct {
    Alloc * alloc;
    Font font;
} Context;


typedef struct {
    Context * context;
    float x, y;    
} Button;



Button * button_new(Context * context, float x, float y) {
    Button * self = new(context->alloc, sizeof(Button));

    *self = (Button) {
        .context = context
        , .x = x
        , .y = y
    };

    return self;
} 


#include <assert.h>


#define VIRTUAL_HEAP_SIZE 1024
char virtual_heap[VIRTUAL_HEAP_SIZE];


int main(void) {
    Alloc alloc = {
        .capacity = VIRTUAL_HEAP_SIZE
        , .mem_buff = virtual_heap
    };

    Context context = {
        .alloc = &alloc
    };


    Button * btn1 = button_new(&context, 100, 50);
    assert(btn1 != NULL);
    Button * btn2 = button_new(&context, 100, 50);
    assert(btn2 != NULL);
    Button * btn3 = button_new(&context, 100, 50);
    assert(btn3 != NULL);

    /* do some work with button */
    
    reset(&alloc);

    printf("program exit\n");
    return EXIT_SUCCESS;
}











