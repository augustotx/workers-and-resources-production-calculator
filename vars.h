#ifndef VARS_H
#define VARS_H
#define RESOURCE_COUNT 40

struct factory
{
    double inputs[RESOURCE_COUNT];
    double outputs[RESOURCE_COUNT];
    int workers;
};
#endif

/* RESOURCE LIST/ARRAY
// Aggregates
0     gravel;
1     stone;
2     coal;
3     coal_ore;
4     iron;
5     iron_ore;
6     bauxite;
7     bauxite_ore;
8     uranium_ore;

    // Open Storage
9     steel;
10     prefab;
11     brick;
12     wood;
13     board;
14     aluminium;
15     uranium_oxide;

    // Warehouse
16     crops;
17     chemicals;
18     fabric;
19     clothes;
20     alcohol;
21     food;
22     plastics;
23     mechanical_components;
24     electronic_components;
25     electronics;

    // Liquids
26     oil;
27     fuel;
28     bitumen;

    // Other
29     aluminium_oxide;
30     asphalt;
31     cement;
32     concrete;
33     livestock;
34     meat;
35     nuclear_fuel;
36     nuclear_waste;
37     uf6;

    // Specific inputs
38     power;
39     water;
40     workers;
*/