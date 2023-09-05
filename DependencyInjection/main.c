/*
** Main aim of dependecy injection is to separate the dependency from implementation of
** the object and make better separation between responsibilitie. This makes cleaner and shorter
** code for object initialization. This object is also more flexible and better testable
**
** Dependecy injection is similar to Strategy pattern, but Strategy pattern 
** can dynamicaly changing the inner dependency/strategy object. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef int(*LogCallback)(void *, const char *, va_list);

/*
** Logger as base class for defining variety of dependencis for App structure
** This works as abstract itnerface for external dependency
*/
typedef struct
{
    LogCallback log;
}Logger;


/*
** calling virtual method with readig of variadic arguments 
*/
int 
logger(
    Logger * self
    , const char * format
    , ...)
{
    va_list args;
    va_start(args, format);

    int result = self->log(self, format, args);

    va_end(args);

    return result;
}


/*
** FileLogger struct definition as extern dependency for App structure
*/
typedef struct
{
    Logger logger;
    FILE * stream;
}FileLogger;


/*
** implementation of logging function for FILE* stream reference
** in the same way is possible to do NetworkLogger structure 
** where the logger function can sent data throw network
*/
static int
file_logger_write(
    FileLogger * self
    , const char * format
    , va_list args)
{
    return vfprintf(self->stream, format, args);
}


/*
** Constructor for FileLogger structure
*/
FileLogger
file_logger_init(FILE * stream)
{
    return (FileLogger)
    {
        .stream = stream
        , .logger.log = (LogCallback) file_logger_write
    };
}


/*
** App structure with logger for monitoring of state changing
*/
typedef struct
{
    int state;
    Logger * logger;
}App;


/*
** update method with implemented monitoring
*/
void
app_update_state(
    App * self
    , int state)
{
    logger(self->logger, "State update %d -> %d\n", self->state, state);
    self->state = state;
}


/*
** App structure constructor
*/
App
app_init(Logger * logger)
{
    return (App) {.state = 0, .logger=logger };
}


int
main(void)
{
    /*
    ** initializing file logger with stdout stream 
    ** it is possible to use FILE * f = fopen(PATH, "w");
    ** but it is nececery to call close(f); for closing the FILE* stream
    */
    FileLogger file_logger = file_logger_init(stdout);
    App app                = app_init((Logger*) &file_logger);

    /*
    ** monitoring of state changing 
    */
    app_update_state(&app, 42);   
    app_update_state(&app, 27);   

    /* release resorce for FileLogger and App */

    printf("Program exit..\n");

    return EXIT_SUCCESS;
}



