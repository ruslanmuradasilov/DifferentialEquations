//
// 32. Метод сведение уравнения к системе второго порядка,
// нахождения решения этой системы ДУ метод Адамса-Мултона
// и используя метод пристрелки (с методом деления пополам) для решения уравнения
//

// y''+p(x)*y'+q(x)*y = f(x)
// z = y'
// z'= f(x)-p(x)*y'-q(x)*y
// y(a) = c, y(b) = d

#include "odu_32.h"
#include <time.h>

// Тест 1: (-2, 2), loss: 0
// Тест 2: (-2, 2), loss: 0
// Тест 3: (-9, 9), loss: 0
// Тест 4: (-2, 2), loss: 0
// Тест 5: (-4, 4), loss: 0
// Тест 6: (-338, 338), loss: ???
// Тест 7: (-4, 4), loss: 0


size_t memoryForResult(double a, double b, double h)
{
    int n = (int) ((b - a) / h + 1);
    return n * sizeof(double);
}

size_t memoryForYZLast()
{
    return 8 * sizeof(double);
}

int test = 7;

int main()
{
    double a, b, h = 0.00001, eps = 0.00001;

    switch (test)
    {
        case 1: a = 0, b = 1; break;// 1
        case 2: a = 0, b = 2; break; // 2
        case 3: a = 0, b = 3; break; // 3
        case 4: a = 2, b = 5; break; // 4 *d
        case 5: a = 0.5, b = 1.5; break; // 5 *d
        case 6: a = 0, b = 1; break; // 6 *d
        case 7: a = 1, b = 3; break; // 7
        default: printf("Bad test %d", test); exit(1);
    }

    double c = y(a), d = y(b);

//    double a = 0, b = 1, c = y(a), d = y(b); // 1   0 1 1 2 0.00001 0.00001
//    double a = 0, b = 2, c = y(a), d = y(b); // 2   0 2 1 6.0183156388887342 0.00001 0.00001
//    double a = 0, b = 3, c = y(a), d = y(b); // 3   0 3 1 -17 0.00001 0.00001
//    double a = 2, b = 5, c = y(a), d = y(b); // 4 *d   2 5 6 2.6009019194419478 0.00001 0.00001
//    double a = 0.5, b = 1.5, c = y(a), d = y(b); // 5 *d   0.5 1.5 1.3253490364501026 4.9797819695946446 0.00001 0.00001
//    double a = 0, b = 1, c = y(a), d = y(b); // 6 *d   0 1 0 3.7194955983552602 0.00001 0.00001
//    double a = 1, b = 2, c = y(a), d = y(b); // 7   1 2 3.7194955983552602 7.4625122304402547 0.00001 0.00001

//    FILE *in, *out;
//
//    if ((in = fopen("../in.txt", "r")) == NULL)
//    {
//        printf("Cannot open infile");
//        getchar();
//        return -2;
//    }
//
//    if ((out = fopen("../out.txt", "w")) == NULL)
//    {
//        printf("Cannot open outfile");
//        getchar();
//        return -3;
//    }

//    double a, b, c, d, h, eps;
//    fscanf(in, "%lf", &a);
//    fscanf(in, "%lf", &b);
//    fscanf(in, "%lf", &c);
//    fscanf(in, "%lf", &d);
//    fscanf(in, "%lf", &h);
//    fscanf(in, "%lf", &eps);

    double x, loss = 0;
    int n = (int) ((b - a) / h), i, rtn;
    double *result = malloc((memoryForResult(a, b, h)));
    double *yzlast = malloc(memoryForYZLast());

    clock_t start, end;
    start = clock();
    rtn = solver(a, b, c, d, h, eps, yzlast, result);
    end = clock();

    if(rtn)
        printf("Interval was not found!");
    else
        {
            printf("time: %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
            printf("nodes: %d\n", n + 1);

            x = a;
            for (i = 0; i <= n; i++)
            {
//                fprintf(out, "%1.9lf %1.9lf\n", x, result[i]);
                loss += (y(x) - result[i]) * (y(x) - result[i]);
                loss /= n;
                x += h;
            }

            printf("loss: %f", loss);
            draw(a, b, h, result);
        }


    free(result);
    free(yzlast);

//    fclose(in);
//    fclose(out);

    return 0;
}