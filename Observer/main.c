#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*
 * Event structure which contains bool signal for calling the callback function
 * callback function and pointer to optional input parameter
 */
typedef struct {
    char * name;
    void (*callback)(void *);
}Event;


typedef enum {
    EVENT_1
    , EVENT_2
    , EVENT_N
}EVENTS;


/*
 * Simple event bus represented as static array of Events
 */
typedef struct {
    size_t size;
    Event event[EVENT_N];
}EventBus;


/*
 * function for emiting the signal for calling the callback function
 */
void event_listener_emit(EventBus * self, char * name, void * param) {
    for(size_t i = 0; i < self->size; i ++) {
        if(strcmp(self->event[i].name, name) == 0) {
            self->event[i].callback(param);
        }
    }
}


/*
 * callback for both events
 * it prints the parameter as string
 */
void event_callback_1(void * param) {
    printf("callback_1: %s\n", (char *) param);
}


void event_callback_2(void * param) {
    printf("callback_2: %s\n", (char *) param);
}


int main(void) {
    /*
     * static initialization of Event bus
     * visible part of the application
     */ 
    EventBus bus = {
        .size = EVENT_N
        , .event = {{"Event 1", event_callback_1}, {"Event 2", event_callback_2}}
    };

    /*
     * event loop, hidden part of the application
     */
    for(size_t i = 0; i < 10; i ++) {
        if(i == 1 || i == 5) {
            event_listener_emit(&bus, "Event 1", "signal for event 1");
        }

        if(i == 3 || i == 5 || i == 9) {
            event_listener_emit(&bus, "Event 2", "signal for event 2");
        }
    }

    printf("Program exit..\n");

    return EXIT_SUCCESS;
}


