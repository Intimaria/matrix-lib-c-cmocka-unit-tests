#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix, output_matrix;
	
	/** CAUTION: mult function calls "create and fill" function for out matrix, 
	* so do not send a fullly created and filled matrix to function. 
	* This will cause memory leaks as new sectors of the heap will be assigned and 
	* previously allocated blocks lost */	
	
	/** MULT WRONG DIMENSIONS */
	printf("Testing mult (wrong dimensions)\n");
	assert (test_create_matrix(&first_input_matrix, 4, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 3, 7) && "new matrix fill error");	
	assert (!test_mult_matrix(&first_input_matrix, &second_input_matrix, &second_input_matrix) && "matrix mult error");			
	assert(test_free_matrix(&first_input_matrix, false) && "free memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free memory error");	
	assert(test_free_matrix(&output_matrix, false) && "free memory error");	
	
		
}
