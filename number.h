//
// Created by maestroprog on 08.01.2019.
//

#ifndef NUMBERS_NUMBER_H
#define NUMBERS_NUMBER_H

#include "op.h"

struct single_number {
    double *num_ptr;
    double calc_num;
    double *calc_history;
    op_e current_op;
    struct single_number *wrapped_number;
    unsigned short level;
};

struct couple_of_numbers {
    struct single_number *num1;
    struct single_number *num2;
//    enum pair_op_e current_op;
};

struct single_number *create_single_number(double *number, unsigned short level);

void delete_single_number(struct single_number *num);

struct couple_of_numbers *create_couple_of_numbers(struct single_number *num1, struct single_number *num2);

int calc_next_single_number(struct single_number *num_ptr);

char *wrap_op(struct single_number *num);

#endif //NUMBERS_NUMBER_H
