#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


int main() {

	matrix_t first_input_matrix;
		/** IDTY LARGE */
	printf("Testing idty large...\n");
	assert (test_idty_matrix(2000, &first_input_matrix) && "large idty matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");

}
