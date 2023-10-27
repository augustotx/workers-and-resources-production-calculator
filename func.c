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
    strcpy(resourceNames[0], "gravel");
    strcpy(resourceNames[1], "stone");
    strcpy(resourceNames[2], "coal ore");
    strcpy(resourceNames[3], "coal");
    strcpy(resourceNames[4], "iron ore");
    strcpy(resourceNames[5], "iron");
    strcpy(resourceNames[6], "raw bauxite");
    strcpy(resourceNames[7], "bauxite");
    strcpy(resourceNames[8], "uranium ore");
    strcpy(resourceNames[9], "steel");
    strcpy(resourceNames[10], "prefabs");
    strcpy(resourceNames[11], "bricks");
    strcpy(resourceNames[12], "wood");
    strcpy(resourceNames[13], "board");
    strcpy(resourceNames[14], "aluminium");
    strcpy(resourceNames[15], "uranium oxide");
    strcpy(resourceNames[16], "crops");
    strcpy(resourceNames[17], "chemicals");
    strcpy(resourceNames[18], "fabric");
    strcpy(resourceNames[19], "clothes");
    strcpy(resourceNames[20], "alcohol");
    strcpy(resourceNames[21], "food");
    strcpy(resourceNames[22], "plastics");
    strcpy(resourceNames[23], "mechanical components");
    strcpy(resourceNames[24], "electronic components");
    strcpy(resourceNames[25], "electronics");
    strcpy(resourceNames[26], "oil");
    strcpy(resourceNames[27], "fuel");
    strcpy(resourceNames[28], "bitumen");
    strcpy(resourceNames[29], "aluminium oxide");
    strcpy(resourceNames[30], "asphalt");
    strcpy(resourceNames[31], "cement");
    strcpy(resourceNames[32], "concrete");
    strcpy(resourceNames[33], "livestock");
    strcpy(resourceNames[34], "meat");
    strcpy(resourceNames[35], "nuclear fuel");
    strcpy(resourceNames[36], "nuclear waste (there's no waste factory)");
    strcpy(resourceNames[37], "uf6");
    strcpy(resourceNames[38], "power (not available yet)");
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
    char *list = malloc(64 * sizeof(char));
    strcpy(list, "list");
    input("Choose a factory type: (type in \"list\" to see options)\n-> ", buffer, 64);
    if (strcompare(buffer, list))
    {
        return -2;
    }
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        if (strlen(resourceNames[i]) == 0)
        {
            continue;
        }
        if (strcompare(resourceNames[i], buffer))
        {
            free(list);
            free(buffer);
            return i;
        }
    }

    free(buffer);
    free(list);
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
    factory->university_workers = 0;
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
    case 2:
        factory->outputs[factoryType] = 924.0; // coal ore mine at 100% capacity/day

        factory->workers = 220;
        break;
    case 3:
        factory->outputs[factoryType] = 120.0; // coal/day

        factory->inputs[2] = 210.0;

        factory->workers = 15;
        break;
    case 4:
        factory->outputs[factoryType] = 1000.0; // iron ore mine at 100% capacity/day

        factory->workers = 250;
        break;
    case 5:
        factory->outputs[factoryType] = 105.0; // iron/day

        factory->inputs[4] = 225.0;

        factory->workers = 15;
        break;
    case 6:
        factory->outputs[factoryType] = 22.5; // raw bauxite/day (i still have to check vehicle performance compared to workers)

        factory->workers = 45;
        break;
    case 7:
        factory->outputs[factoryType] = 75.0; // bauxite/day

        factory->inputs[6] = 125.0;

        factory->workers = 25;
        break;
    case 8:
        factory->outputs[factoryType] = 75.0; // uranium ore/day

        factory->workers = 100;
        break;
    case 9:
        factory->outputs[factoryType] = 43.0; // steel/day

        factory->inputs[3] = 375.0;
        factory->inputs[5] = 200.0;

        factory->workers = 500;
        break;
    case 10:
        factory->outputs[factoryType] = 71.0; // prefabs/day

        factory->inputs[0] = 65.0;
        factory->inputs[31] = 9.8;

        factory->workers = 65;
        break;
    case 11:
        factory->outputs[factoryType] = 51.0; // bricks/day

        factory->inputs[3] = 33.0;

        factory->workers = 75;
        break;
    case 12:
        factory->outputs[factoryType] = 189.0; // wood/day

        factory->inputs[27] = 1.5; // 3 vehicles estimate consumption

        factory->workers = 30;
        break;
    case 13:
        factory->outputs[factoryType] = 140.0; // boards/day

        factory->inputs[12] = 180.0;

        factory->workers = 20;
        break;
    case 14:
        factory->outputs[factoryType] = 30.0; // aluminium/day

        factory->inputs[29] = 52.0;
        factory->inputs[17] = 2.5;

        factory->workers = 350;
        break;
    case 15:
        factory->outputs[factoryType] = 1.7; // uranium oxide/day

        factory->inputs[8] = 36.0;

        factory->workers = 60;
        factory->university_workers = 15;
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
    case 18:
        factory->outputs[factoryType] = 5.0; // fabric/day

        factory->inputs[16] = 20.0;
        factory->inputs[17] = 0.5;
        factory->inputs[39] = 11.0;

        factory->workers = 100;
        break;
    case 19:
        factory->outputs[factoryType] = 1.2; // clothes/day

        factory->inputs[18] = 2.4;

        factory->workers = 80;
        break;
    case 20:
        factory->outputs[factoryType] = 6.0; // alcohol/day

        factory->inputs[16] = 30.0;
        factory->inputs[39] = 13.0;

        factory->workers = 100;
        break;
    case 21:
        factory->outputs[factoryType] = 20.0; // food/day

        factory->inputs[39] = 8.5;  // water/day needed
        factory->inputs[16] = 42.0; // crops/day needed

        factory->workers = 170;
        break;
    case 22:
        factory->outputs[factoryType] = 6.6; // plastics/day

        factory->inputs[17] = 3.0;
        factory->inputs[26] = 27.0;

        factory->workers = 60;
        break;
    case 23:
        factory->outputs[factoryType] = 33.0; // mechanical components/day

        factory->inputs[9] = 22.0;

        factory->workers = 150;
        break;
    case 24:
        factory->outputs[factoryType] = 3.4; // electronic components/day

        factory->inputs[9] = 1.7;
        factory->inputs[17] = 1.3;
        factory->inputs[22] = 1.7;

        factory->workers = 150;
        break;
    case 25:
        factory->outputs[factoryType] = 4.1; // electronics/day

        factory->inputs[23] = 1.7;
        factory->inputs[24] = 1.7;
        factory->inputs[22] = 2.5;
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
    case 28:
        newfactory(factory, 27); // bitumen is from the oil refinery
        break;
    case 29:
        factory->outputs[factoryType] = 33.0; // aluminium oxide/day

        factory->inputs[39] = 29.0;
        factory->inputs[17] = 2.6;
        factory->inputs[3] = 29.0;
        factory->inputs[7] = 77.0;

        factory->workers = 370;
        break;
    case 30:
        // asphalt plant I dialed back the numbers a bit because no one uses it 100% of the time, come on
        factory->outputs[factoryType] = 145.0 / 4.0; // asphalt/day

        factory->inputs[28] = 20.0 / 4.0;
        factory->inputs[0] = 120.0 / 4.0;

        factory->workers = 5;
        break;
    case 31:
        factory->outputs[factoryType] = 81.0; // cement/day

        factory->inputs[3] = 22.0;
        factory->inputs[0] = 210.0;

        factory->workers = 30;
        break;
    case 32:
        // same case as asphalt plant
        factory->outputs[factoryType] = 175.0 / 4.0; // concrete/day

        factory->inputs[39] = 85.0 / 4.0;
        factory->inputs[31] = 30.0 / 4.0;
        factory->inputs[0] = 135.0 / 4.0;

        factory->workers = 5;
        break;
    case 33:
        factory->outputs[factoryType] = 5.0; // livestock/day

        factory->inputs[16] = 10.0;

        factory->workers = 50;
        break;
    case 34:
        factory->outputs[factoryType] = 60.0; // meat/day

        factory->inputs[33] = 150.0;

        factory->workers = 50;
        break;
    case 35:
        factory->outputs[factoryType] = 0.095; // nuclear fuel/day

        factory->inputs[37] = 0.4;
        factory->inputs[17] = 0.75;

        factory->workers = 50;
        factory->university_workers = 70;
        break;
    case 36:
        // nuclear waste factory? lmao
        break;
    case 37:
        factory->outputs[factoryType] = 0.96; // UF6/day

        factory->inputs[17] = 0.21;
        factory->inputs[15] = 2.0;

        factory->workers = 80;
        factory->university_workers = 40;
        break;
    case 38:
        // power factory? (future power plant calculation?)
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

int calculate(struct factory *factory, double amount, struct factory *resource_pool, double *factory_count, char resourceNames[][64], int *worker_population, int *university_worker_population, double *sewage)
{
    *sewage += factory->inputs[39];
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
    if (resource_pool->inputs[39] > 0.0)
    {
        printf("\nIndustry-made sewage to take care of: %f\n", *sewage);
    }
    printf("\nWorkers needed: %d\n", *worker_population * 3);
    printf("\nUniversity workers needed: %d\n", *university_worker_population * 3);
    printf("\n");
    return 0;
}