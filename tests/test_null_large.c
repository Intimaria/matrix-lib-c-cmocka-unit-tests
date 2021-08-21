#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix;
	/** NULL LARGE */
	printf("Testing null large...\n");
	assert (test_null_matrix(2000, &first_input_matrix) && "large null matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");

}
