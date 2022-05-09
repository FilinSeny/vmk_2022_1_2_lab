#include <stdio.h>
#include <math.h>
#include <string.h>
const double Eps1 = 0.00001;
const double Eps2 = 0.001;

///f1 = 3 (0.5 / (x + 1) + 1)   f' = 1.5/(x+1)^2
///f2 = 2.5x − 9.5              f' = 2.5
///f3 = 5 / x                   f' = 5/x^2
extern  double f1(double);
extern double df1(double);
extern double f2(double);
extern double df2(double);
extern double f3(double);
extern double df3(double);


double exmp0(double x) {
	return 0;
}


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

double exmp3 (double x) {
    return x*x -5*x -  6;
}

double dexmp3 (double x) {
    return 2*x - 5;
}

double exmp4 (double x) {
    return exp(x*x - 3) - 10;
}

double dexmp4 (double x) {
    return exp(x*x - 3) * 2*x;
}

double get_root(double (*f)(double), double (*fd)(double), double (*g)(double), double (*gd)(double), double a, double b, const double e, int* iteratinon) {
    double F_a = f(a) - g(a);
    double F_b = f(b) - g(b);
	(*iteratinon) = 0;


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
            double f_ = fd(a);
            double g_ = gd(a);
            cross_point = a - F_a / (fd(a) - gd(a));
            if (fabs(a - cross_point) < e) return a;
            a = cross_point;
            F_a = f(cross_point) - g(cross_point);
        }
    }

    return 0;
}


double get_integral(double (*f)(double), const double a, const double b, double eps, int * iterations) {
    int n= 10;
    *iterations = 0;
    double sum_0 = 0;
    double sum_1 = 0;
    double F_0 = f(a);
    double F_n = f(b);
    double h = (b - a) / n;
    for (int i = 1; i < 10; ++i) {
        if (i % 2 == 0) {
            sum_0 += f(a + i*h);
        } else {
            sum_1 += f(a + i*h);
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
        for (int i = 1; i < n; i += 2) {
            sum_1 += f(a + i*h);
        }
        I_2n = h/3 * (F_0 + 4 * sum_1 + 2 * sum_0 + F_n);
    } while (1/15 * fabs(I_n - I_2n) > eps);

    return I_2n;
}


int main(int argc, char **argv) {
	int i = 1;
	int flag = 0;
	if (argc == 1) {
		flag = 1;
	}
	while (i < argc || flag) {
		if (!flag && !strcmp(argv[i+0], "-help")) { 
			printf(" -help \n -show_exmp [num_exmp] \n -show_cross_points \n -show_iterations \n -get_integral \n");
			++i;
		}
		else if (!flag && !strcmp(argv[i+0], "-show_exmp")) {
			if (!strcmp(argv[i+1], "1")) {
				int it = 0;
				printf("f1: x^2 \n f2: x \n ");
				double p1 = get_root(exmp1, dexmp1, exmp2, dexmp2, -0.1, 0.1, Eps1, &it);
				double p2 = get_root(exmp1, dexmp1, exmp2, dexmp2, 0.1, 10, Eps1, &it);  
				printf("roots : %lf %lf \n", p1, p2);
				printf("I: %lf", get_integral(exmp1, p1, p2, Eps2, &it) - get_integral(exmp2, p1, p2, Eps2, &it));
			} else if (!flag && !strcmp(argv[i+1], "2")) {
				int it = 0;
				printf("f1 : x^2 - 5x - 6 \n f2:0  \n");
				double p1 = get_root(exmp3, dexmp3, exmp0, exmp0, -1000, 0, Eps1, &it);
				double p2 = get_root(exmp3, dexmp3, exmp0, exmp0, 0, 1000, Eps1, &it);
				printf("roots : %lf %lf \n", p1, p2);
				printf("I: %lf", get_integral(exmp3, p1, p2, Eps2, &it) - get_integral(exmp0, p1, p2, Eps2, &it)); 
			} else if (!flag && !strcmp(argv[i+1], "3")) {
				int it = 0;
				printf("f1 : e^(x^2 - 3) - 10");
				double p1 = get_root(exmp4, dexmp4, exmp0, exmp0, -5, 0, Eps1, &it);
				double p2 = get_root(exmp4, dexmp4, exmp0, exmp0, 0, 5, Eps1, &it);
				printf("roots : %lf, %lf \n", p1, p2);
				printf("I: %lf \n",fabs(get_integral(exmp4, p1, p2, Eps2, &it)));
			}
			i += 2;
		}
		else {
			int it1, it2, it3;
			double p1 = get_root(f1, df1, f2, df2, 0.1, 100, Eps1, &it1);
			double p2 = get_root(f2, df2, f3, df3, 0.1, 100, Eps1, &it2);
			double p3 = get_root(f1, df1, f3, df3, 0.1, 100, Eps1, &it3);
			if (!flag && !strcmp(argv[i+0], "-show_cross_points")) { 
				printf("f1&f2: %lf f2&f3: %lf f1&f3: %lf", p1, p2, p3);
				++i;
			} else if (!flag && !strcmp(argv[i+0], "-show_iterations")) {
				printf("f1&f2:%d, f2&f3 %d, f3&f1 %d", it1, it2, it3);
				++i; 
			} else if (flag || !strcmp(argv[i+0], "-get_integral")) {
				int it = 0;
				double res = get_integral(f1, p3, p2, Eps2, &it) - get_integral(f3, p3, p2, Eps2, &it);
				res += get_integral(f1, p2, p1, Eps2, &it) - get_integral(f2, p2, p1, Eps2, &it);
				printf("I: %lf", res);
				++i;
				flag = 0;
			}
		} 
	}
	 return 0;
}
