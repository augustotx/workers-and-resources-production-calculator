#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "vars.h"

int main()
{
    // Global variables
    
    // list in vars.h
    double resources[FACTORY_SIZE];
    double factory_count[FACTORY_SIZE];
    double *checker = malloc(FACTORY_SIZE * sizeof(double));
    zerofact(checker);
    int factory_checker[FACTORY_SIZE];
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        factory_checker[i] = (int)checker[i];
    }
    free(checker);
    zerofact(factory_count);
    zerofact(resources);

    char resourceNames[FACTORY_SIZE][64];
    define_resource_names(resourceNames);
    
    int worker_population = 0;
    double power_consumption = 0.0;

    // CONSUMPTION PER WORKER PER YEAR
    // got this data from https://steamcommunity.com/app/784150/discussions/0/3454842150489701958/
    
    // I also put a number bigger than the actual estimates so that
    // production is always more than consumption

    double worker_food = 0.17;
    double worker_meat = 0.038;
    double worker_clothes = 0.005;

    // this estimate I don't have much basis on
    // (got it from a ratio I made from a dude's reply in that steam link)
    double worker_electronics = 0.0085;

    // This one I got from here (https://www.reddit.com/r/Workers_And_Resources/comments/ka2ael/worker_resource_consumption_and_population_growth/)
    double worker_alcohol = 0.01;
    
    
    double factories[FACTORY_SIZE][FACTORY_SIZE];
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        zerofact(factories[i]);
        initfact(i,factories[i]);
    }
    

    // Actual user program
    printf("todo welcome message\n");
    calculate(resourceNames,factory_count,resources,factories,21,1.0, factory_checker); // 1 food factory and its needs
    showresults(resourceNames,factory_count);
    return 0;
}