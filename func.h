#include "vars.h"

int input(char *, char *, int);
int strcompare(char *, char *);
int get_factory_type(char[][64]);
int define_resource_names(char[][64]);
int zerofactory(struct factory *);
int newfactory(struct factory *, enum resource_ids);
int checkratio(double *);
int calculate(struct factory *, double, struct factory *, double *, char[][64], int *, int *, double *);
int results(struct factory *, double *, char[][64], int *, int *, double *);
int terminal_init();