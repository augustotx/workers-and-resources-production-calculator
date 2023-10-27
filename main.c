#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "vars.h"

int main()
{
    // Global variables
    double *sewage = malloc(sizeof(double));
    *sewage = 0.0;

    // list in vars.h
    struct factory *resource_pool = malloc(sizeof(struct factory));
    zerofactory(resource_pool);
    double factory_count[RESOURCE_COUNT] = {0.0};

    char resourceNames[RESOURCE_COUNT][64];
    define_resource_names(resourceNames);

    int worker_population = 0;
    int university_worker_population = 0;

    // This one I got from here (https://www.reddit.com/r/Workers_And_Resources/comments/ka2ael/worker_resource_consumption_and_population_growth/)
    double worker_alcohol = 0.01;

    // Actual user program
    printf("Welcome to the calculator, comrade!\nReady to build your republic?\n");

    struct factory *factory = malloc(sizeof(struct factory));

    int type;
    while (1)
    {
        type = get_factory_type(resourceNames);
        if (type == none)
        {
            printf("No factory type with that name.\n");
            continue;
        }
        if (type == list)
        {

            printf("Factory Types:\n");
            for (int i = 0; i < RESOURCE_COUNT; i++)
            {
                printf("%d/40 - %s\n", i+1,resourceNames[i]);
            }
            continue;
        }
        break;
    }
    double amount;
    char *str = malloc(15 * sizeof(char));
    char *endptr;
    while (1)
    {
        input("\nType in the amount of factories you want to account for.\n-> ", str, 15);
        amount = strtod(str, &endptr);
        if (amount > 0.0)
        {
            break;
        }
        printf("\nType in a valid amount (bigger than 0)\n");
    }

    newfactory(factory, type);
    calculate(factory, amount, resource_pool, factory_count, resourceNames, &worker_population, &university_worker_population, sewage);
    results(resource_pool, factory_count, resourceNames, &worker_population, &university_worker_population, sewage);
    free(factory);
    free(resource_pool);
    free(sewage);
    input("\nPress enter/return to quit\n-> ", str, 15);
    free(str);
    return 0;
}
