#include "../includes/matrix.h"
#include "../includes/error.h"
#include "matrix_test.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

error_t e;

bool test_read_matrix_from_user(matrix_t *m){
	if ((e = read_matrix_from_user(m)) == E_OK){
		return true;
	}
	error_help(stderr, e);
	return false;
	
	}
bool test_create_matrix(matrix_t *m, size_t n, double d){
	if ((e = create_matrix_and_fill(m, m1, n, n, d)) == E_OK){
	return true;
	}
	error_help(stderr, e);
	return false;
}

bool test_create_matrix_rect(matrix_t *m, size_t rows, size_t columns, double d){
	if ((e = create_matrix_and_fill(m, m1, rows, columns, d)) == E_OK){
	return true;
	}
	error_help(stderr, e);
	return false;
}

bool test_free_matrix(matrix_t *m, bool print){
	if (print){
	printf("before FREE: rows: %d columns: %d fmt: %s pointer: %p \n", m->rows, m->columns, m->fmt == 0 ? "m1" : "m2", &m->data);
	printf("If data exists at array: %s\n", m->data ? "true" : "false");
	}
	(free_matrix(m));
	if (print) {
	printf("after FREE: rows: %d columns: %d fmt: %s pointer: %p \n", m->rows, m->columns, m->fmt == 0 ? "m1" : "m2", &m->data);
	printf("If data exists at array: %s\n", m->data ? "true" : "false");
	}
	if (!m->data){
	return true;
	} 
	return false;
}


bool test_null_matrix(size_t n, matrix_t *m){
	if ((e = null_matrix_rect(n, n, m1, m)) == E_OK){
	return true;
	}
	error_help(stderr, e);
	return false;
}

bool test_idty_matrix(size_t n, matrix_t *m){
	if ((e = idty_matrix (m, m1, n)) == E_OK){
	return true;
	}
	error_help(stderr, e);
	return false;
}



bool test_dup_matrix(matrix_t *msrc, matrix_t *mdst){
	if ((e = dup_matrix(msrc, mdst)) == E_OK){
		return true;
	} 
	error_help(stderr, e);
	return false;
}

bool test_mult_scalar(matrix_t *ms, double scalar){
		if ((e = multiply_scalar_inplace(ms, scalar)) == E_OK){
		return true;
	} 
	error_help(stderr, e);
	return false;
}

bool test_sum_matrix(matrix_t *m1, matrix_t *m2){
	if ((e = sum_inplace(m1, m2)) == E_OK){
		return true;
	} else {
		error_help(stderr, e);
		return false;
	}
}

bool test_mult_matrix(matrix_t *m1, matrix_t *m2, matrix_t *m3){
	if ((e = multiply(m1, m2, m3)) == E_OK){
		return true;
	} 
	error_help(stderr, e);
	return false;

}

bool test_comp_matrix(matrix_t *m1, matrix_t *m2){
	if (cmp_matrix(m1, m2) == 1){
		printf("Matrixes are equal. \n");
		return true;
	} else {
		printf("Matrixes are different. \n");
		return false;
	}
}

