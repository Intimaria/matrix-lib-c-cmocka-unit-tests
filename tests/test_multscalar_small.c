#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix;
	/** MULT SCALAR SMALL */
	printf("Testing mult scalar in place small...\n");
	assert (test_create_matrix(&first_input_matrix, 2, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert (test_mult_scalar(&first_input_matrix, 5.5) && "small null matrix error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");

}
