/* 
 * Facade design pattern can wrap complex/inappropriate api of 
 * other modules with clean one
 *
 * This pattern is used in situation where is nececary to hide unnecessary
 * complexity of other module or system of bounded modules
 *
 * This pattern is similar to Adapter pattern, but Adapter change the api to be 
 * cleaner, but Facade pattern use only subset of complex api or/and adds new functionality
 */

#include <stdio.h>
#include <stdlib.h>


/*
 * This is data model for whole application, this can be configuration from
 * large config file or DB system api...
 *
 * In other small modules is needed only small part of this structure and other data parts
 * is only mess for this modules.
 */
typedef struct
{
    int ATS;
    int RTS;
    int DTS;
    int SP;
    int SPK1;
    int SPK2;
}Model;


/*
 * Small module which needs only several parametrs 
 */
typedef struct
{
    int SPK1;
    int SPK2;
}DTSSP;


/*
 * function/method which computes some magic value from configuration 
 * values SPK1 and SPK2 and accespts runtime values SP, ATS and RTS which are
 * also stored in model, but DTSSP is not care about where they are stored
 */
int 
dtssp_compute(
    DTSSP * self
    , int ATS
    , int RTS
    , int SP)
{
    return SP + ((SP - ATS) * self->SPK1) + ((SP - RTS) * self->SPK2);
}


/*
 * Facade which hides api of the DTSSP module and makes easier access of the
 * data from Model 
 *
 * Facade can not just hide complex api of other module, but it can also add
 * new usefull functionality
 */
typedef struct
{
    DTSSP dtssp;
    Model * model;

    int setpoint;
}DTSSP_Facade;


/*
 * Simple constructor for DTSSP_Facade
 */
#define DTSSP_Facade(model)             \
    (DTSSP_Facade)                      \
    {                                   \
        {(model)->SPK1, (model)->SPK2}  \
        , (model), 0                    \
    }


/*
 * Wrapper function for dtssp_compute function
 */
void
dtssp_update(DTSSP_Facade * self)
{
    self->setpoint = 
        dtssp_compute(
            &self->dtssp
            , self->model->ATS
            , self->model->RTS
            , self->model->SP);
}


int
main(void)
{
    /*
     * initialization of Model and DTSSP_Facade
     */
    Model model = {27, 12, 19, 19, 1, 2};
    DTSSP_Facade dtssp_facade = DTSSP_Facade(&model);

    /*
     * computation of DTSSP
     */
    dtssp_update(&dtssp_facade);

    printf("DTSSP: %d\n", dtssp_facade.setpoint);
    printf("Hello world\n");

    return EXIT_SUCCESS;
}
