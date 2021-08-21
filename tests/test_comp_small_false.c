#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix;
	
	/** COMP SMALL: FALSE */
	printf("Testing comp (small - false)...\n");
	assert (test_create_matrix(&first_input_matrix, 2, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2, 2) && "new matrix fill error");	
	printf("Comparing different small matrixes: \n");	
	assert (!test_comp_matrix(&first_input_matrix, &second_input_matrix) && "small matrix comp error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free smallmemory error");	

	
		
}
