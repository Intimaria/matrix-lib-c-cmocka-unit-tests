#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix;
	/** IDTY SMALL */
	printf("Testing idty zero sized...\n");
	assert (test_idty_matrix(0, &first_input_matrix) && "small idty matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	
	printf("Testing idty small...\n");
	assert (test_idty_matrix(2, &first_input_matrix) && "small idty matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");

}
