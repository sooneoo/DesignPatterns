/*
 * Design pattern Strategy is pattern for dynamic behavior of class based on current configuration.
 */
#include <stdio.h>
#include <stdlib.h>


typedef struct FanUnit FanUnit;


typedef void (*FanUnit_Strategy_Callback)(FanUnit *, int);


/*
 * interface pattern
 */
typedef struct {
    FanUnit_Strategy_Callback callback;
}FanUnit_Strategy_VTab;


/*
 * Abstract interface/class for strategy definition
 */
typedef struct {
    FanUnit_Strategy_VTab * vtab;
    /*
     * possible another virtual variables
     */
} FanUnit_Strategy;


#define FAN_UNIT_STRATEGY(T) ((FanUnit_Strategy*) (T))


/*
 * module containing strategy for sending value throw Ethernet network
 */
typedef struct {
    FanUnit_Strategy strategy;

    /* possible aditional parameters */
}FanUnit_EthernetStrategy;


#define FAN_UNIT_ETHERNET_STRATEGY(T) ((FanUnit_EthernetStrategy*)(T))

/*
 * implementation of strategy virtual function for Ethernet network control strategy
 */
void ethernet_set_speed(FanUnit * self, int speed) {
    (void) self; // not needed at this moment
                 
    //FAN_UNIT_ETHERNET_STRATEGY(self->strategy)->some attribute

    printf("Sending request for fan speed (%d) throw Ethernet network\n", speed);
}


FanUnit_EthernetStrategy ethernet_strategy(void) {
    static FanUnit_Strategy_VTab vtab = {.callback = ethernet_set_speed};
    return (FanUnit_EthernetStrategy) {.strategy = {.vtab = &vtab}};
}

/*
 * module containing strategy for sending value throw Serial line
 */
typedef struct {
    FanUnit_Strategy strategy;

    /* possible aditional parameters */
}FanUnit_SerialStrategy;


#define FAN_UNIT_SERIAL_STRATEGY(T) ((FanUnit_SerialStrategy*)(T))


/*
 * implementation of strategy virtual function for Serial line control strategy
 */
void serial_set_speed(FanUnit * self, int speed) {
    (void) self; // not needed at this moment
                 
    //FAN_UNIT_SERIAL_STRATEGY(self->strategy)->some attribute
    printf("Sending request for fan speed (%d) throw serial line\n", speed);
}


FanUnit_SerialStrategy serial_strategy(void) {
    static FanUnit_Strategy_VTab vtab = {.callback = serial_set_speed};
    return (FanUnit_SerialStrategy) {.strategy = {.vtab = &vtab}};
}


/*
 * module for fan speed control abstracting the way how it is done
 */
struct FanUnit {
    FanUnit_Strategy * strategy;
};


#define FanUnit(strategy)(FanUnit) {(strategy)}


/*
 * method for setup of given control strategy
 */
void  fan_unit_set_control_strategy(FanUnit * self, FanUnit_Strategy * strategy)  {
    self->strategy = strategy;
}


/*
 * virtual method for calling configured strategy callback
 */
void fan_unit_set_speed(FanUnit * self, int speed) {
    // safety for NULL pointer accessing
    if(self->strategy != NULL && self->strategy->vtab != NULL && self->strategy->vtab->callback != NULL) {
        self->strategy->vtab->callback(self, speed);
    }
}


int main(void) {
    /*
     * definition of strategy instances
     */ 
    FanUnit_EthernetStrategy ethernet = ethernet_strategy();
    FanUnit_SerialStrategy serial = serial_strategy();

    /*
     * module working as interface for control
     * be carefull for initialization if it is worked with function pointers!
     */
    FanUnit fan_control = FanUnit(FAN_UNIT_STRATEGY(&ethernet));

    /*
     * dynamic behavior of control module
     * it can sending commands either throw Ethernet network or throw Serial line based on runtime settings
     */
    fan_unit_set_speed(&fan_control, 5);

    fan_unit_set_control_strategy(&fan_control, FAN_UNIT_STRATEGY(&serial));
    fan_unit_set_speed(&fan_control, 2);

    printf("Program exit\n");
    return EXIT_SUCCESS;
}






