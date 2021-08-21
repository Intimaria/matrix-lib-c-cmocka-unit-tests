#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix;
	/** MULT SCALAR LARGE */
	printf("Testing mult scalar in place large...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 2) && "small matrix fill error");
	assert (test_mult_scalar(&first_input_matrix, 5.5) && "large null matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	

}
