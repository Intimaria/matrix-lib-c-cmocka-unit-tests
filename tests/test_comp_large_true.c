#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix;
	
	/** COMP LARGE: TRUE */
	printf("Testing comp (large - true)... \n");
	assert (test_create_matrix(&first_input_matrix, 2000, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2000, 5) && "new matrix fill error");
	printf("Comparing equal large matrixes: \n");		
	assert (test_comp_matrix(&first_input_matrix, &second_input_matrix) && "large matrix comp error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");	

	
		
}
