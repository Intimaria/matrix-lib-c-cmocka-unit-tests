#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix, second_input_matrix;
	

	/** DUP ZERO DIMENSIONS*/
	
	printf("Testing dup zero sized...\n");
	assert (test_create_matrix_rect(&first_input_matrix, 0, 0, 1) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert (test_dup_matrix(&first_input_matrix, &second_input_matrix) && "large idty matrix error");
	print_matrix(&second_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free small memory error");
	
	/** DUP SMALL MATRIX*/
	
	printf("Testing dup small...\n");
	assert (test_create_matrix_rect(&first_input_matrix, 2, 1, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert (test_dup_matrix(&first_input_matrix, &second_input_matrix) && "large idty matrix error");
	print_matrix(&second_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free small memory error");

}
