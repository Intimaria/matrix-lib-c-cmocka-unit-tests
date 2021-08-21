#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {
	clock_t start, end;
	matrix_t first_input_matrix, second_input_matrix, output_matrix;
	
	/** CAUTION: mult function calls "create and fill" function for out matrix, 
	* so do not send a fullly created and filled matrix to function. 
	* This will cause memory leaks as new sectors of the heap will be assigned and 
	* previously allocated blocks lost */	
	
	/** MULT LARGE: warning, this is O(n^3) so gets verrry slow at large N*/
	printf("Testing mult (large)...\n");
	assert (test_create_matrix(&first_input_matrix, 500, 5) && "large matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 500, 7) && "large matrix fill error");	
	printf("Line: %d. Starting clock, please wait for execution to finish... \n", __LINE__);
	start = clock();
	assert (test_mult_matrix(&first_input_matrix, &second_input_matrix, &output_matrix) && "large matrix mult error");	
	end = clock();
	double time_taken = (end - start) / (CLOCKS_PER_SEC); 
	printf("Execution time for mult in seconds: %f \n\n", time_taken);
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");	
	assert(test_free_matrix(&output_matrix, false) && "free large memory error");		
	//printf("Line: %d \n", __LINE__);
	
		
}
