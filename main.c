#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "my_math.h"
#include "number.h"

int max_recursion_level = 1;

int extract_numbers(char *const *argv, int *numbers);

void each_couple_of_numbers(struct couple_of_numbers *nums1, struct couple_of_numbers *nums2);

int main(int argc, char **argv) {
    printf("Hello, World!\n");
    if (argc < 2) {
        fprintf(stderr, "Need to pass one required argument");
        return 1;
    }

    int numbers[4];
    int err;
    if ((err = extract_numbers(argv, numbers))) {
        printf("Error occured while numbers extracting %d\n", err);
        return err;
    }
    double double_numbers[4];
    for (int i = 0; i < 4; i++) {
        double_numbers[i] = numbers[i] * 1.0;
    }
    struct couple_of_numbers *nums1 = create_couple_of_numbers(
            create_single_number(&double_numbers[0]),
            create_single_number(&double_numbers[1])
    );
    struct couple_of_numbers *nums2 = create_couple_of_numbers(
            create_single_number(&double_numbers[2]),
            create_single_number(&double_numbers[3])
    );

    each_couple_of_numbers(nums1, nums2);

    delete_single_number(nums1->num1);
    delete_single_number(nums1->num2);
    delete_single_number(nums2->num1);
    delete_single_number(nums2->num2);
    free(nums1);
    free(nums2);

    printf("Done\n");

    return 0;
}

void each_couple_of_numbers(struct couple_of_numbers *nums1, struct couple_of_numbers *nums2) {
    int ops_size = sizeof(pair_ops) / sizeof(void *);

    unsigned long ic = 0;
    start:
    do {
        ic++;

        for (int i = 0; i < ops_size; i++) {
            double number_left = (*pair_ops[i])((*nums1->num1)->calc_num, (*nums1->num2)->calc_num);

            if (my_math_error) {
                my_math_error = 0; // reset error
                continue;
            }

            for (int j = 0; j < ops_size; j++) {
                double number_right = (*pair_ops[j])((*nums2->num1)->calc_num, (*nums2->num2)->calc_num);

                if (my_math_error) {
                    my_math_error = 0; // reset error
                    continue;
                }

                if (number_left == number_right) {
                    char *chr1 = wrap_op((*nums1->num1));
                    char *chr2 = wrap_op((*nums1->num2));
                    char *chr3 = wrap_op((*nums2->num1));
                    char *chr4 = wrap_op((*nums2->num2));

                    printf(
                            "%s%s%s==%s%s%s,%.2f==%.2f\n",
                            chr1,
                            get_op(i),
                            chr2,
                            chr3,
                            get_op(j),
                            chr4,
                            number_left,
                            number_right
                    );

                    free(chr1);
                    free(chr2);
                    free(chr3);
                    free(chr4);
                    return;
                } else {

                }
            }
        }
    } while (calc_next_single_number(nums1->num1));

    if (calc_next_single_number(nums1->num2)) {
        goto start;
    }

    if (calc_next_single_number(nums2->num1)) {
        goto start;
    }

    if (calc_next_single_number(nums2->num2)) {
        goto start;
    }

    printf("%lu\n", ic);
}

int extract_numbers(char *const *argv, int *numbers) {
    if (strlen(*argv) < 4) {
        return 3;
    }
    char *digits = argv[1];
    printf("%s\n", digits);
    for (int i = 0; i < 4; i++) {
        char cpy[2];
        strncpy(cpy, (digits + i), (size_t) 1);
        if (!isdigit(*cpy)) {
            printf("%s not is digit\n", cpy);
            return 2;
        }
        numbers[i] = (int) strtol(cpy, NULL, 10);
    }

    return 0;
}


//struct buffer_pointer {
//    size_t size;
//    void *ptr;
//};

/*void *custom_realloc(struct buffer_pointer *old_pointer, size_t size) {
    if (old_pointer == NULL) {
        size_t *mem = malloc(size);
        if (mem == 0) {
            printf("Cannot malloc memory");
            raise(SIGUSR1);
            return NULL;
        }

        struct buffer_pointer buffer_ptr = {size, mem};
        struct buffer_pointer *ptr = &buffer_ptr;
        return ptr;
    } else {
        size_t *oldmem = old_pointer->ptr;
        size_t *newmem = realloc(oldmem, size);
        if (newmem == 0) {
            printf("Cannot realloc memory");
            raise(SIGUSR1);
            return NULL;
        }

        struct buffer_pointer buffer_ptr = {size, newmem};
        struct buffer_pointer *ptr = &buffer_ptr;
        return ptr;
    }
}*/
