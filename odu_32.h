#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int test;

double p(double x);

double q(double x);

double f(double x);

double y(double x);

size_t memoryForResult(double a, double b, double h);

size_t memoryForYZLast();

double metric(const double *result, const double *result_2, int n);

void Adams_Moulton(double a, double b, double c, double t, double h, int n, double *yz_last, double *result);

double G(double a, double b, double c, double t, double h, double *yz_last, double *result, double d);

int find_interval(double a, double b, double c, double d, double h, double *yz_last, double *result, double *left,
                  double *right);

void shoot(double a, double b, double c, double d, double h, double eps, double *yz_last, double *result, double left,
           double right, int G_ascends);

//int solver(double a, double b, double c, double d, double h, double eps, double *yz_last, double *result);

void draw(double a, double b, double h, double *result);