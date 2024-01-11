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
        sprintf(resourceNames[i], "UNNAMED ID#%d", i);
    }
    strcpy(resourceNames[gravel], "gravel");
    strcpy(resourceNames[stone], "stone");
    strcpy(resourceNames[coal_ore], "coal ore");
    strcpy(resourceNames[coal], "coal");
    strcpy(resourceNames[iron_ore], "iron ore");
    strcpy(resourceNames[iron], "iron");
    strcpy(resourceNames[bauxite_ore], "raw bauxite");
    strcpy(resourceNames[bauxite], "bauxite");
    strcpy(resourceNames[uranium_ore], "uranium ore");
    strcpy(resourceNames[mechanical_components], "steel");
    strcpy(resourceNames[prefab], "prefabs");
    strcpy(resourceNames[brick], "bricks");
    strcpy(resourceNames[wood], "wood");
    strcpy(resourceNames[board], "boards");
    strcpy(resourceNames[aluminium], "aluminium");
    strcpy(resourceNames[uranium_oxide], "uranium oxide");
    strcpy(resourceNames[crops], "crops");
    strcpy(resourceNames[chemicals], "chemicals");
    strcpy(resourceNames[fabric], "fabric");
    strcpy(resourceNames[clothes], "clothes");
    strcpy(resourceNames[alcohol], "alcohol");
    strcpy(resourceNames[food], "food");
    strcpy(resourceNames[plastics], "plastics");
    strcpy(resourceNames[mechanical_components], "mechanical components");
    strcpy(resourceNames[electronic_components], "electronic components");
    strcpy(resourceNames[electronics], "electronics");
    strcpy(resourceNames[oil], "oil");
    strcpy(resourceNames[fuel], "fuel");
    strcpy(resourceNames[bitumen], "bitumen");
    strcpy(resourceNames[aluminium_oxide], "aluminium oxide");
    strcpy(resourceNames[asphalt], "asphalt");
    strcpy(resourceNames[cement], "cement");
    strcpy(resourceNames[concrete], "concrete");
    strcpy(resourceNames[livestock], "livestock");
    strcpy(resourceNames[meat], "meat");
    strcpy(resourceNames[nuclear_fuel], "nuclear fuel");
    strcpy(resourceNames[nuclear_waste], "nuclear waste (there's no waste factory)");
    strcpy(resourceNames[uf6], "uf6");
    strcpy(resourceNames[power], "power (not available yet)");
    strcpy(resourceNames[water], "water");
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
    char *str_list = malloc(64 * sizeof(char));
    strcpy(str_list, "list");
    input("Choose a factory type: (type in \"list\" to see options)\n-> ", buffer, 64);
    enum resource_ids ret_value = none;
    if (strcompare(buffer, str_list))
    {
        ret_value = list;
        free(buffer);
        free(str_list);
        return ret_value;
    }
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        if (strlen(resourceNames[i]) == 0)
        {
            continue;
        }
        if (strcompare(resourceNames[i], buffer))
        {
            ret_value = i;
        }
    }
    free(buffer);
    free(str_list);
    return ret_value;
}

int zerofactory(struct factory *factory)
{
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        factory->inputs[i] = 0.0;
        factory->outputs[i] = 0.0;
    }
    factory->workers = 0;
    factory->university_workers = 0;
    return 0;
}

int newfactory(struct factory *factory, int factoryType)
{
    zerofactory(factory);

    switch (factoryType)
    {
    case gravel:
        factory->outputs[gravel] = 82.0; // gravel/day

        factory->inputs[stone] = 120.0; // stone

        factory->workers = 15;
        break;
    case stone:
        factory->outputs[stone] = 140.0; // stone/day

        factory->inputs[fuel] = 0.5; // fuel estimate consumption
        break;
    case coal_ore:
        factory->outputs[coal_ore] = 924.0; // coal ore mine at 100% capacity/day

        factory->workers = 220;
        break;
    case coal:
        factory->outputs[coal] = 120.0; // coal/day

        factory->inputs[coal_ore] = 210.0;

        factory->workers = 15;
        break;
    case iron_ore:
        factory->outputs[iron_ore] = 1000.0; // iron ore mine at 100% capacity/day

        factory->workers = 250;
        break;
    case iron:
        factory->outputs[iron] = 105.0; // iron/day

        factory->inputs[iron_ore] = 225.0;

        factory->workers = 15;
        break;
    case bauxite_ore:
        factory->outputs[bauxite_ore] = 22.5; // raw bauxite/day (i still have to check vehicle performance compared to workers)

        factory->workers = 45;
        break;
    case bauxite:
        factory->outputs[bauxite] = 75.0; // bauxite/day

        factory->inputs[bauxite_ore] = 125.0;

        factory->workers = 25;
        break;
    case uranium_ore:
        factory->outputs[uranium_ore] = 75.0; // uranium ore/day

        factory->workers = 100;
        break;
    case steel:
        factory->outputs[steel] = 43.0; // steel/day

        factory->inputs[coal] = 375.0;
        factory->inputs[iron] = 200.0;

        factory->workers = 500;
        break;
    case prefab:
        factory->outputs[prefab] = 71.0; // prefabs/day

        factory->inputs[gravel] = 65.0;
        factory->inputs[cement] = 9.8;

        factory->workers = 65;
        break;
    case brick:
        factory->outputs[brick] = 51.0; // bricks/day

        factory->inputs[coal] = 33.0;

        factory->workers = 75;
        break;
    case wood:
        factory->outputs[wood] = 189.0; // wood/day

        factory->inputs[fuel] = 1.5; // 3 vehicles estimate consumption

        factory->workers = 30;
        break;
    case board:
        factory->outputs[board] = 140.0; // boards/day

        factory->inputs[wood] = 180.0;

        factory->workers = 20;
        break;
    case aluminium:
        factory->outputs[aluminium] = 30.0; // aluminium/day

        factory->inputs[aluminium_oxide] = 52.0;
        factory->inputs[chemicals] = 2.5;

        factory->workers = 350;
        break;
    case uranium_oxide:
        factory->outputs[uranium_oxide] = 1.7; // uranium oxide/day

        factory->inputs[uranium_ore] = 36.0;

        factory->workers = 60;
        factory->university_workers = 15;
        break;
    case crops:
        factory->outputs[crops] = 0.82; // crops/day

        factory->inputs[fuel] = 1.5; // 3 vehicles estimate consumption
        break;
    case chemicals:
        factory->outputs[chemicals] = 0.81; // chemicals/day

        factory->inputs[gravel] = 0.72;
        factory->inputs[wood] = 0.82;
        factory->inputs[crops] = 0.78;
        factory->inputs[oil] = 1.2;
        factory->inputs[water] = 10.0;

        factory->workers = 60;
        break;
    case fabric:
        factory->outputs[fabric] = 5.0; // fabric/day

        factory->inputs[crops] = 20.0;
        factory->inputs[chemicals] = 0.5;
        factory->inputs[water] = 11.0;

        factory->workers = 100;
        break;
    case clothes:
        factory->outputs[clothes] = 1.2; // clothes/day

        factory->inputs[fabric] = 2.4;

        factory->workers = 80;
        break;
    case alcohol:
        factory->outputs[alcohol] = 6.0; // alcohol/day

        factory->inputs[crops] = 30.0;
        factory->inputs[water] = 13.0;

        factory->workers = 100;
        break;
    case food:
        factory->outputs[food] = 20.0; // food/day

        factory->inputs[water] = 8.5;  // water/day needed
        factory->inputs[crops] = 42.0; // crops/day needed

        factory->workers = 170;
        break;
    case plastics:
        factory->outputs[plastics] = 6.6; // plastics/day

        factory->inputs[chemicals] = 3.0;
        factory->inputs[oil] = 27.0;

        factory->workers = 60;
        break;
    case mechanical_components:
        factory->outputs[mechanical_components] = 33.0; // mechanical components/day

        factory->inputs[mechanical_components] = 22.0;

        factory->workers = 150;
        break;
    case electronic_components:
        factory->outputs[electronic_components] = 3.4; // electronic components/day

        factory->inputs[mechanical_components] = 1.7;
        factory->inputs[chemicals] = 1.3;
        factory->inputs[plastics] = 1.7;

        factory->workers = 150;
        break;
    case electronics:
        factory->outputs[electronics] = 4.1; // electronics/day

        factory->inputs[mechanical_components] = 1.7;
        factory->inputs[electronic_components] = 1.7;
        factory->inputs[plastics] = 2.5;
        break;
    case oil:
        factory->outputs[oil] = 7.0; // oil/day
        break;
    case fuel:
        factory->outputs[fuel] = 125.0;   // fuel/day
        factory->outputs[bitumen] = 75.0; // bitumen/day

        factory->inputs[oil] = 250.0;

        factory->workers = 500;
        break;
    case bitumen:
        newfactory(factory, fuel); // bitumen is from the oil refinery
        break;
    case aluminium_oxide:
        factory->outputs[aluminium_oxide] = 33.0; // aluminium oxide/day

        factory->inputs[water] = 29.0;
        factory->inputs[chemicals] = 2.6;
        factory->inputs[coal] = 29.0;
        factory->inputs[bauxite] = 77.0;

        factory->workers = 370;
        break;
    case asphalt:
        // asphalt plant I dialed back the numbers a bit because no one uses it 100% of the time, come on
        factory->outputs[asphalt] = 145.0 / 4.0; // asphalt/day

        factory->inputs[bitumen] = 20.0 / 4.0;
        factory->inputs[gravel] = 120.0 / 4.0;

        factory->workers = 5;
        break;
    case cement:
        factory->outputs[cement] = 81.0; // cement/day

        factory->inputs[coal] = 22.0;
        factory->inputs[gravel] = 210.0;

        factory->workers = 30;
        break;
    case concrete:
        // same case as asphalt plant
        factory->outputs[concrete] = 175.0 / 4.0; // concrete/day

        factory->inputs[water] = 85.0 / 4.0;
        factory->inputs[cement] = 30.0 / 4.0;
        factory->inputs[gravel] = 135.0 / 4.0;

        factory->workers = 5;
        break;
    case livestock:
        factory->outputs[livestock] = 5.0; // livestock/day

        factory->inputs[crops] = 10.0;

        factory->workers = 50;
        break;
    case meat:
        factory->outputs[meat] = 60.0; // meat/day

        factory->inputs[livestock] = 150.0;

        factory->workers = 50;
        break;
    case nuclear_fuel:
        factory->outputs[nuclear_fuel] = 0.095; // nuclear fuel/day

        factory->inputs[uf6] = 0.4;
        factory->inputs[chemicals] = 0.75;

        factory->workers = 50;
        factory->university_workers = 70;
        break;
    case nuclear_waste:
        // nuclear waste factory? lmao
        break;
    case uf6:
        factory->outputs[uf6] = 0.96; // UF6/day

        factory->inputs[chemicals] = 0.21;
        factory->inputs[uranium_oxide] = 2.0;

        factory->workers = 80;
        factory->university_workers = 40;
        break;
    case power:
        // power factory? (future power plant calculation?)
        break;
    case water:
        factory->outputs[water] = 200.0; // water/day estimate idk

        factory->inputs[chemicals] = 0.5; // chemicals
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

int calculate(struct factory *factory, double amount, struct factory *resource_pool, double *factory_count, char resourceNames[][64], int *worker_population, int *university_worker_population, double *sewage)
{
    *sewage += factory->inputs[water];
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        resource_pool->inputs[i] -= factory->inputs[i] * amount;
        resource_pool->inputs[i] += factory->outputs[i] * amount;
        if (factory->outputs[i] > 0.0)
        {
            factory_count[i] += 1.0 * amount;
        }
    }
    *worker_population += factory->workers;
    *university_worker_population += factory->university_workers;

    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        if (resource_pool->inputs[i] >= 0.0)
        {
            continue;
        }
        struct factory *recursive_factory = malloc(sizeof(struct factory));

        newfactory(recursive_factory, i);
        while (resource_pool->inputs[i] < 0.0)
        {
            calculate(recursive_factory, 1.0, resource_pool, factory_count, resourceNames, worker_population, university_worker_population, sewage);
        }
        free(recursive_factory);
    }

    return 0;
}

int results(struct factory *resource_pool, double *factory_count, char resourceNames[][64], int *worker_population, int *university_worker_population, double *sewage)
{
    printf("Remaining resources from factories (able to export):\n\n");
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        if (resource_pool->inputs[i] != 0.0)
        {
            printf("%s:\n  Amount: %f\n  Factory Count: %f\n", resourceNames[i], resource_pool->inputs[i], factory_count[i]);
        }
    }
    if (resource_pool->inputs[water] > 0.0)
    {
        printf("\nIndustry-made sewage to take care of: %f\n", *sewage);
    }
    printf("\nWorkers needed: %d\n", *worker_population * 3);
    printf("\nUniversity workers needed: %d\n", *university_worker_population * 3);
    printf("\n");
    return 0;
}

int terminal_init()
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
                printf("%d/40 - %s\n", i + 1, resourceNames[i]);
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
    free(str);
    return 0;
}