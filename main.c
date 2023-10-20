#include <stdio.h>
#include "vars.h"
int main()
{
    // Global variables
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

    // Production values
    struct factory prod_values;
    zerofact(prod_values);
    

    // Declare an array factory types
    struct factory factories[64];

    for (int i = 0; i < 64; i++)
    {
        initfact(&factories[i],i);
    }
    
    // Actual user program
    printf("todo welcome message\n");
    calculate(factories,&worker_population,&power_consumption,&worker_food,&worker_meat,&worker_clothes,&worker_electronics,&worker_alcohol,&prod_values);
    return 0;
}