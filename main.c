#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"
#include "vars.h"
#include "gui/guifunc.h"

// Saved data for future updates
/*
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
*/

int main(int argc, char **argv)
{
    // First, check if the program was run with the "--gui" argument
    if (argc > 1 && strcmp(argv[1], "--gui") == 0) {
        gui_init(); // Initialize GUI mode
    } else if (isatty(fileno(stdin))) {
        terminal_init(); // Initialize terminal mode if stdin is a terminal
    } else {
        // If stdin is not a terminal and "--gui" was not specified
        terminal_init();
    }
    // All the main code is moved to gui/guifuncs.c
    return 0;
}
