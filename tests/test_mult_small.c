#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix, output_matrix;
	
	
	/** MULT SMALL */
	
	/** CAUTION: mult function calls "create and fill" function for out matrix, 
	* so do not send a fullly created and filled matrix to function. 
	* This will cause memory leaks as new sectors of the heap will be assigned and 
	* previously allocated blocks lost */	
	printf("Testing mult (small)...\n");
	assert (test_create_matrix(&first_input_matrix, 2, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2, 7) && "new matrix fill error");			
	printf("product of: \n");
	print_matrix(&first_input_matrix);
	printf("*\n");
	print_matrix(&second_input_matrix);
	assert (test_mult_matrix(&first_input_matrix, &second_input_matrix, &output_matrix) && "small matrix mult error");	
	printf("resulting matrix: \n");
	print_matrix(&output_matrix);	
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free small memory error");	
	assert(test_free_matrix(&output_matrix, false) && "free small memory error");	
		
}
