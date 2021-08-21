#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix;
	/** NULL SMALL */
	printf("Testing null zero sized...\n");
	assert (test_null_matrix(0, &first_input_matrix) && "small null matrix error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	
	printf("Testing null small...\n");
	assert (test_null_matrix(1, &first_input_matrix) && "small null matrix error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");

}
