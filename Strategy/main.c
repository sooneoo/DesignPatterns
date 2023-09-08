/*
** Design pattern Strategy is pattern for dynamic behavior of class based on current configuration.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Strategy Strategy;

typedef void
(*StrategyCallback)(struct Strategy *, int);

/*
** Abstract interface/class for strategy definition
*/
struct Strategy
{
    StrategyCallback callback;
};


/*
** casting macro for conversion of derived structures into Strategy structure
*/
#define STRATEGY(T)(Strategy*) (T)


/*
** module containing strategy for sending value throw Ethernet network
*/
typedef struct
{
    Strategy super;

    /* aditional parameters */
}EthernetStrategy;


/*
** implementation of strategy virtual function for Ethernet network control strategy
*/
void
ethernet_set_speed(
    EthernetStrategy * self
    , int speed)
{
    (void) self; // not needed at this moment
    printf("Sending request for fan speed (%d) throw Ethernet network\n", speed);
}


/*
** module containing strategy for sending value throw Serial line
*/
typedef struct 
{
    Strategy super;

    /* aditional parameters */
}SerialStrategy;


/*
** implementation of strategy virtual function for Serial line control strategy
*/
void
serial_set_speed(
    SerialStrategy * self
    , int speed)
{
    (void) self; // not needed at this moment
    printf("Sending request for fan speed (%d) throw serial line\n", speed);
}


/*
** module for fan speed control abstracting the way how it is done
*/
typedef struct
{
    Strategy * strategy;
}FanUnit;


/*
** method for setup of given control strategy
*/
void 
fan_unit_set_control_strategy(
    FanUnit * self
    , Strategy * strategy) 
{
    self->strategy = strategy;
}


/*
** virtual method for calling configured strategy callback
*/
void
fan_unit_set_speed(
    FanUnit * self
    , int speed)
{
    // safety for NULL pointer accessing
    if(self->strategy != NULL)
        self->strategy->callback(self->strategy, speed);
}


int
main(void)
{
    /*
    ** definition of strategy instances
    */ 
    EthernetStrategy ethernet = {.super.callback = (StrategyCallback) ethernet_set_speed};
    SerialStrategy serial     = {.super.callback = (StrategyCallback) serial_set_speed};

    /*
    ** module working as interface for control
    ** be carefull for initialization if it is worked with function pointers!
    */
    FanUnit fan_control       = {.strategy = STRATEGY(&ethernet)};

    /*
    ** dynamic behavior of control module
    ** it can sending commands either throw Ethernet network or throw Serial line based on runtime settings
    */
    fan_unit_set_speed(&fan_control, 5);

    fan_unit_set_control_strategy(&fan_control, STRATEGY(&serial));
    fan_unit_set_speed(&fan_control, 2);

    printf("Program exit\n");

    return EXIT_SUCCESS;
}






