#include <stdio.h>
#include <stdlib.h>
#include "vars.h"

int zerofact(struct factory *fact)
{
    fact->gravel = 0.0;
    fact->stone = 0.0;
    fact->coal = 0.0;
    fact->coal_ore = 0.0;
    fact->iron = 0.0;
    fact->iron_ore = 0.0;
    fact->bauxite = 0.0;
    fact->bauxite_ore = 0.0;
    fact->uranium_ore = 0.0;
    fact->steel = 0.0;
    fact->prefab = 0.0;
    fact->brick = 0.0;
    fact->wood = 0.0;
    fact->board = 0.0;
    fact->aluminium = 0.0;
    fact->uranium_oxide = 0.0;
    fact->crops = 0.0;
    fact->chemicals = 0.0;
    fact->fabric = 0.0;
    fact->clothes = 0.0;
    fact->alcohol = 0.0;
    fact->food = 0.0;
    fact->plastics = 0.0;
    fact->mechanical_components = 0.0;
    fact->electronic_components = 0.0;
    fact->electronics = 0.0;
    fact->oil = 0.0;
    fact->fuel = 0.0;
    fact->bitumen = 0.0;
    fact->aluminium_oxide = 0.0;
    fact->asphalt = 0.0;
    fact->cement = 0.0;
    fact->concrete = 0.0;
    fact->livestock = 0.0;
    fact->meat = 0.0;
    fact->nuclear_fuel = 0.0;
    fact->nuclear_waste = 0.0;
    fact->uf6 = 0.0;
    fact->workers = 0;
    fact->power = 0.0;
    fact->water = 0.0;
    fact->output = 0.0;
    fact->output2 = 0.0;
    fact->sewage = 0.0;
    fact->pollution = 0;
}

int initfact(struct factory *fact, int factory_type)
{
    if (!zerofact(fact))
    {
        return 1;
    }

    switch (factory_type)
    {
    case 0:
        // Clothes

        // Workers
        fact->workers = 80;

        // Inputs
        fact->fabric = 2.4;
        fact->power = 60.0;

        // Outputs
        fact->pollution = 1;
        fact->output = 1.2;
        break;

    case 1:
        // Fabric
        fact->workers = 100;

        fact->chemicals = 0.5;
        fact->water = 11.0;
        fact->crops = 20.0;
        fact->power = 330.0;

        fact->pollution = 1;
        fact->sewage = fact->water;
        fact->output = 5.0;
        break;

    case 2:
        // Chemical
        fact->workers = 60;

        fact->gravel = 0.72;
        fact->water = 10.0;
        fact->crops = 0.78;
        fact->wood = 0.84;
        fact->oil = 1.2;
        fact->power = 320.0;

        fact->pollution = 1;
        fact->sewage = fact->water;
        fact->output = 0.81;
        break;

    case 3:
        // Gravel plant
        fact->workers = 15;

        fact->stone = 120.0;
        fact->power = 407.0;

        fact->pollution = 1;
        fact->output = 82.0;
        break;

    case 4:
        // Quarry
        fact->power = 163.0;
        fact->fuel = 0.4;

        fact->pollution = 1;
        fact->output = 140.0;
        break;

    case 5:
        // Woodcutter
        fact->workers = 30;

        fact->power = 121.0;

        fact->pollution = 0;
        fact->output = 189.0;
        break;

    case 6:
        // Pumpjack
        fact->power = 114.0;

        fact->pollution = 1;
        fact->output = 7.0;
        break;

    case 7:
        // oil refinery
        fact->workers = 500;

        fact->oil = 250.0;

        fact->pollution = 1;
        fact->power = 12.0;

        fact->output = 125.0;
        fact->output2 = 75.0;
        break;

    case 8:
        // small water plant
        fact->workers = 5;

        fact->power = 0.17;

        fact->pollution = 0;
        fact->output = 120.0;
        break;

    case 9:
        // big water plant
        fact->workers = 10;

        fact->power = 0.23;

        fact->pollution = 0;
        fact->output = 300.0;
        break;

    case 10:
        // small farm
        fact->power = 50.0;

        fact->fuel = 0.4 * 6.0;

        fact->pollution = 0;
        fact->output = 300.0 * 3;
        break;

    case 11:
        // medium farm
        fact->power = 50.0;

        fact->fuel = 0.4 * 6.0;

        fact->pollution = 0;
        fact->output = 300.0 * 6;
        break;

    case 12:
        // big farm
        fact->power = 50.0;

        fact->fuel = 0.4 * 6.0;

        fact->pollution = 0;
        fact->output = 300.0 * 15;
        break;

    default:
        break;
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

int calculate(struct factory *factories, int *worker_population, double *power_consumption, double *worker_food, double *worker_meat, double *worker_clothes, double *worker_electronics, double worker_alcohol, struct factory *prod_values)
{
    for (int i = 0; i < 64; i++)
    {
        struct factory *fact = (struct factory *)malloc(sizeof(struct factory));
        if (factories[i].output == 0.0)
        {
            break;
        }
        fact->gravel = factories[i].gravel;
        fact->stone = factories[i].stone;
        fact->coal = factories[i].coal;
        fact->coal_ore = factories[i].coal_ore;
        fact->iron = factories[i].iron;
        fact->iron_ore = factories[i].iron_ore;
        fact->bauxite = factories[i].bauxite;
        fact->bauxite_ore = factories[i].bauxite_ore;
        fact->uranium_ore = factories[i].uranium_ore;
        fact->steel = factories[i].steel;
        fact->prefab = factories[i].prefab;
        fact->brick = factories[i].brick;
        fact->wood = factories[i].wood;
        fact->board = factories[i].board;
        fact->aluminium = factories[i].aluminium;
        fact->uranium_oxide = factories[i].uranium_oxide;
        fact->crops = factories[i].crops;
        fact->chemicals = factories[i].chemicals;
        fact->fabric = factories[i].fabric;
        fact->clothes = factories[i].clothes;
        fact->alcohol = factories[i].alcohol;
        fact->food = factories[i].food;
        fact->plastics = factories[i].plastics;
        fact->mechanical_components = factories[i].mechanical_components;
        fact->electronic_components = factories[i].electronic_components;
        fact->electronics = factories[i].electronics;
        fact->oil = factories[i].oil;
        fact->fuel = factories[i].fuel;
        fact->bitumen = factories[i].bitumen;
        fact->aluminium_oxide = factories[i].aluminium_oxide;
        fact->asphalt = factories[i].asphalt;
        fact->cement = factories[i].cement;
        fact->concrete = factories[i].concrete;
        fact->livestock = factories[i].livestock;
        fact->meat = factories[i].meat;
        fact->nuclear_fuel = factories[i].nuclear_fuel;
        fact->nuclear_waste = factories[i].nuclear_waste;
        fact->uf6 = factories[i].uf6;
        fact->workers = factories[i].workers;
        fact->power = factories[i].power;
        fact->water = factories[i].water;
        fact->sewage = factories[i].sewage;
        free(fact);
    }
    return 0;
}