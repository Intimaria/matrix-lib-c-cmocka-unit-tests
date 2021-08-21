#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix;
	
	/** SUM LARGE */
	printf("Testing sum in place (large)...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2000, 7) && "new matrix fill error");	
	assert (test_sum_matrix(&first_input_matrix, &second_input_matrix) && "large matrix sum error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");	
	

}
