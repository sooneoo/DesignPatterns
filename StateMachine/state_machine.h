#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include <stdbool.h>


/*
 * state machine internal states definition
 */
typedef enum {
    STATE_WAIT
    , STATE_FINISH
    , STATE_ERROR
    , STATE_N
}State;


#define STATE(T)                        \
    T == STATE_WAIT   ? "STATE_WAIT":   \
    T == STATE_FINISH ? "STATE_FINISH": \
    T == STATE_ERROR  ? "STATE_ERROR":  \
                        "UNKNOWN"


/*
 * state machine structure
 */
typedef struct {
    State state;
}StateMachine;


/*
 * Macro constructor for StateMachine
 */
#define StateMachine(...) (StateMachine){__VA_ARGS__}


/*
 * structure describing inputs for the state machine
 */
typedef struct {
    int a;
    int b;
}StateMachine_Input;


/*
 * running state machine
 */
bool state_machine_runtime(StateMachine * self, StateMachine_Input * input);



#endif
