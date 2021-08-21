#ifndef H_MATRIX_TEST
#define H_MATRIX_TEST

#include "../includes/matrix.h"
#include "../includes/error.h"
#include <stdbool.h>

bool test_read_matrix_from_user(matrix_t *m);

bool test_create_matrix(matrix_t *m, size_t n, double d);

bool test_create_matrix_rect(matrix_t *m, size_t rows, size_t cols, double d);

bool test_free_matrix(matrix_t *m, bool print);

bool test_null_matrix(size_t n, matrix_t *m);

bool test_idty_matrix(size_t n, matrix_t *m);

bool test_dup_matrix(matrix_t *msrc, matrix_t *mdst);

bool test_mult_scalar(matrix_t *ms, double scalar); 

bool test_sum_matrix(matrix_t *m1, matrix_t *m2);

bool test_mult_matrix(matrix_t *m1, matrix_t *m2,  matrix_t *m3);

bool test_comp_matrix(matrix_t *m1, matrix_t *m2);

#endif
