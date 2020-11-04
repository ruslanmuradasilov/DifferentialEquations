#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int test;

double p(double x);

double q(double x);

double f(double x);

double y(double x);

void Adams_Moulton(double a, double b, double c, double t, double h, int n, double *yzlast, double *result);

double G(double a, double b, double c, double t, double h, double *yzlast, double *result, double d);

int solver(double a, double b, double c, double d, double h, double eps, double *yzlast, double *result);

void draw(double a, double b, double h, double *result);