#include <stdio.h>
#include <math.h>

///f1 = 3 (0.5 / (x + 1) + 1)   f' = 1.5/(x+1)^2
///f2 = 2.5x − 9.5              f' = 2.5
///f3 = 5 / x                   f' = 5/x^2
///get_val_f1.asm
///get_val_f2.asm
///get_val_f3.asm


double exmp1(double x) {
    return x * x;
}

double dexmp1(double x) {
    return 2 * x;
}

double exmp2(double x) {
    return x;
}

double dexmp2(double x) {
    return 1;
}

double get_root(double (*f)(double), double (*fd)(double), double (*g)(double), double (*gd)(double), double a, double b, const double e, int* iteratinon) {
    double F_a = f(a) - g(a);
    double F_b = f(b) - g(b);



    while (fabs(a - b) > e) {
        (*iteratinon)++;
        int first_p = 1;
        if (F_a > 0) {
            first_p = -1;
        }
        int second_p = 1;
        double mid = (a + b) / 2;
        double F_mid = f(mid) - g(mid);
        if (F_mid > ((F_a + F_b) / 2)) {
            second_p = -1;
        }

        double cross_point;
        if (first_p * second_p > 0) {
            cross_point = b - F_b / (fd(b) - gd(b));
            if (fabs(b - cross_point) < e) return b;
            b = cross_point;
            F_b = f(cross_point) - g(cross_point);
        } else {
            cross_point = a-   F_a / (fd(a) - gd(a));
            if (fabs(a - cross_point) < e) return a;
            a = cross_point;
            F_a = f(cross_point) - g(cross_point);
        }
    }

    return 0;
}


double get_integral(double (*f)(double), double (*g)(double), const double a, const double b, int * iterations) {
    int n= 10;
    *iterations = 0;
    double sum_0 = 0;
    double sum_1 = 0;
    double F_0 = f(a) - g(a);
    double F_n = f(b) - g(b);
    double h = (b - a) / n;
    for (int i = 1; i < 10; ++i) {
        if (i % 2 == 0) {
            sum_0 += f(a + i*h) - g(a + i*h);
        } else {
            sum_1 += f(a + i*h) - g(a + i*h);
        }
    }

    double I_n;
    double I_2n = h/3 * (F_0 + 4 * sum_1 + 2 * sum_0 + F_n);
    do {
        (*iterations)++;
        I_n = I_2n;
        sum_0 += sum_1;
        n *= 2;
        h = (b - a) / n;
        sum_1 = 0;
        for (int i = 1; i < 2*n; i += 2) {
            sum_1 += f(a + i*n) - g(a + i*h);
        }
        I_2n = h/3 * (F_0 + 4 * sum_1 + 2 * sum_0 + F_n);
    } while (1/15 * fabs(I_n - I_2n));

    return I_2n;
}


int main() {
    int it = 0;
    printf("%lf ", get_root(exmp1, dexmp1, exmp2, dexmp2, -0.1, 0.1, 0.00001, &it));
    printf("%lf", get_root(exmp1, dexmp1, exmp2, dexmp2, 0.1, 10, 0.00001, &it));
    return 0;
}
