#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool is_value; 
    double value;
} SafeDiv;


SafeDiv safe_div(double a, double b) {
    if(a == 0 || b == 0) {
        return (SafeDiv) {0};
    } else {
        return (SafeDiv) {true, a / b};
    }
}


int main(void) {
    SafeDiv result = safe_div(10, 20);

    if(result.is_value == true) {
        printf("%f\n", result.value);
    } else {
        printf("N/A\n");
    }

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}
