#include "matrix_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>


int main() {
  clock_t start, end;
	matrix_t first_input_matrix, second_input_matrix, output_matrix;
	/** unary operations */

	/** CREATE SMALL*/
	printf("Testing create zero sized...\n");
	assert (test_create_matrix(&first_input_matrix, 0, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free memory error");
	
	printf("Testing create small...\n");
	assert (test_create_matrix(&first_input_matrix, 1, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free memory error");
	
	/** CREATE LARGE */
	printf("Testing create large...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 2) && "large matrix fill error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	
	/** NULL & IDTY UNARY OPERATIONS CREATE & ALLOCATE FIRST INPUT **/
	/** NULL SMALL */
	printf("Testing null zero sized...\n");
	assert (test_null_matrix(0, &first_input_matrix) && "small null matrix error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	
	printf("Testing null small...\n");
	assert (test_null_matrix(1, &first_input_matrix) && "small null matrix error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	
	/** NULL LARGE */
	printf("Testing null large...\n");
	assert (test_null_matrix(2000, &first_input_matrix) && "large null matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");

	/** IDTY SMALL */
	printf("Testing idty zero sized...\n");
	assert (test_idty_matrix(0, &first_input_matrix) && "small idty matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	
	printf("Testing idty small...\n");
	assert (test_idty_matrix(2, &first_input_matrix) && "small idty matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");

	/** IDTY LARGE */
	printf("Testing idty large...\n");
	assert (test_idty_matrix(2000, &first_input_matrix) && "large idty matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	
	/** DUP SMALL */
	
	printf("Testing dup zero sized...\n");
	assert (test_create_matrix_rect(&first_input_matrix, 0, 0, 1) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert (test_dup_matrix(&first_input_matrix, &second_input_matrix) && "large idty matrix error");
	print_matrix(&second_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free small memory error");
	
	printf("Testing dup small...\n");
	assert (test_create_matrix_rect(&first_input_matrix, 2, 1, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert (test_dup_matrix(&first_input_matrix, &second_input_matrix) && "large idty matrix error");
	print_matrix(&second_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free small memory error");
	
	/** DUP LARGE */
	printf("Testing dup large...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 2) && "small matrix fill error");
	assert (test_dup_matrix(&first_input_matrix, &second_input_matrix) && "large dup matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");
	
	/** MULT SCALAR SMALL */
	printf("Testing mult scalar in place small...\n");
	assert (test_create_matrix(&first_input_matrix, 2, 2) && "small matrix fill error");
	print_matrix(&first_input_matrix);
	assert (test_mult_scalar(&first_input_matrix, 5.5) && "small null matrix error");
	print_matrix(&first_input_matrix);
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	
	/** MULT SCALAR LARGE */
	printf("Testing mult scalar in place large...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 2) && "small matrix fill error");
	assert (test_mult_scalar(&first_input_matrix, 5.5) && "large null matrix error");
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	
	/** MULT SCALAR (not in place) */ 
	
	/** binary operations */
	
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
	
	/** SUM LARGE */
	printf("Testing sum in place (large)...\n");
	assert (test_create_matrix(&first_input_matrix, 2000, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2000, 7) && "new matrix fill error");	
	assert (test_sum_matrix(&first_input_matrix, &second_input_matrix) && "large matrix sum error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");	
	
	/** SUM (not in place) */
	
	/** SUM WRONG DIMENSIONS */
	printf("Testing sum in place (wrong dimensions)...\n");
	assert (test_create_matrix(&first_input_matrix, 2, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 4, 7) && "new matrix fill error");	
	assert (!test_sum_matrix(&first_input_matrix, &second_input_matrix) && "matrix sum error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free memory error");	
	
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
	
	/** MULT WRONG DIMENSIONS */
	printf("Testing mult (wrong dimensions)\n");
	assert (test_create_matrix(&first_input_matrix, 4, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 3, 7) && "new matrix fill error");	
	assert (!test_mult_matrix(&first_input_matrix, &second_input_matrix, &second_input_matrix) && "matrix mult error");			
	assert(test_free_matrix(&first_input_matrix, false) && "free memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free memory error");	
	assert(test_free_matrix(&output_matrix, false) && "free memory error");	
	
	/** COMP SMALL: TRUE */
	printf("Testing comp (small - true)... \n");
	assert (test_create_matrix(&first_input_matrix, 2, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2, 5) && "new matrix fill error");
	printf("Comparing equal small matrixes: \n");	
	assert (test_comp_matrix(&first_input_matrix, &second_input_matrix) && "small matrix comp error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free small memory error");	
	
	/** COMP SMALL: FALSE */
	printf("Testing comp (small - false)...\n");
	assert (test_create_matrix(&first_input_matrix, 2, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2, 2) && "new matrix fill error");	
	printf("Comparing different small matrixes: \n");	
	assert (!test_comp_matrix(&first_input_matrix, &second_input_matrix) && "small matrix comp error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free small memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free smallmemory error");	
	/*try comp different ways - null matrix, try by value, try zero values */
	
	/** COMP LARGE: TRUE */
	printf("Testing comp (large - true)... \n");
	assert (test_create_matrix(&first_input_matrix, 2000, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2000, 5) && "new matrix fill error");
	printf("Comparing equal large matrixes: \n");		
	assert (test_comp_matrix(&first_input_matrix, &second_input_matrix) && "large matrix comp error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");	
	
	/** COMP LARGE: FALSE */
	printf("Testing comp (large - false)... \n");
	assert (test_create_matrix(&first_input_matrix, 2000, 5) && "new matrix fill error");	
	assert (test_create_matrix(&second_input_matrix, 2000, 1) && "new matrix fill error");	
	printf("Comparing different large matrixes: \n");
	assert (!test_comp_matrix(&first_input_matrix, &second_input_matrix) && "large matrix comp error");	
	
	assert(test_free_matrix(&first_input_matrix, false) && "free large memory error");
	assert(test_free_matrix(&second_input_matrix, false) && "free large memory error");	
	
}
