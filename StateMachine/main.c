#include <stdio.h>
#include <stdlib.h>

#include "state_machine.h"


int
main(void)
{
    /*
    ** initialization of state machine
    */
    StateMachine state_machine = StateMachine(STATE_WAIT);
    StateMachine_Input input = {0};
    

    /*
    ** state machine evaluation
    */
    for(size_t i = 0; i < 6; i++)
    {
        StateMachine_Input * input_ptr = &input;
    
        /*
        ** input of state machine simulation
        */ 
        if(i == 1)
            input.a = 1;
        else if(i == 2)
            input.a = 0;
        else if(i == 3)
            input.b = 1;
        else if(i == 4)
        {
            input.b = 0;
            input_ptr = NULL;
        }

        /*
        ** check output of state machine
        */
        if(state_machine_runtime(&state_machine, input_ptr) == true)
            printf("return true, state: %s\n", STATE(state_machine.state));
        else
        {
            printf("return false\n");

            /*
            ** initialization of state machine after runtime exception
            */
            state_machine = StateMachine(STATE_WAIT);
        }
    }

    printf("Program exit..\n");

    return EXIT_SUCCESS;
}
