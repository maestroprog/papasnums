//
// Created by maestroprog on 04.01.2019.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "my_math.h"

volatile int my_math_error = 0;

double pair_nothing(double a, double b) {
    if (round(a) != a || round(b) != b || a > 9 || b > 9 || a < 0 || b < 0) {
        my_math_error = 1;
        return 0;
    }
    char buf1[3];
    char buf2[2];
    sprintf(buf1, "%d", (int) a);
    sprintf(buf2, "%d", (int) b);
    strcat(buf1, buf2);
    return strtol(buf1, NULL, 10);
}

double add(double a, double b) { return a + b; }

double subtract(double a, double b) { return a - b; }

double multiply(double a, double b) { return a * b; }

double divide(double a, double b) {
    if (b == 0) {
        my_math_error = 1;
        return 0;
    }
    return a / b;
}

double single_nothing(double a) { return a; }

double pow2(double a) { return pow(a, 2); }
