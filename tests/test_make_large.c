#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {
	matrix_t first_input_matrix;
	

	/** CREATE LARGE MATRIX */
	printf("Testing create large...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 2) && "large matrix fill error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");

}
