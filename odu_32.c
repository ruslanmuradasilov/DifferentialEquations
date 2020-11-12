#include "odu_32.h"

// y' := g1
// z' := g2

size_t memoryForResult(double a, double b, double h)
{
    int n = (int) ((b - a) / h + 1);
    return n * sizeof(double);
}

size_t memoryForYZLast()
{
    return 8 * sizeof(double);
}

double g1(double x, double y, double z)
{
    return z;
}

double g2(double x, double y, double z)
{
    return f(x) - p(x) * z - q(x) * y;
}

double metric(const double *result, const double *result_2, int n)
{
    int i;
    double sum = 0;

    for (i = 0; i < n; i++)
//        sum += fabs(result[i] - result_2[i * 2]);
        sum += (result[i] - result_2[i * 2]) * (result[i] - result_2[i * 2]);

    return sum / n;
}

void Adams_Moulton(double a, double b, double c, double t, double h, int n, double *yz_last, double *result)
{
    double k11, k12, k13, k14;
    double k21, k22, k23, k24;
    double x0, y0, z0, y1, z1;
    double *y_last = yz_last;
    double *z_last = yz_last + 4;
    int i, j;

    x0 = a;
    y0 = c;
    z0 = t;
    result[0] = y0;

    for (i = 0; i < __min(n, 4); i++, x0 += h)
    {
        k11 = h * g1(x0, y0, z0);
        k21 = h * g2(x0, y0, z0);

        k12 = h * g1(x0 + h / 2, y0 + k11 / 2, z0 + k21 / 2);
        k22 = h * g2(x0 + h / 2, y0 + k11 / 2, z0 + k21 / 2);

        k13 = h * g1(x0 + h / 2, y0 + k12 / 2, z0 + k22 / 2);
        k23 = h * g2(x0 + h / 2, y0 + k22 / 2, z0 + k22 / 2);

        k14 = h * g1(x0 + h, y0 + k13, z0 + k23);
        k24 = h * g2(x0 + h, y0 + k13, z0 + k23);

        y1 = y0 + (k11 + 2 * k12 + 2 * k13 + k14) / 6;
        z1 = z0 + (k21 + 2 * k22 + 2 * k23 + k24) / 6;

        y_last[i] = y1;
        z_last[i] = z1;

        y0 = y1;
        z0 = z1;

        result[i + 1] = y0;
    }

    for (i = 4; i < n; i++, x0 += h)
    {
        y1 = y_last[3] + h * (55 * g1(x0, y_last[3], z_last[3]) - 59 * g1(x0 - h, y_last[2], z_last[2]) +
                              37 * g1(x0 - 2 * h, y_last[1], z_last[1]) - 9 * g1(x0 - 3 * h, y_last[0], z_last[0])) /
                         24;

        z1 = z_last[3] + h * (55 * g2(x0, y_last[3], z_last[3]) - 59 * g2(x0 - h, y_last[2], z_last[2]) +
                              37 * g2(x0 - 2 * h, y_last[1], z_last[1]) - 9 * g2(x0 - 3 * h, y_last[0], z_last[0])) /
                         24;

        y1 = y_last[3] + h * (9 * g1(x0 + h, y1, z1) + 19 * g1(x0, y_last[3], z_last[3]) -
                              5 * g1(x0 - h, y_last[2], z_last[2]) + g1(x0 - 2 * h, y_last[1], z_last[1])) / 24;

        z1 = z_last[3] + h * (9 * g2(x0 + h, y1, z1) + 19 * g2(x0, y_last[3], z_last[3]) -
                              5 * g2(x0 - h, y_last[2], z_last[2]) + g2(x0 - 2 * h, y_last[1], z_last[1])) / 24;

        for (j = 0; j < 3; j++)
        {
            y_last[j] = y_last[j + 1];
            z_last[j] = z_last[j + 1];
        }

        y_last[3] = y1;
        z_last[3] = z1;

        result[i + 1] = y1;
    }
}

double G(double a, double b, double c, double t, double h, double *yz_last, double *result, double d)
{
    int n = (int) ((b - a) / h);
    Adams_Moulton(a, b, c, t, h, n, yz_last, result);
    return result[n - 1] - d;
}


int find_interval(double a, double b, double c, double d, double h, double *yz_last, double *result, double *left,
                  double *right)
{
    double left_error, right_error, step = 1;
    while (1)//подбор интервала
    {
        left_error = G(a, b, c, *left, h, yz_last, result, d);
        right_error = G(a, b, c, *right, h, yz_last, result, d);
        if (left_error * right_error < 0)
            break;
        *left -= step;
        *right += step;
//        printf("%lf, %lf\n", left, right);
        if (*right > 1000)
            return -1;//нет решения
    }

    if (left_error > 0)
        return 0;//убывает
    else
        return 1;//возрастает
}

void shoot(double a, double b, double c, double d, double h, double eps, double *yz_last, double *result, double left,
           double right, int G_ascends)
{
    double middle, error;
    while (1)//метод половинного деления
    {
        middle = (left + right) / 2;
        error = G(a, b, c, middle, h, yz_last, result, d);

        if (fabs(error) < eps)
            break;

        if (error < 0)
        {
            if (G_ascends == 0)
                right = middle;
            else
                left = middle;
        }

        if (error > eps)
        {
            if (G_ascends == 0)
                left = middle;
            else
                right = middle;
        }
    }
}


//int solver(double a, double b, double c, double d, double h, double eps, double *yz_last, double *result)
//{
//    double left, right, middle;
//    double left_error, right_error, error;
//
//    int G_ascends = 1;//возрастает
//    double step = 1;
//    left = 0;
//    right = 0;
//
////    left = -338;
////    right = -337;
//
//    while (1)//подбор интервала
//    {
//        left_error = G(a, b, c, left, h, yz_last, result, d);
//        right_error = G(a, b, c, right, h, yz_last, result, d);
//        if (left_error * right_error < 0)
//            break;
//        left -= step;
//        right += step;
////        printf("%lf, %lf\n", left, right);
//        if (right > 1000)
//            return -1;//нет решения
//    }
//
//    if(left_error > 0)
//        G_ascends = 0;//убывает
//
//    while (1)//метод половинного деления
//    {
//        middle = (left + right) / 2;
//        error = G(a, b, c, middle, h, yz_last, result, d);
//
//        if (fabs(error) < eps)
//            break;
//
//        if (error < 0)
//        {
//            if(G_ascends == 0)
//                right = middle;
//            else
//                left = middle;
//        }
//
//        if (error > eps)
//        {
//            if(G_ascends == 0)
//                left = middle;
//            else
//                right = middle;
//        }
//    }
//
//    return 0;
//}
