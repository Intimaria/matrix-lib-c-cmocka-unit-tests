#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {
	matrix_t first_input_matrix;
	
/** CREATE SMALL MATRIX*/
	printf("Testing create zero sized...\n");
	assert (test_create_matrix(&first_input_matrix, 0, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free memory error");
	
	printf("Testing create small...\n");
	assert (test_create_matrix(&first_input_matrix, 1, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free memory error");

}
