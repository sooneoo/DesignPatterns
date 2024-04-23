#include "state_machine.h"

#include <stddef.h>

/*
 * helper structure which helps control the state transition of state machine
 * if is_error attribute is false, then the new state value is regular value
 * if is_error attribute is true, then some runtime exception happend which is not
 * regarding to state machine function
 */
typedef struct {
    bool is_error;
    State state;    
}SM_Result;


/*
 * helper macros for easier returning of output state from state handler functions
 */
#define state(T) (SM_Result){.state = T}


#define raise_error return (SM_Result){.is_error = true}


/*
 * static function for handling state machine states
 */
static SM_Result __state_wait(StateMachine_Input * input) {
    if(input == NULL)
        raise_error;

    if(input->a > input->b)
        return state(STATE_FINISH);
    else if(input->a < input->b)
        return state(STATE_ERROR);
    else
        return state(STATE_WAIT);
}


static SM_Result __state_finish(StateMachine_Input * input) {
    if(input == NULL)
        raise_error;

    if(input->a == 0 && input->b == 0)
        return state(STATE_WAIT);
    else
        return state(STATE_FINISH);
}


static SM_Result __state_error(StateMachine_Input * input) {
    if(input == NULL)
        raise_error;

    if(input->a == 0 && input->b == 0)
        return state(STATE_WAIT);
    else
        return state(STATE_ERROR);
}


typedef SM_Result (*StateMachine_callback)(StateMachine_Input *);


/*
 * statck of state machine callbacks
 */
static StateMachine_callback callback[] = {
    __state_wait
    , __state_finish
    , __state_error 
};


bool state_machine_runtime(StateMachine * self, StateMachine_Input * input) {
    if(self->state < STATE_N) {
        SM_Result result;

        /*
         * state machine state transition
         */
        if((result = callback[self->state](input)).is_error == false) {
            self->state = result.state;
            return true;
        }
    } else
        self->state = STATE_WAIT;

    return false;
}



