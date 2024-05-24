/*
 * closure can be used anywhere, where is needed to call function with internal state but 
 * the state must be changed, but the sygnature of the function must be the same
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


typedef void(*Thunk)(void);


#define THUNK(T) ((Thunk) (T))


typedef struct {
    Thunk thunk;
    int a;
}AddOneClosure;


#define AddOneClosure(...) (AddOneClosure) {__VA_ARGS__}


/*
 * from arbitrary C function is possible to create closure by storing its 
 * environment into structure initialized by given input values
 */
static int cls_add_one(int a, int b) {
    return a + b;
} 


#define add_one(T, b) ((int(*)(int, int)) (T)->thunk)((T)->a, (b))


int main(void) {
    Thunk * cls = (Thunk*) &AddOneClosure(THUNK(cls_add_one), 1);
    printf("%d\n", add_one((AddOneClosure*) cls, 41));
    printf("Program exit\n");
    return EXIT_SUCCESS;
}





