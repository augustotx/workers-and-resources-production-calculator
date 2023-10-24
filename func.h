#include "vars.h"

int define_resource_names(char [][64]);
int zerofact(double *);
int initfact(int, double *);
int checkratio(double *);
int calculate(char [][64], double *, double *, double [FACTORY_SIZE][FACTORY_SIZE],int,double, int *);
int showresults(char [][64], double *);