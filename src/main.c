#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../includes/params.h"
#include "../includes/error.h"
#include "../includes/help.h"
#include "../includes/matrix.h"



FILE *fout, *fp1, *fp2;
	
int main(int argc, char *argv[])
{
    double scalar;
    char *file_in1, *file_in2, *file_out;
    matrix_t first_input_matrix, second_input_matrix;
    matrix_t * output_matrix = NULL;
    bool help = false;
    bool args_complete = true; 
    int flags[] = {false,  /** flags[IN1] */
                   false,  /** flags[IN2] */
                   false,  /** flags[OUT] */
                   false,  /** flags[SC]  */
                   false}; /** flags[OP]  */

    /** -------------------------------------------------------------
     * parses & allocates memory for file names  from command line 
     * --------------------------------------------------------------*/

    error_t error = parse (argc, argv, flags, &scalar, &file_in1, &file_in2, &file_out, &help, &args_complete); 

    /** input matrices -> reads from files & allocates memory **/
    if (flags[IN1]) {
        error = read_and_allocate(fp1, file_in1, &first_input_matrix);
        if (first_input_matrix.data) print_matrix(&first_input_matrix);
		if (flags[IN2]) {
			error = read_and_allocate(fp2, file_in2, &second_input_matrix);
            if (second_input_matrix.data) print_matrix(&second_input_matrix);
		}
	}


    /** -------------------------------------------------------------
     * if help is called, prints help and exits normally, else calls 
     * matrix operations normally if all arguments are present
     * --------------------------------------------------------------*/
    if (help) {
        print_help();
        return E_OK;
    } 
    else if ((error == E_OK) && (args_complete)) {	
	/** --------------------------------------------------------------
	 * calls functions - also frees memory for all parsed file names 
	 * ---------------------------------------------------------------*/
         output_matrix = (matrix_t*)malloc(sizeof(matrix_t));
         error = sort_and_call(argc, argv, flags, scalar, &first_input_matrix, &second_input_matrix, output_matrix);

		 if (error == E_OK) {
			error = write_matrix_to_file(fout, file_out, output_matrix);
            free(output_matrix);
            output_matrix = NULL;
            } 
		
    }
    
    /** filenames & matrices -> frees all allocated memory **/
	if (flags[IN1]) {
        free_matrix(&first_input_matrix);
    } 
    if (flags[IN2]) {
        free_matrix(&second_input_matrix);
    } 

    /** --------------------------------------------------------------
     * provides helpful feedback to the user regarding any errors 
     * ---------------------------------------------------------------*/
    error_help(stderr, error);
    
    return error;
}

