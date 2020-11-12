#include "odu_32.h"

double p(double x)
{
    switch (test)
    {
        case 1: return -2 * x / (x * x + 1);
        case 2: return 4 * x / (2 * x + 1);
        case 3: return -2 * x / (x * x + 1);
        case 4: return -1 / (x * log(x));
        case 5: return (x * tan(x) - 2) / x;
        case 6: return -1;
        case 7: return -(x * x + 3) / x;
        default: printf("Bad test %d", test); exit(1);
    }
}

double q(double x)
{
    switch (test)
    {
        case 1: return 2 / (x * x + 1);
        case 2: return -4 / (2 * x + 1);
        case 3: return 2 / (x * x + 1);
        case 4: return 1 / (x * x * log(x));
        case 5: return (2 - x * tan(x)) / (x * x);
        case 6: return 10000;
        case 7: return (x * x + 3) / (x * x);
        default: printf("Bad test %d", test); exit(1);
    }
}

double f(double x)
{
    switch (test)
    {
        case 1: return 0;
        case 2: return 0;
        case 3: return x * x + 1;
        case 4: return -log(x);
        case 5: return x * exp(x) * cos(x);
        case 6: return 100 * exp(x) * cos(100 * x);
        case 7: return 10 * x * x * x * sin(x * x);
        default: printf("Bad test %d", test); exit(1);
    }
}

double y(double x)
{
    switch (test)
    {
        case 1: return 1 - x * x + 2 * x;
        case 2: return 3 * x + exp(-2 * x);
        case 3: return 1 - x * x + 2 * x - 11 * x + (x * x * x * x) / 6.0 + (x * x) / 2.0;
        case 4: return x + 2 * (log(x) + 1) + 0.5 * x * x * (1 - log(x));
        case 5: return x * (1 + sin(x)) + 0.5 * x * exp(x) * (cos(x) + sin(x));
        case 6: return exp(x) * sin(x);
        case 7: return x * (1 + exp(0.5 * x * x)) + x * (cos(x * x) - 2 * sin(x * x));
        default: printf("Bad test %d", test); exit(1);
    }
}