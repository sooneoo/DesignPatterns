#include <stdio.h>
#include <stdlib.h>

/*
** plugin is just interface used for specifing api for dynamic working with given object
** This plugins can be dynamicaly connected/disconnected from system at runtime (teoreticaly)
** Every plugin can add another functionality into system without corruption of core and
** this is the essence of plugin pattern
*/
typedef struct Plugin
{
    void (*set_state)(struct Plugin *, void *);
    void (*show_state)(struct Plugin *);
}Plugin;


void
set_state(Plugin * self, void * data)
{
    self->set_state(self, data);
}


void
show_state(Plugin * self)
{
    self->show_state(self);
}


#define PLUGIN(T)((Plugin*) (T))


/*
** plugins declaraction
*/
typedef struct
{
    Plugin plugin;
    int value;
}Controller01;


void
controller01_show_state(
    Controller01 * self)
{
    printf("Controller01 {value: %d}\n" , self->value);
}


void
controller01_set_state(
    Controller01 * self
    , int * value)
{
    self->value = *value;
}


#define Controller01(v)(Controller01)                           \
{                                                               \
    .plugin =                                                   \
    {                                                           \
        (void (*)(Plugin*, void *)) controller01_set_state      \
        , (void (*)(Plugin*)) controller01_show_state           \
    }                                                           \
    , .value = (v)                                              \
}


typedef struct
{
    Plugin plugin;

    struct Controller02_attributes
    {
        int a;
        int b;
    }attributes;
}Controller02;


void
controller02_show_state(
    Controller02 * self)
{
    printf("Controller02 {a: %d, b: %d}\n" , self->attributes.a, self->attributes.b);
}


void
controller02_set_state(
    Controller02 * self
    , struct Controller02_attributes * attributes)
{
    self->attributes = *attributes;
}


#define Controller02(a, b)(Controller02)                    \
{                                                           \
    .plugin =                                               \
    {                                                       \
        (void(*)(Plugin*, void *)) controller02_set_state   \
        , (void(*)(Plugin*)) controller02_show_state        \
    }                                                       \
    , .attributes={(a), (b)}                                \
}


typedef enum
{
    Plugin_Controller01
    , Plugin_Controller_02
    , Plugin_N
}Plugin_ID;


/*
** Core is nothing else than array of plugins and other system 
** parts needed for running the aplication
*/
typedef struct
{
    Plugin * plugin_array[Plugin_N];
}Core;


void
core_run(Core * self)
{
    for(size_t i = 0; i < Plugin_N; i++)
        show_state(self->plugin_array[i]);
}


int
main(void)
{
    /*
    ** Plugins definition
    */
    Controller01 ctrl_01 = Controller01(42);
    Controller02 ctrl_02 = Controller02(27, 16);

    /*
    ** Core initialization
    */
    Core core = {.plugin_array = {PLUGIN(&ctrl_01), PLUGIN(&ctrl_02)}};
    
    /*
    ** running core with plugins 
    */
    core_run(&core);

    set_state(PLUGIN(&ctrl_01), (int []){12});
    set_state(PLUGIN(&ctrl_02), (struct Controller02_attributes[]){{1, 2}});

    core_run(&core);

    printf("Program exit..\n");

    return EXIT_SUCCESS;
}




