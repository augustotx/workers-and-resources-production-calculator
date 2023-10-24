#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vars.h"

int define_resource_names(char resourceNames[][64])
{
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        strcpy(resourceNames[i], " ");
    }
    strcpy(resourceNames[0], "Output 1");
    strcpy(resourceNames[1], "Output 2");
    strcpy(resourceNames[0 + RESOURCE_FACTOR], "Gravel");
    strcpy(resourceNames[1 + RESOURCE_FACTOR], "Stone");
    strcpy(resourceNames[2 + RESOURCE_FACTOR], "Refined Coal");
    strcpy(resourceNames[3 + RESOURCE_FACTOR], "Coal Ore");
    strcpy(resourceNames[4 + RESOURCE_FACTOR], "Refined Iron");
    strcpy(resourceNames[5 + RESOURCE_FACTOR], "Iron Ore");
    strcpy(resourceNames[6 + RESOURCE_FACTOR], "Raw Bauxite");
    strcpy(resourceNames[12 + RESOURCE_FACTOR], "Wood");
    strcpy(resourceNames[16 + RESOURCE_FACTOR], "Crops");
    strcpy(resourceNames[17 + RESOURCE_FACTOR], "Chemicals");
    strcpy(resourceNames[21 + RESOURCE_FACTOR], "Food");
    strcpy(resourceNames[26 + RESOURCE_FACTOR], "Oil");
    strcpy(resourceNames[27 + RESOURCE_FACTOR], "Fuel");
    strcpy(resourceNames[40 + RESOURCE_FACTOR], "Water");
    return 0;
}

int zerofact(double *factory)
{
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        factory[i] = 0.0;
    }
}

int initfact(int factoryType, double *factory)
{
    zerofact(factory);
    switch (factoryType)
    {
    case 0:
        // Gravel
        factory[0] = 120.0; // output 1 (gravel in this case)
        factory[1] = 0.0;   // output 2 (none in this case)

        // inputs respect resource array order
        // factory[2] = 0.0;// gravel input
        factory[1 + RESOURCE_FACTOR] = 140.0; // stone input
        factory[38 + RESOURCE_FACTOR] = 15.0; // workers
        factory[39 + RESOURCE_FACTOR] = 407.0;
        break;
    case 1:
        // stone
        factory[0] = 140.0;                  // stone output
        factory[27 + RESOURCE_FACTOR] = 0.5; // fuel input (vehicle in quarry)
        factory[39 + RESOURCE_FACTOR] = 163.0;
        break;
    case 2:
        factory[0] = 120.0; // refined coal output
        factory[3 + RESOURCE_FACTOR] = 210.0;
        factory[38 + RESOURCE_FACTOR] = 15.0;
        factory[39 + RESOURCE_FACTOR] = 257.0;
        break;
    case 3:
        factory[0] = 900.0; // coal output
        factory[38 + RESOURCE_FACTOR] = 220.0;
        factory[39 + RESOURCE_FACTOR] = 154.0;
        break;
    case 4:
        factory[0] = 105.0; // refined iron output
        factory[5 + RESOURCE_FACTOR] = 225.0;
        factory[38 + RESOURCE_FACTOR] = 15.0;
        factory[39 + RESOURCE_FACTOR] = 287.0;
        break;
    case 5:
        factory[0] = 1000.0; // iron output
        factory[38 + RESOURCE_FACTOR] = 250.0;
        factory[39 + RESOURCE_FACTOR] = 187.0;
        break;
    case 6:
        factory[0] = 22.5; // raw bauxite output
        factory[38 + RESOURCE_FACTOR] = 45.0;
        factory[39 + RESOURCE_FACTOR] = 72.0;
        break;
    case 12:
        factory[0] = 189.0; // wood
        factory[38 + RESOURCE_FACTOR] = 30.0;
        factory[27 + RESOURCE_FACTOR] = 0.5 * 3.0;
        break;
    case 16:
        factory[0] = 0.8;                          // big field production per day
        factory[27 + RESOURCE_FACTOR] = 0.5 * 3.0; // three vehicles per field i guess?
        break;
    case 17:
        factory[0] = 0.81; // chemical
        factory[0 + RESOURCE_FACTOR] = 0.72;
        factory[12 + RESOURCE_FACTOR] = 0.84;
        factory[26 + RESOURCE_FACTOR] = 1.2;
        factory[16 + RESOURCE_FACTOR] = 0.78;
        factory[40 + RESOURCE_FACTOR] = 10.0;
        factory[38 + RESOURCE_FACTOR] = 60.0;
        break;
    case 21:
        factory[0] = 20.0; // food output
        factory[16 + RESOURCE_FACTOR] = 42.0;
        factory[40 + RESOURCE_FACTOR] = 8.5;
        factory[38 + RESOURCE_FACTOR] = 170.0;
        break;
    case 26:
        factory[0] = 7.0; // oil
        break;
    case 27:
        factory[0] = 125.0; // fuel
        factory[26 + RESOURCE_FACTOR] = 250.0;
        factory[38 + RESOURCE_FACTOR] = 500.0;
    case 40:
        factory[0] = 200.0;                  // big water "output guesstimate" for testing purposes (i'll check its actual outputs later)
        factory[17 + RESOURCE_FACTOR] = 0.5; // also a guesstimate
        factory[38 + RESOURCE_FACTOR] = 25.0;
        break;
    default:
        return 0;
    }
    return 1;
}

int checkratio(double *ratio)
{
    if (*ratio < 1.0)
    {
        *ratio = 1.0;
    }
    return 0;
}

int calculate(char resourceNames[][64], double *factory_count, double *resources, double factories[][FACTORY_SIZE], int final_product, double production_factor, int *factory_checker)
{
    // init
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        resources[i] = factories[final_product][i] * production_factor;
    }
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        if (i == 41)
        {
            factory_count[i] += resources[i];
            continue;
        }
        
        if (resources[i] > 0.0)
        {
            factory_count[i] += resources[i] / factories[i - RESOURCE_FACTOR][0];
        }
    }

    for (int i = 2; i < FACTORY_SIZE; i++)
    {
        if (factory_count[i] > 0.0)
        {
            switch (i - RESOURCE_FACTOR)
            {
            case 0:
                if (!factory_checker[0])
                {
                    factory_checker[0]++;
                    calculate(resourceNames, factory_count, resources, factories, 0, factory_count[0 + RESOURCE_FACTOR], factory_checker);
                }
                break;
            case 12:
                if (!factory_checker[12])
                {
                    factory_checker[12]++;
                    calculate(resourceNames, factory_count, resources, factories, 12, factory_count[12 + RESOURCE_FACTOR], factory_checker);
                }

                break;
            case 17:
                if (!factory_checker[17])
                {
                    factory_checker[17]++;
                    calculate(resourceNames, factory_count, resources, factories, 17, factory_count[17 + RESOURCE_FACTOR], factory_checker);
                }
                break;
            case 27:
                if (!factory_checker[27])
                {
                    factory_checker[27]++;
                    calculate(resourceNames, factory_count, resources, factories, 27, factory_count[27 + RESOURCE_FACTOR], factory_checker);
                }
                break;
            case 40:
                if (!factory_checker[40])
                {
                    factory_checker[40]++;
                    calculate(resourceNames, factory_count, resources, factories, 40, factory_count[40 + RESOURCE_FACTOR], factory_checker);
                }
                break;

            default:
                break;
            }
        }
    }
    return 0;
}

int showresults(char resourceNames[][64], double *factory_count)
{
    for (int i = 2; i < FACTORY_SIZE; i++)
    {
        if (i == 40)
        {
            continue;
        }
        if (i == 41)
        {
            printf("Electrical Power needed = %fMHz\n",factory_count[i]);
            continue;
        }
        
        if (factory_count[i] > 0.0)
        {
            printf("%s: %f factories needed\n", resourceNames[i], factory_count[i]);
        }
    }
}