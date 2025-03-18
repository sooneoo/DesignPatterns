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
    void*(*next)(struct Iterator *);
} Iterator;


#define iterator_next(T) ((T)->next((T)))


#define iterate(T, type, var, block) \
    do { \
        for(type var = iterator_next((T)); var != NULL; var = iterator_next((T))) \
            block \
    } while(0)

#define INPUT_BUFF_SIZE 10


/*
 * buffered input 
 */
typedef struct {
    Iterator iterator;

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


static uint8_t * input_next(Input * self) {
    if(input_empty(self) == false) {
       uint8_t * value = &self->input_buffer[self->tail];
       self->tail = (self->tail + 1) % INPUT_BUFF_SIZE;
       self->size--;
       return value;
    } else {
        return NULL;
    }
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


Iterator * input_new(void) {
    Input * self = malloc(sizeof(Input));

    if(self != NULL) {
        *self = (Input) {
            .iterator = {
                .next = (void*(*)(Iterator*)) input_next
            }
        };
    } 

    return (Iterator*) self;
}


void input_finalize(Input * self) {
    if(self != NULL) {
        free(self);
    }
}


int main(void) {
    Iterator * in = input_new();

    printf("iterator available: %s\n", input_empty(INPUT(in)) == false ? "true" : "false");

    for(size_t i = 0; i < INPUT_BUFF_SIZE + 1;  i++) {
        if(input_read(INPUT(in)) == false) {
            printf("input queue full: %ld\n", i);
        }
    }   

    printf("iterator available: %s\n\n", input_empty(INPUT(in)) == false ? "true" : "false");

    iterate(in, uint8_t*, i, {
        printf("readed from sensor: %d\n", *i);
    });

    input_finalize(INPUT(in));

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}



