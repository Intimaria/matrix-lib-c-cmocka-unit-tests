#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix;
	
	/** SUM SMALL */
	printf("Testing sum in place (small)...\n");
	assert (test_create_matrix(&first_input_matrix, 2, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2, 7) && "new matrix fill error");	
	printf("sum of: \n");
	print_matrix(&first_input_matrix);
	printf("+\n");
	print_matrix(&second_input_matrix);
	assert (test_sum_matrix(&first_input_matrix, &second_input_matrix) && "small matrix sum error");	
	printf("resulting matrix: \n");
	print_matrix(&second_input_matrix);

	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free small memory error");	
	

}
