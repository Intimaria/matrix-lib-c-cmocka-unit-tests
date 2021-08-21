#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix;
	

	/** DUP LARGE */
	printf("Testing dup large...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 2) && "small matrix fill error");
	assert (test_dup_matrix(&first_input_matrix, &second_input_matrix) && "large dup matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");

}
