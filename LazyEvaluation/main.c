#include <stdlib.h>
#include <stdio.h>


typedef void (*Thunk)(void);


#define THUNK(T) ((Thunk) (T))


typedef struct {
    Thunk thunk;
    /* input parameters */
    int a;
    int b;
}LazySum;


#define LazySum(...) (LazySum) {__VA_ARGS__}


#define lazy_add(T) ((int(*)(int, int)) (T)->thunk)((T)->a, (T)->b)


int sum(int a, int b) {
    return a + b;
}


int main(void) {
    /*
     * setup first input parameters into abstract interface before its evaluation
     */
    Thunk * cls = (Thunk*) &LazySum(THUNK(sum), 10, 5);
    printf("%d\n", lazy_add((LazySum*) cls));

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}




