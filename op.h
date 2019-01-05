//
// Created by maestroprog on 08.01.2019.
//

#ifndef NUMBERS_OP_H
#define NUMBERS_OP_H

typedef enum single_op_e {
    SINGLE_BEGIN,
    SINGLE_NOTHING,
    SINGLE_NEGATIVE,
    POW2,
    SQRT,
    SIN,
    COS,
    TAN,
    SINGLE_END
} op_e;

enum pair_op_e {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

#define SINGLE_OPS_COUNT 8

double (*const single_ops[SINGLE_OPS_COUNT])(double a);

double (*const pair_ops[4])(double a, double b);

const char *get_op_name(enum single_op_e op);

const char *get_op(int op);

#endif //NUMBERS_OP_H
