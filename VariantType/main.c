/*
** Variant type is design pattern used for making polymorfic data structure which can
** repressent several different internal representation but are used in one type class
** Type class is defined as several data types related for given application and bounded into
** one type identifier
** Typical example is Token structure which can contain string, integer, bool and another data types
** readed from input string
**
** Difference from Factory pattern is that Factory pattern describing the way of 
** complex object construction, this class object can or also can't be variadic.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
** Variadic structure 
*/
typedef struct
{
    /*
    ** internal id of the variadic data structure which identifying 
    ** concrete instance
    */
    enum
    {
        TOKEN_STRING
        , TOKEN_NUMBER
        , TOKEN_BOOL
    }id;

    /*
    ** data type attribute regarding to id value
    */
    union
    {
        char * string;
        int number;
        bool boolean;
    };
}Token;


/*
** variadic method which switching data type which Token 
** object containg based on its configured ID
*/
void
token_show(Token * self)
{
    switch(self->id)
    {
    case TOKEN_STRING:
        printf("Token {id=TOKEN_STRING, value=\"%s\"}\n", self->string);
        break;
    case TOKEN_NUMBER:
        printf("Token {id=TOKEN_NUMBER, value=%d}\n", self->number);
        break;
    case TOKEN_BOOL:
        printf("Token {id=TOKEN_BOOL, value=%s}\n", self->boolean ? "true" : "false");
        break;
    default:
        printf("Token {id=unknown}\n");
    }
}


/*
** Simple constructors based on factory design pattern
*/
#define Token_String(value)(Token){.id=TOKEN_STRING, .string=value}
#define Token_Number(value)(Token){.id=TOKEN_NUMBER, .number=value}
#define Token_Bool(value)(Token){.id=TOKEN_BOOL, .boolean=value}


int
main(void)
{
    /*
    ** creating instances for different Token type
    */
    Token str_tok  = Token_String("String value");
    Token num_tok  = Token_Number(42);
    Token bool_tok = Token_Bool(false);

    /*
    ** printing token content based on it's value type
    */
    token_show(&str_tok);
    token_show(&num_tok);
    token_show(&bool_tok);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}



