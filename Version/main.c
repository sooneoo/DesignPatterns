#include <stdio.h>
#include <stdlib.h>

#include "version.h"


#define MINIMAL_SUPPORTED_LIB_VER 1


int main(void) {
    Version lib_ver = version();

    printf("my library version: %d.%d.%d\n", lib_ver.major, lib_ver.minor, lib_ver.patch);

    if(lib_ver.major < MINIMAL_SUPPORTED_LIB_VER) {
        fprintf(stderr, "warnig: old library version, minimal major supported version is: %d\n", MINIMAL_SUPPORTED_LIB_VER);
    }

    return EXIT_SUCCESS;
} 


