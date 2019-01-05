//
// Created by maestroprog on 08.01.2019.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "number.h"

extern int max_recursion_level;

struct single_number **create_single_number(double *number) {
    struct single_number **num_ptr = malloc(sizeof(void *) + sizeof(struct single_number));
    *num_ptr = num_ptr + 1;
    (*num_ptr)->num_ptr = number;
    (*num_ptr)->calc_num = 0;
    (*num_ptr)->calc_history = malloc(sizeof(double) * SINGLE_OPS_COUNT);
    (*num_ptr)->current_op = SINGLE_BEGIN;
    (*num_ptr)->wrapped_number = NULL;
    (*num_ptr)->level = 0;

    memset((*num_ptr)->calc_history, 0, sizeof(double) * SINGLE_OPS_COUNT);

    calc_next_single_number(num_ptr);

    return num_ptr;
}

void delete_single_number(struct single_number **num) {
    if ((*num)->wrapped_number != NULL) {
        delete_single_number(&(*num)->wrapped_number);
    }

    free((*num)->calc_history);
    free(*num);
}

struct couple_of_numbers *create_couple_of_numbers(struct single_number **num1, struct single_number **num2) {
    struct couple_of_numbers *num = malloc(sizeof(struct couple_of_numbers));
    num->num1 = num1;
    num->num2 = num2;
//    num->current_op = PAIR_NOTHING;

    return num;
}

int calc_next_single_number(struct single_number **num_ptr) {
    (*num_ptr)->current_op++;

    if ((*num_ptr)->current_op >= SINGLE_END) {
        (*num_ptr)->current_op = SINGLE_NOTHING + 2;
        if ((*num_ptr)->wrapped_number == NULL) {
            if ((*num_ptr)->level >= max_recursion_level) {
                return 0;
            } else {
                struct single_number **new_num = create_single_number((*num_ptr)->num_ptr);
                (*new_num)->level = (unsigned short) ((*num_ptr)->level + 1);
                (*num_ptr)->wrapped_number = *new_num;
                num_ptr = new_num;
                printf("create level %d\n", (*new_num)->level);
            }
        } else if (!calc_next_single_number(&(*num_ptr)->wrapped_number)) {
            return 0;
        }
    }

    if (*((*num_ptr)->calc_history + (*num_ptr)->current_op) == 0) {
        (*num_ptr)->calc_num = (*single_ops[(*num_ptr)->current_op])(*(*num_ptr)->num_ptr);
        if (!isnan((*num_ptr)->calc_num)) {
            (*num_ptr)->calc_num = ((int) ((*num_ptr)->calc_num * 100)) / 100.0;
        }
        *((*num_ptr)->calc_history + (*num_ptr)->current_op) = (*num_ptr)->calc_num;
    } else {
        (*num_ptr)->calc_num = *((*num_ptr)->calc_history + (*num_ptr)->current_op);
    }

    return 1;
}

char *wrap_op(struct single_number *num) {
    const char *op_name = get_op_name(num->current_op);
    char *buf = malloc(sizeof(char) * 32);
    memset(buf, 0, sizeof(char) * 32);

    char *number;
    if (num->wrapped_number != NULL) {
        number = wrap_op(num->wrapped_number);
    } else {
        number = malloc(64);
        sprintf(number, "%d", (uint) round(trunc(*num->num_ptr)));
    }

    if (strcmp(op_name, "") == 0) {
        sprintf(buf, "%s", number);
    } else {
        sprintf(buf, "%s(%s)", op_name, number);
    }

    free(number);

    return buf;
}
