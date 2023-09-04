/*
** Decorator pattern allows to separate condition from action code
** For example if some action si conditioned by given value, it is more
** clean and readable way to separate them
**
** This allows to create better testable code
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
** Clima mode definition
*/
typedef enum
{
    MODE_HEAT
    , MODE_VENT
    , MODE_COOL
}Mode;


/*
** Clima structure which contains current clima mode and TTL value
** Request from network have top priority, is TTL is zero it means 
** that more than 5 second was not received any request from network so
** it is possible to do it manualy
*/
typedef struct
{
    Mode mode;
    int TTL;
}Clima;


// interval in seconds
#define TTL_INTERVAL 5 

/*
** method for setting of mode from network
*/
void
clima_update_mode(Clima * self, Mode mode)
{
    self->mode = mode;
    self->TTL  = TTL_INTERVAL;
}


/*
** conditional decorator method, this method accept Clima object pointer and
** callback function which is called only if the given conditional passed
*/
static bool
__clima_ttl(Clima * self, void (*callback)(Clima *))
{
    if(self->TTL == 0)
    {
        callback(self);
        return true;
    }

    return false;
}

/*
** clima metods for manual setup of clima mode
*/
static void
__clima_set_mode_cool(Clima * self)
{
    self->mode = MODE_COOL;
}


static void
__clima_set_mode_heat(Clima * self)
{
    self->mode = MODE_HEAT;
}


static void
__clima_set_mode_vent(Clima * self)
{
    self->mode = MODE_VENT;
}


/*
** public method which are decorated by TTL == 0 condition
*/
bool
clima_set_mode_heat(Clima * self)
{
    return __clima_ttl(self, __clima_set_mode_heat);
}


bool
clima_set_mode_cool(Clima * self)
{
    return __clima_ttl(self, __clima_set_mode_cool);
}


bool
clima_set_mode_vent(Clima * self)
{
    return __clima_ttl(self, __clima_set_mode_vent);
}


int
main(void)
{
    /*
    ** clima object initialization
    */
    Clima clima = {.mode=MODE_VENT, .TTL = 0};

    /*
    ** manual setup of clima mode mode
    */
    if(clima_set_mode_heat(&clima) == true)
        printf("Clima mode heat set\n");
    else
        printf("Clima mode heat was not set TTL=%ds\n", clima.TTL); 

    /*
    ** updating of clima mode from network
    */
    clima_update_mode(&clima, MODE_VENT);

    /*
    ** trial for manual set of clima mode
    ** it not pass because TTL is now equal 5
    */
    if(clima_set_mode_heat(&clima) == true)
        printf("Clima mode heat set\n");
    else
        printf("Clima mode heat was not set TTL=%ds\n", clima.TTL); 

    printf("Program exit..\n");

    return EXIT_SUCCESS;
}



