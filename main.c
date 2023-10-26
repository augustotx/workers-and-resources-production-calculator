#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "vars.h"

int main()
{
    // Global variables

    // list in vars.h
    struct factory *resource_pool = malloc(sizeof(struct factory));
    zerofactory(resource_pool);
    double factory_count[RESOURCE_COUNT] = {0.0};

    char resourceNames[RESOURCE_COUNT][64];
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

    // Actual user program
    printf("Welcome to the calculator, comrade!\nReady to build your republic?\n");
    
    struct factory *factory = malloc(sizeof(struct factory));
    
    int type = get_factory_type(resourceNames);
    if (type == -1)
    {
        printf("No factory type with that name.\n");
        return 1;
    }
    
    char *str = malloc(15 * sizeof(char));
    char *endptr;
    input("\nType in the amount of factories you want to account for.\n-> ", str, 15);
    double amount = strtod(str, &endptr);
    free(str);
    printf("\n");
    
    newfactory(factory, type);
    calculate(factory, amount, resource_pool, factory_count, resourceNames, &worker_population);
    results(resource_pool, factory_count, resourceNames, &worker_population);
    free(factory);
    free(resource_pool);

    return 0;
}
