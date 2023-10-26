#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vars.h"

int input(char *text, char *str, int max_len)
{
    strcpy(str, "");
    printf("%s", text);
    printf("");
    if (fgets(str, max_len, stdin) != NULL)
    {
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] == '\n')
            {
                str[i] = '\0';
            }
        }
        
        return 1;
    }
    return 0;
}


int define_resource_names(char resourceNames[][64])
{
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        strcpy(resourceNames[i], "");
    }
    strcpy(resourceNames[0], "gravel");
    strcpy(resourceNames[1], "stone");
    strcpy(resourceNames[2], "coal");
    strcpy(resourceNames[3], "coal ore");
    strcpy(resourceNames[4], "iron");
    strcpy(resourceNames[5], "iron ore");
    strcpy(resourceNames[6], "raw bauxite");
    strcpy(resourceNames[12], "wood");
    strcpy(resourceNames[16], "crops");
    strcpy(resourceNames[17], "chemicals");
    strcpy(resourceNames[21], "food");
    strcpy(resourceNames[26], "oil");
    strcpy(resourceNames[27], "fuel");
    strcpy(resourceNames[28], "bitumen");
    strcpy(resourceNames[39], "water");
    return 0;
}

int strcompare(char *str1, char *str2)
{
    int result = strcmp(str1, str2);
    if (result == 0)
    {
        for (int i = 0; i < strlen(str2); i++)
        {
            if (str1[i] != str2[i])
            {
                return 0;
            }
        }
    }
    return (result == 0) ? 1 : 0;
}

int get_factory_type(char resourceNames[][64])
{
    char *buffer = malloc(64 * sizeof(char));
    input("Choose a factory type: (e.g. gravel, food, electronic components, etc)\n-> ",buffer,64);
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        if(strlen(resourceNames[i]) == 0)
        {
            continue;
        }
        if(strcompare(resourceNames[i],buffer))
        {
            free(buffer);
            return i;
        }
    }
    free(buffer);
    return -1;
}

int zerofactory(struct factory *factory)
{
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        factory->inputs[i] = 0.0;
        factory->outputs[i] = 0.0;
    }
    factory->workers = 0;
    return 0;
}

int newfactory(struct factory *factory, int factoryType)
{
    zerofactory(factory);
    if (factoryType == 28)
    {
        factoryType = 27; // bitumen factory = fuel factory
    }
    
    switch (factoryType)
    {
    case 0:
        factory->outputs[factoryType] = 82.0; // gravel/day

        factory->inputs[1] = 120.0; // stone

        factory->workers = 15;
        break;
    case 1:
        factory->outputs[factoryType] = 140.0; // stone/day

        factory->inputs[27] = 0.5; // fuel estimate consumption
        break;
    case 12:
        factory->outputs[factoryType] = 189.0; // wood/day

        factory->inputs[27] = 1.5; // 3 vehicles estimate consumption

        factory->workers = 30;
        break;
    case 16:
        factory->outputs[factoryType] = 0.82; // crops/day

        factory->inputs[27] = 1.5; // 3 vehicles estimate consumption
        break;
    case 17:
        factory->outputs[factoryType] = 0.81; // chemicals/day

        factory->inputs[0] = 0.72;
        factory->inputs[12] = 0.82;
        factory->inputs[16] = 0.78;
        factory->inputs[26] = 1.2;
        factory->inputs[39] = 10.0;

        factory->workers = 60;
        break;
    case 21:
        factory->outputs[factoryType] = 20.0; // food/day

        factory->inputs[39] = 8.5;  // water/day needed
        factory->inputs[16] = 42.0; // crops/day needed
        factory->workers = 170;
        break;
    case 26:
        factory->outputs[factoryType] = 7.0; // oil/day
        break;
    case 27:
        factory->outputs[27] = 125.0; // fuel/day
        factory->outputs[28] = 75.0;  // bitumen/day

        factory->inputs[26] = 250.0;

        factory->workers = 500;
        break;
    case 39:
        factory->outputs[factoryType] = 200.0; // water/day estimate idk

        factory->inputs[17] = 0.5; // chemicals
        factory->workers = 15;
        break;
    default:
        break;
    }
    return 0;
}

int checkratio(double *ratio)
{
    if (*ratio < 1.0)
    {
        *ratio = 1.0;
    }
    return 0;
}

int calculate(struct factory *factory,double amount,struct factory *resource_pool,double *factory_count, char resourceNames[][64], int *worker_population)
{
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        resource_pool->inputs[i] -= factory->inputs[i] * amount;
        resource_pool->inputs[i] += factory->outputs[i] * amount;
        if(factory->outputs[i] > 0.0)
        {
            factory_count[i] += 1.0 * amount;
        }
    }
    *worker_population += factory->workers;
    
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        if (resource_pool->inputs[i] >= 0.0)
        {
            continue;
        }
        struct factory *recursive_factory = malloc(sizeof(struct factory));
        
        newfactory(recursive_factory,i);
        while (resource_pool->inputs[i] < 0.0)
        {
            calculate(recursive_factory,1.0,resource_pool,factory_count,resourceNames,worker_population);
        }
        free(recursive_factory);
    }

    return 0;
}

int results(struct factory *resource_pool,double *factory_count,char resourceNames[][64], int *worker_population)
{
    printf("Remaining resources from factories (able to export):\n\n");
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        if (resource_pool->inputs[i] != 0.0)
        {
            printf("%s:\n  Amount: %f\n  Factory Count: %f\n",resourceNames[i],resource_pool->inputs[i],factory_count[i]);
        }   
    }
    if (resource_pool->inputs[39] > 0.0)
    {
        printf("\nIndustry-made sewage to take care of: %f\n",resource_pool->inputs[39]);
    }
    printf("\nWorkers needed: %d\n",*worker_population * 3);
    printf("\n");
    return 0;
}