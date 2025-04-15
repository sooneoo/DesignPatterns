/*
 * iterator design patter is abstraction for terable object, this object can be collection type simple array, array list, linked list, ... 
 * or buffered or non buffered system input for example from sensor
 *
 * iterator is only special interface for iteration over iterable object
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct Iterator {
    void * context;
    size_t index;
    void (*__reset__)(struct Iterator *);
    void*(*__next__)(struct Iterator *);
} Iterator;


#define iterator_reset(T) ((T)->__reset__((T)))


#define iterator_next(T) ((T)->__next__((T)))


#define iterate(T, type, var, block) \
    do { \
        Iterator iterator = (T);        \
        iterator_reset(&iterator);      \
        for(type var = iterator_next(&iterator); var != NULL; iterator.index++, var = iterator_next(&iterator)) \
            block \
    } while(0)


#define INPUT_BUFF_SIZE 10


/*
 * buffered input 
 */
typedef struct {
    uint8_t size;
    uint8_t head;
    uint8_t tail;
    uint8_t input_buffer[INPUT_BUFF_SIZE];
} Input;


#define INPUT(T) ((Input*)(T))


bool input_empty(Input * self) {
    if(self->size == 0) {
        return true;
    } else {
        return false;
    }
}


bool input_full(Input * self) {
    if(self->size < INPUT_BUFF_SIZE) {
        return false;
    } else {
        return true;
    }
}


static void input_iterator_reset(Iterator * it) {
    it->index = 0;
}


static void * input_iterator_next(Iterator * it) {
    Input * context = it->context;
    if(input_empty(context) == false) {
       uint8_t * value = &context->input_buffer[context->tail];
       context->tail = (context->tail + 1) % INPUT_BUFF_SIZE;
       context->size--;
       return value;
    } else {
        return NULL;
    }
}


Iterator input_to_iterator(Input * self) {
    return (Iterator) {
        .context = self
        , .__reset__ = input_iterator_reset
        , .__next__ = input_iterator_next
    };
}


bool input_read(Input * self) {
    if(input_full(self) == false) {
        self->input_buffer[self->head] = rand() % 100;
        self->head = (self->head + 1) % INPUT_BUFF_SIZE;
        self->size++;
        return true;
    } else {
        return false;
    }
}


Input input(void) {
    return (Input) {0};
}


int main(void) {
    Input sensor = input();

    printf("iterator available: %s\n", input_empty(&sensor) == false ? "true" : "false");

    for(size_t i = 0; i < INPUT_BUFF_SIZE + 1;  i++) {
        if(input_read(&sensor) == false) {
            printf("input queue full: %ld\n", i);
        }
    }   

    printf("iterator available: %s\n\n", input_empty(&sensor) == false ? "true" : "false");

    iterate(input_to_iterator(&sensor), uint8_t*, i, {
        printf("%zu readed from sensor: %d\n",iterator.index,  *i);
    });

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}



