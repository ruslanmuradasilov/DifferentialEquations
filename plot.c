#include "odu_32.h"

void draw(double a, double b, double h, double *result)
{
    FILE *pipe = popen("gnuplot -persistent", "w");

    fprintf(pipe, "plot '-' with linespoints pointtype 0 lw 5 lt rgb \"#7CFC00\"  title 'Source function'");
    fprintf(pipe, " , '-' with linespoints pointtype 0 lw 5 lt rgb \"#1d2666\" title 'Approximation'\n");

    double left = a, right = b;
    for (; left < right; left += 0.001)
        fprintf(pipe, "%lf %lf\n", left, y(left));

    fprintf(pipe, "%s\n", "e");
    fflush(pipe);

    int n = (int) ((b - a) / h);
    left = a;
    for (int i = 0; i <= n; i++, left += h)
        fprintf(pipe, "%lf %lf\n", left, result[i]);

    fprintf(pipe, "%s\n", "e");
    fflush(pipe);
    pclose(pipe);
}

