#include "vars.h"

int input(char *, char *, int);
int strcompare(char *, char *);
int get_factory_type(char[][64]);
int define_resource_names(char[][64]);
int zerofactory(struct factory *);
int newfactory(struct factory *, int);
int checkratio(double *);
int calculate(struct factory *, double, struct factory *, double *, char[][64], int *, double *);
int results(struct factory *, double *, char[][64], int *, double *);