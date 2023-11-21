/*
 * Repository pattern is used for separation of the dependency for creation of more
 * flexible api of the given module
 * This module is then easier to test, more modular and it is easy to replace them
 *
 * Repository pattern is defined as abstract interface (VTab) which defined functions for
 * data transaction needed for working of the given module. This interface is encapsulated in
 * another module where is interconnected data module and module defining bussines logic
 */
#include <stdio.h>
#include <stdlib.h>


/*
 * Data mode, barebone of the application 
 * storing all the data nececary for running main algorithms, atc ...
 *
 * This module must define abstract enaught interface for interation with
 * other modules
 */
typedef struct
{
    int ATS;
    int DTS;
    int RTS;
}Model;


/*
 * interface functions for interation with the Model object
 */
int
model_ATS(Model * self)
{
    return self->ATS;
}


int
model_DTS(Model * self)
{
    return self->DTS;
}


int
model_RTS(Model * self)
{
    return self->RTS;
}


/*
 * One of the algorithms inside application in abstract form
 * This module is responsible for computation of 
 * water valve flow based on current temperatures
 *
 * Inside this module is defined abstract interface for accessing
 * dependecy data and other runtime parameters nececary for
 * computation
 */
typedef struct
{
    int (*ats)(void *);
    int (*dts)(void *);
    int (*rts)(void *);

    /*
     * another runtime parameters
     */
}WaterValve;


int
water_valve_compute_flow(
    WaterValve * self
    , void * param)
{
    if(self->dts(param) - 60 > self->ats(param))
        return 100;
    else if(self->rts(param) < self->ats(param))
        return 0;
    else
        return 50;
}


/*
 * Manager layer which hides concrete implementation of the 
 * WaterValve module and it's dependencies
 */
typedef struct
{
    WaterValve water_valve;
    Model * model;
}WaterValve_Manager;


/*
 * Constructor for the WaterValve_Manager
 */
#define WaterValve_Manager(model)             \
    {                                         \
        {                                     \
            (int(*)(void*)) model_ATS         \
            , (int(*)(void*)) model_DTS       \
            , (int(*)(void*)) model_RTS       \
        }                                     \
       , (model)                              \
    }


/*
 * Calling of the function with dependency stored inside manager
 * This can be regular function or macro
 */
#define compute_flow(T) \
    water_valve_compute_flow(&(T)->water_valve, (T)->model)


int
main(void)
{
    /*
     * initialization of the Model
     */
    Model model = (Model){12, 24, 18};

    /*
     * Initialization of the WaterValve_Manager
     * Here is pared interface of the WaterValve with Model
     */ 
    WaterValve_Manager WV_Manager = WaterValve_Manager(&model);   

    /*
     * computation of the water valve flow
     */
    printf("water valve flow: %d\n", compute_flow(&WV_Manager));




    printf("Program exit..\n");
    return EXIT_SUCCESS;
}  



