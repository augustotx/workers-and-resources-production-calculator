// Factories
struct factory
{
    // INPUTS

    // Aggregates
    double gravel;
    double stone;
    double coal;
    double coal_ore;
    double iron;
    double iron_ore;
    double bauxite;
    double bauxite_ore;
    double uranium_ore;

    // Open Storage
    double steel;
    double prefab;
    double brick;
    double wood;
    double board;
    double aluminium;
    double uranium_oxide;

    // Warehouse
    double crops;
    double chemicals;
    double fabric;
    double clothes;
    double alcohol;
    double food;
    double plastics;
    double mechanical_components;
    double electronic_components;
    double electronics;

    // Liquids
    double oil;
    double fuel;
    double bitumen;

    // Other
    double aluminium_oxide;
    double asphalt;
    double cement;
    double concrete;
    double livestock;
    double meat;
    double nuclear_fuel;
    double nuclear_waste;
    double uf6;

    // Specific inputs
    int workers;
    double power;
    double water;

    // OUTPUTS
    double output;
    double output2;
    double sewage;

    // PROPERTIES
    int pollution; // 1 = true, 0 = false
};