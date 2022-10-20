#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

struct spoint {
    double x, y;
};
bool vect(int n, ...) {
    if (n < 3) {
        return false;
    }
    else if (n  == 3) {
        return true;
    }
    bool Flag = false;
    va_list factor;
    va_start(factor, n);
    typedef struct spoint coordinates;
    coordinates *mas_p;
    mas_p = (coordinates*)malloc(n*(sizeof(coordinates)));
    for (int i = 0; i < n; i++) {
        coordinates p;
        coordinates *pPtr = NULL;
        pPtr = &p;
        p.x = va_arg(factor, double);
        p.y = va_arg(factor, double);
        mas_p[i] = *pPtr;
    }
    for(int i = 0; i < n; i++) {
        double dx1 = mas_p[(i + 2) % n].x - mas_p[(i + 1) % n].x;
        double dy1 = mas_p[(i + 2) % n].y - mas_p[(i + 1) % n].y;
        double dx2 = mas_p[i].x - mas_p[(i + 1) % n].x;
        double dy2 = mas_p[i].y - mas_p[(i + 1) % n].y;
        double rez = dx1 * dy2 - dy1 * dx2;
        if (i == 0) {
            Flag = rez > 0;
        }
        else if (Flag != (rez > 0)) {
            return false;
        }
    }
    return true;
}
double polynom(int x, int n, ...) {
    double res = 0.0;
    va_list factor;
    va_start(factor, n);
    for (int i = 0; i <= n; i++) {
        res = res * x + va_arg(factor, double);
    }
    return res;
}
int main(void) {
    if (vect(4, 1.2, 2.0, 3.5, 4.9, 5.1, 2.8, 3.0, 0.0)) {
        printf("YES\n");
    }
    else {
        printf("No\n");
    }
    printf("%lf\n", polynom(-2, 3, 1.5, 2.5, 9.0, 1.0));
    return 0;
}
