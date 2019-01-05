//
// Created by maestroprog on 08.01.2019.
//

#include <math.h>
#include "op.h"
#include "my_math.h"

double negative(double a) {
    return -a;
}

double (*const single_ops[SINGLE_OPS_COUNT])(double a) = {
        NULL,
        single_nothing,
        negative,
        pow2,
        sqrt,
        sin,
        cos,
        tan,
};

double (*const pair_ops[4])(double a, double b) = {
        add,
        subtract,
        multiply,
        divide
};

const char *get_op_name(enum single_op_e op) {
    const char *single_op_map_str[SINGLE_OPS_COUNT] = {
            "",
            "",
            "-",
            "pow2",
            "sqrt",
            "sin",
            "cos",
            "tan",
    };

    return single_op_map_str[op];
}

const char *get_op(int op) {
    if (op == 0) {
        return "+";
    } else if (op == 1) {
        return "-";
    } else if (op == 2) {
        return "*";
    } else if (op == 3) {
        return "/";
    } else {
        return "";
    }
}
