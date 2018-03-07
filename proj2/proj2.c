/*
 *	VUT FIT
 *	IZP 2017/2018
 *	Projekt 2 - Iterační výpočty
 *	Autor: Adam Abrahám
 *	Datum: 19.11.2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 1.0e-10
#define HEIGHT 1.5
#define MAX_HEIGHT 100
#define MAX_ITER 14
#define MIN_RAD 0
#define MAX_RAD 1.4


double taylor_tan(double x, unsigned int n);

double cfrac_tan(double x, unsigned int n);

void printTan(double x, int a, int length);

double mAbs(double x);

double lengthTan(double c, double alpha);

double heightTan(double c, double beta, double length);

void tanCheck(double a, double n, double m, char **end);

void cmCheck(double x, double a, double b);

void endCheck(char **end);

int main(int argc, char *argv[]) {
    char *end;
    if (argc == 1) {
        printf("ERROR: No argument!\nType '--help' for details.\n");
    } else if (strcmp(argv[1], "--tan") == 0) {
        if (argc == 5) {
            double alpha = strtod(argv[2], &end);//atof(argv[2]);
            int N = atof(argv[3]);
            int length = atof(argv[4]) - N;
            tanCheck(atof(argv[2]), atof(argv[3]), atof(argv[4]), &end);
            printTan(alpha, N, length);
        } else {
            printf("ERROR: Invalid argument!\nType '--help' for details.\n");
        }
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("--tan A N M\nPorovna presnosti vypoctov tangens uhla A(v radianoch).\nArgumenty N a M udavaju, v ktorych iteraciach iteracneho vypoctu ma porovnavanie prebiehat. 0 < N <= M < 14\n\n[-c X] -m A [B]\nProgram vypocita a vypise vzdialenost meraneho objektu. 0 < A <= 1.4 < π/2.\nProgram vypocita a vypise aj vysku meraneho objektu. 0 < B <= 1.4 < π/2\nVyska c je dana argumentom X (0 < X <= 100). Argument je volitelny - implicitna vyska je 1.5 metrov.\n");
    } else if (strcmp(argv[1], "-m") == 0) {
        if (argc == 3) {
            double alpha = strtod(argv[2], &end);
            endCheck(&end);
            cmCheck(HEIGHT, alpha, 1); //1 lebo tam neni nic
            printf("%.10e\n", lengthTan(HEIGHT, alpha));
        } else if (argc == 4) {
            double alpha = strtod(argv[2], &end);
            endCheck(&end);
            double beta = strtod(argv[3], &end);
            endCheck(&end);
            cmCheck(HEIGHT, alpha, beta);
            double length = lengthTan(HEIGHT, alpha);
            double height = heightTan(HEIGHT, beta, length);
            printf("%.10e\n%.10e\n", length, height);
        } else {
            printf("ERROR: Invalid argument!\nType '--help' for details.\n");
        }
    } else if (strcmp(argv[1], "-c") == 0 && argc >= 4) {
        if (strcmp(argv[3], "-m") == 0) {
            double newHeight = 0.;
            double alpha = 0.;
            double beta = 0.;
            if (argc == 5) {
                newHeight = strtod(argv[2], &end);
                endCheck(&end);
                alpha = strtod(argv[4], &end);
                endCheck(&end);
                cmCheck(newHeight, alpha, 1);
                printf("%.10e\n", lengthTan(newHeight, alpha));
            } else if (argc == 6) {
                newHeight = strtod(argv[2], &end);
                endCheck(&end);
                alpha = strtod(argv[4], &end);
                endCheck(&end);
                beta = strtod(argv[5], &end);
                endCheck(&end);
                cmCheck(newHeight, alpha, beta);
                double length = lengthTan(newHeight, alpha);
                double height = heightTan(newHeight, beta, length);
                printf("%.10e\n%.10e\n", length, height);
            }
        } else {
            printf("ERROR: Invalid argument!\nType '--help' for details.\n");
        }
    } else {
        printf("ERROR: Invalid argument!\nType '--help' for details.\n");
    }

    return 0;
}

void printTan(double x, int a, int length) {
    double taylor;
    double cfrac;
    double tang = tan(x);
    for (int i = a; i <= a + length; i++) {
        taylor = taylor_tan(x, i);
        cfrac = cfrac_tan(x, i);
        printf("%d %e %e %e %e %e\n",
               i, tang, taylor, mAbs(tang - taylor), cfrac, mAbs(tang - cfrac));
    }
}

double lengthTan(double c, double alpha) {
    double old = 0.;
    double new = 0.;
    int i = 1;
    do {
        old = new;
        new = cfrac_tan(alpha, i);
        i++;
    } while (mAbs(new - old) >= EPS);
    return c / new;
}

double heightTan(double c, double beta, double length) {
    double old = 0.;
    double new = 0.;
    int i = 1;
    do {
        old = new;
        new = cfrac_tan(beta, i);
        i++;
    } while (mAbs(new - old) >= EPS);
    return new * length + c;
}

void tanCheck(double a, double n, double m, char **end) {
    if (n <= MIN_RAD || n > m || m >= MAX_ITER || a <= MIN_RAD || a > MAX_RAD || **end != '\0') {
        printf("ERROR: Invalid argument!\nType '--help' for details.\n");
        exit(1);
    }
}

void cmCheck(double x, double a, double b) {
    if (x <= MIN_RAD || x > MAX_HEIGHT || a <= MIN_RAD || a > MAX_RAD || b <= MIN_RAD || b > MAX_RAD) {
        printf("ERROR: Invalid argument!\nType '--help' for details.\n");
        exit(1);
    }
}

void endCheck(char **end) {
    if (**end != '\0') {
        printf("ERROR: Invalid argument!\nType '--help' for details.\n");
        exit(1);
    }
}

double mAbs(double x) {
    if (x < 0) {
        return x * (-1);
    } else {
        return x;
    }
}

double taylor_tan(double x, unsigned int n) {
    double citatel[] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862,
                        58870668456604};
    double menovatel[] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625,
                          49308808782358125, 3698160658676859375};
    double result = 0.;
    double oldX = x;

    for (int i = 0; i < (int) n; i++) {
        if (i >= 1) {
            for (int g = 0; g < 2; g++) {
                x = x * oldX;
            }
        }
        result += (citatel[i] * x) / menovatel[i];
    }
    return result;
}

double cfrac_tan(double x, unsigned int n) {
    double result = 0.;
    double a;
    double oldX = x;
    for (int k = n; k > 0; k--) {
        a = 2 * k - 1;
        x *= x;
        if (k != 1) {
            result = x / (a - result);
            x = oldX;
        } else {
            result = oldX / (a - result);
        }
    }
    return result;
}
