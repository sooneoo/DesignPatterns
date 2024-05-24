#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


typedef void(*C_GenericCallback)(void);


#define C_CALLBACK(T) ((C_GenericCallback) (T))


typedef struct {
    void(*call)(C_GenericCallback, va_list);
    C_GenericCallback callback;
}Closure;


#define Closure(call, callback) (Closure){call, callback}


void closure_call(Closure * self, ...) {
    va_list args;
    va_start(args, self);
    self->call(self->callback, args);
    va_end(args);
} 


void Closure_INT_DOUBLE(C_GenericCallback callback, va_list args) {
    int int_arg = va_arg(args, int);
    double double_arg = va_arg(args, double);
    ((void(*)(int, double)) callback)(int_arg, double_arg);
}


void my_callback(int a, double b) {
    printf("callback {%d, %f}\n", a, b);    
}


int main(void) {
    Closure cls = Closure(Closure_INT_DOUBLE, C_CALLBACK(my_callback));    
    closure_call(&cls, 42, 3.14);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}



