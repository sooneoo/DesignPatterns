#include <stdio.h>
#include <stdlib.h>


/*
 * Structure for initialization 
 * (image there is more parameters to initialize)
 */
typedef struct {
    const char * brand;
    const char * model;
    int year;
    int tachometer;
}Car;


/*
 * simple function for print Car object parameters
 */
#define car_show(T)                                                 \
    printf(                                                         \
        "Car {brand: %s, model: %s, year: %d, tachometer: %d}\n"    \
        , (T)->brand                                                \
        , (T)->model                                                \
        , (T)->year                                                 \
        , (T)->tachometer)


/*
 * CarBuilder which helps initialize huge structure
 * It contains all nececery parameters which are needed to initialize in Car structure 
 */
typedef struct {
    const char * brand;
    const char * model;
    int year;
}CarBuilder;


/*
 * bulder function which initialize Car structure from accumulated 
 * parameters in CarBuilder
 */
Car car_builder_build(CarBuilder * self) {
    return (Car) {
        .brand        = self->brand
        , .model      = self->model
        , .year       = self->year
        , .tachometer = 220
    };
}


/*
 * building functions
 */
void car_builder_set_brand(CarBuilder * self, const char * brand) {
    self->brand = brand;
}


void car_builder_set_model(CarBuilder * self, const char * model) {
    self->model = model;
}


void car_builder_set_year(CarBuilder * self, int year) {
    self->year = year;
}


int main(void) {
    /*
     * initialize builder
     */
    CarBuilder builder = {0};

    /*
     * set builder parameters
     */
    car_builder_set_brand(&builder, "Ford");
    car_builder_set_model(&builder, "Mustang");
    car_builder_set_year(&builder, 2023);

    /*
     * build Car object
     */ 
    Car car = car_builder_build(&builder);

    car_show(&car);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}



