#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef union {
    uint8_t byte;

    struct {
        uint8_t onoff:1;
        uint8_t up:1;
        uint8_t down:1;
        uint8_t hi:1;
        uint8_t low:1;
    } attributes;
} Keys;


typedef enum {
    Event_Signal_Nothing

    , Event_Signal_ShortPress_OnOff
    , Event_Signal_ShortPress_Up
    , Event_Signal_ShortPress_Down
    , Event_Signal_ShortPress_Hi
    , Event_Signal_ShortPress_Low

    , Event_Signal_LongPress_OnOff
    , Event_Signal_LongPress_Up
    , Event_Signal_LongPress_Down
    , Event_Signal_LongPress_Hi
    , Event_Signal_LongPress_Low
} Event_Signal;


#define EVENT_SIGNAL_STR(T) \
    (T) == Event_Signal_Nothing ? "Event_Signal_Nothing" : \
    (T) == Event_Signal_ShortPress_OnOff ? "Event_Signal_ShortPress_OnOff" : \
    (T) == Event_Signal_ShortPress_Up ? "Event_Signal_ShorPress_Up" : \
    (T) == Event_Signal_ShortPress_Down ? "Event_Signal_ShortPress_Down": \
    (T) == Event_Signal_ShortPress_Hi ? "Event_Signal_ShorPress_Hi": \
    (T) == Event_Signal_ShortPress_Low ? "Event_Signal_ShorPress_Low": \
    (T) == Event_Signal_LongPress_OnOff ? "Event_Signal_LongPress_OnOff" : \
    (T) == Event_Signal_LongPress_Up ? "Event_Signal_LongPress_Up" : \
    (T) == Event_Signal_LongPress_Down ? "Event_Signal_LongPress_Down": \
    (T) == Event_Signal_LongPress_Hi ? "Event_Signal_LongPress_Hi": \
    (T) == Event_Signal_LongPress_Low ? "Event_Signal_LongPress_Low": \
                                        "Unknown"

typedef enum {
    Event_StateID_NoAction
    , Event_StateID_KeyPressed
    , Event_StateID_ShortPress
    , Event_StateID_LongPress
    , Event_StateID_KeyReleased
    , Event_StateID_N
} Event_StateID;


typedef struct Event_Loop Event_Loop;


typedef struct Event_State {
    struct Event_State (*callback)(Event_Loop *, Keys);
} Event_State;


struct Event_Loop {
    Keys keys;
    uint8_t key_press_timer;
    Event_State state[Event_StateID_N];
    Event_Signal signal;
};


typedef struct {
    Event_State state;
    Event_Loop event_loop;
} Event;


static Event_State event_state_no_action(Event_Loop * self, Keys keys) {
    self->key_press_timer = 0;
    self->keys = keys;
    self->signal = Event_Signal_Nothing;

    if(keys.byte != 0) {
        return self->state[Event_StateID_KeyPressed];
    } else {
        return self->state[Event_StateID_NoAction];
    }
}


#define LONG_PRESS_DELAY 2

static Event_State event_state_key_pressed(Event_Loop * self, Keys keys) {
    self->key_press_timer ++;

    if(keys.byte == 0) {
        if(self->key_press_timer < LONG_PRESS_DELAY) {
            return self->state[Event_StateID_ShortPress];
        } else {
            return self->state[Event_StateID_NoAction];
        }
    } else if(self->key_press_timer >= LONG_PRESS_DELAY) {
        return self->state[Event_StateID_LongPress];
    } else {
        self->keys = keys; 
        return self->state[Event_StateID_KeyPressed];
    }
}


static Event_State event_state_short_press(Event_Loop * self, Keys keys) {
    if(self->keys.attributes.onoff == true) {
        self->signal = Event_Signal_ShortPress_OnOff;
    } else if(self->keys.attributes.up == true) {
        self->signal = Event_Signal_ShortPress_Up;
    } else if(self->keys.attributes.down == true) {
        self->signal = Event_Signal_ShortPress_Down;
    } else if(self->keys.attributes.hi == true) {
        self->signal = Event_Signal_ShortPress_Hi;
    } else if(self->keys.attributes.low == true) {
        self->signal = Event_Signal_ShortPress_Low;
    }

    self->keys = keys;
    return self->state[Event_StateID_KeyReleased];
} 


static Event_State event_state_long_press(Event_Loop * self, Keys keys) {
    if(self->keys.attributes.onoff == true) {
        self->signal = Event_Signal_LongPress_OnOff;
    } else if(self->keys.attributes.up == true) {
        self->signal = Event_Signal_LongPress_Up;
    } else if(self->keys.attributes.down == true) {
        self->signal = Event_Signal_LongPress_Down;
    } else if(self->keys.attributes.hi == true) {
        self->signal = Event_Signal_LongPress_Hi;
    } else if(self->keys.attributes.low == true) {
        self->signal = Event_Signal_LongPress_Low;
    }

    self->keys = keys;
    return self->state[Event_StateID_KeyReleased];
}


static Event_State event_state_key_released(Event_Loop * self, Keys keys) {
    self->keys = keys;
    self->signal = Event_Signal_Nothing;

    if(keys.byte == 0) {
        return self->state[Event_StateID_NoAction];
    } else {
        return self->state[Event_StateID_KeyPressed];
    }
}


Event event(void) {
    return (Event) {
        .state = {.callback = event_state_no_action}
        , .event_loop = {
            .state = {
                {.callback = event_state_no_action}
                , {.callback = event_state_key_pressed}
                , {.callback = event_state_short_press}
                , {.callback = event_state_long_press} 
                , {.callback = event_state_key_released}
            }
        }
    };
}


Event_Signal event_loop(Event * self, Keys keys) {
    self->state = self->state.callback(&self->event_loop, keys);
    return self->event_loop.signal;
}


int main(void) {
    Event key_event = event();
    Keys keys = {0};
    Event_Signal signal; 
    
    signal = event_loop(&key_event, keys);
    printf("%d %s\n", signal, EVENT_SIGNAL_STR(signal));
    
    keys.attributes.up = true;
    signal = event_loop(&key_event, keys);
    printf("%d %s\n", signal, EVENT_SIGNAL_STR(signal));
    
    keys.attributes.up = false;
    signal = event_loop(&key_event, keys);
    printf("%d %s\n", signal, EVENT_SIGNAL_STR(signal));

    signal = event_loop(&key_event, keys);
    printf("%d %s\n", signal, EVENT_SIGNAL_STR(signal));

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}


