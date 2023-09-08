#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    ID_Network
    , ID_Automat
    , ID_Manual
}RequestID;


typedef struct
{
    RequestID id;
    int TTL;
    int value;
}Handler;



typedef struct request
{
    (void)(handler)(struct Handler *)
}Request;



int
main(void)
{
    printf("Program exit..\n");
    return EXIT_SUCCESS;
}
