#ifndef VARS_H
#define VARS_H

#define RESOURCE_COUNT 40

// CONSUMPTION PER WORKER PER YEAR
// got this data from https://steamcommunity.com/app/784150/discussions/0/3454842150489701958/

// I also put a number bigger than the actual estimates so that
// production is always more than consumption

#define WORKER_FOOD 0.17
#define WORKER_MEAT 0.038
#define WORKER_CLOTHES 0.005

// this estimate I don't have much basis on
// (got it from a ratio I made from a dude's reply in that steam link)
#define WORKER_ELECTRONICS 0.0085

enum resource_ids
{
    gravel,
    stone,
    coal_ore,
    coal,
    iron_ore,
    iron,
    bauxite_ore,
    bauxite,
    uranium_ore,

    // Open Storage
    steel,
    prefab,
    brick,
    wood,
    board,
    aluminium,
    uranium_oxide,

    // Warehouse
    crops,
    chemicals,
    fabric,
    clothes,
    alcohol,
    food,
    plastics,
    mechanical_components,
    electronic_components,
    electronics,

    // Liquids
    oil,
    fuel,
    bitumen,

    // Other
    aluminium_oxide,
    asphalt,
    cement,
    concrete,
    livestock,
    meat,
    nuclear_fuel,
    nuclear_waste,
    uf6,

    // Specific inputs
    power,
    water,

    // garbage
    bio_waste,
    metal_scrap,
    aluminium_scrap,
    construction_waste,
    plastic_waste,
    hazardous_waste,
    burnable_waste,
    other_waste,
    ash,

    // None
    none,

    // list
    list
};

struct factory
{
    double inputs[RESOURCE_COUNT];
    double outputs[RESOURCE_COUNT];
    int workers;
    int university_workers;
};
#endif
