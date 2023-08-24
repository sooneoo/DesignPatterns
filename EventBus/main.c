#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
** Event structure which contains bool signal for calling the callback function
** callback function and pointer to optional input parameter
*/
typedef struct
{
    bool signal;
    void * param;
    void (*callback)(void *);
}Event;


/*
** function for emiting the signal for calling the callback function
*/
void
event_listener_emit(Event * self)
{
    self->signal = true;
}


enum
{
    EVENT_1
    , EVENT_2
    , EVENT_N
}EVENTS;


/*
** Simple event bus represented as static array of Events
*/
typedef Event EventBus[EVENT_N];


/*
** handling the event signals for calling the callback function
** if the signal is true then the callback is called
*/
void
event_loop(EventBus self)
{
    for(size_t i = 0; i < EVENT_N; i++)
    {
        if(self[i].signal == true)
        {
            self[i].callback(self[i].param);
            self[i].signal = false;
        }
    }
}


/*
** callback for both events
** it prints the parameter as string
*/
void
event_callback(void * param)
{
    printf("%s\n", (char *) param);
}


int
main(void)
{
    /*
    ** static initialization of Event bus
    */ 
    EventBus bus =
    {
        {false, "Event 1", event_callback}
        , {false, "Event 2", event_callback}
    };


    /*
    ** event loop
    */
    for(size_t i = 0; i < 10; i ++)
    {
        if(i == 1 || i == 5)
            event_listener_emit(&bus[EVENT_1]);

        if(i == 3 || i == 5 || i == 9)
            event_listener_emit(&bus[EVENT_2]);

        event_loop(bus);
    }

    printf("Program exit..\n");

    return EXIT_SUCCESS;
}
