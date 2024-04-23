#ifndef _ALLOC_H_
#define _ALLOC_H_


#include <stddef.h>


typedef struct Alloc {
    void *(*new)(struct Alloc *, size_t);
    void (*delete)(struct Alloc *, void *);
}Alloc;


#define new(T, size) (T)->new((T), size)


#define delete(T, ptr) (T)->delete((T), ptr)





#endif
