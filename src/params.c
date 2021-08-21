#include <stdbool.h>

#include "../includes/params.h"





/** --------------------------------------------------------------------
 * parses arguments from main, validates files & calls to read_mat, 
 * sets flags for in/out files and operations ( calls set_ops_and_flags) 
 * ---------------------------------------------------------------------*/
error_t parse (int argc, char *argv[], int flags[], double * scalar, char **file_in1,char **file_in2, char **file_out, bool *help, bool *args_complete)
{
    size_t i;
    

    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-1", 2) == 0 || (strncmp(argv[i], "--in1", 5) == 0)) {
            if ((argv[i + 1] == NULL) || (strncmp(argv[i], "-", 1))){
                args_complete = false;
                return -E_INPUT_ERROR;
            } else {
                FILE * fp1 = fopen(argv[i + 1], "r");
                if (fp1 == NULL)
                {                
                    fprintf(stderr, "Error in opening file 1. \n");
                    return -E_FILE_ERROR;                                          
                }
                else {
                    *file_in1 =  argv[i + 1];
                    flags[IN1] = true;
                    fclose(fp1);
                }
            }
        }
        /** Need to check for all files*/
        if (strncmp(argv[i], "-2", 2) == 0 || (strncmp(argv[i], "--in2", 5) == 0)) {
            if ((argv[i + 1] == NULL) || (strncmp(argv[i], "-", 1))){
                args_complete = false;
                fprintf(stderr, "No filename defined. \n");
                return -E_INPUT_ERROR;
            } else {
                FILE * fp2 = fopen(argv[i + 1], "r");
                if (fp2 == NULL)
                {                
                    fprintf(stderr, "Error in opening file 2. \n");
                    return -E_FILE_ERROR;                                          
                }
                else {
                    *file_in2 =  argv[i + 1];
                    flags[IN2] = true;
                    fclose(fp2);
                }
            }
        }
        /** Need to check for all files */
        if (strncmp(argv[i], "-o", 2) == 0 || (strncmp(argv[i], "--out", 5) == 0)) {
            if ((argv[i + 1] == NULL) || (strncmp(argv[i], "-", 1))) {
                args_complete = false;
                fprintf(stderr, "No filename defined. \n");
                return -E_INPUT_ERROR;
            } else {
                FILE * fpo = fopen(argv[i + 1], "r");
                if (fpo == NULL)
                {                
                    fprintf(stderr, "Error in opening file out. \n");
                    return -E_FILE_ERROR;
                } else {
                    *file_out = argv[i + 1];
                    flags[OUT] = true;
                    fclose(fpo);
                }
            }
        }
        /** Need to check for all files*/
        if (strncmp(argv[i], "-s", 2) == 0 || (strncmp(argv[i], "--scalar", 8) == 0)) {
            if (argv[i + 1] == NULL) {
                args_complete = false;
                fprintf(stderr, "No scalar value defined. \n");
                return -E_INPUT_ERROR;
            } else {
                char *fin_cadena;
                * scalar = strtod(argv[++i], &fin_cadena);
                /** error checking */
                if (*fin_cadena != '\0') {
                    fprintf(stderr, "couldnt read the scalar value \n");
                    return -E_INPUT_ERROR;
                }
                flags[SC] = true;
                flags[OP] = MULT_S;
            }
        }
        /**   saves operation in flags[OP] */
        if (strncmp(argv[i], "-p", 2) == 0 || (strncmp(argv[i], "--op", 4) == 0)) {
            if (argv[i + 1] == NULL) {
                args_complete = false;
                fprintf(stderr, "No operation defined. \n");
                return -E_INPUT_ERROR;
            } else {
                char *op_type = argv[++i];
                if (flags[OP] != MULT_S) {
                    set_ops_and_flags(op_type, flags);
                }
                if (flags[OP] == NONE) {
                    fprintf(stderr, "No operation defined. \n");
                    return -E_INPUT_ERROR;
                }
            }
        }
        /** if --help is typed, exit program normally with help message.*/
        if (strncmp(argv[i], "--help", 6) == 0) {
            *help = true;
            args_complete = false;
            return E_OK;
        }
    } 	/** end of argc loops **/
   
    /** checks that basic necessary inputs exist */
    if ((flags[IN1] == false) || (flags[OP] == false) || (flags[OUT] == false)) {
		    args_complete = false;
            return -E_INPUT_ERROR;
    }
    /** checks the right number of input matrixes exist for binary operations */
    if ((flags[OP] == CMP) || (flags[OP] == SUM) || (flags[OP] == MULT)) {
        if ((flags[IN1] == false) || (flags[IN2] == false)) {
            args_complete = false;
            return -E_INPUT_ERROR;
        }
    }
    return E_OK;
}


/** -----------------------------------------------------------------------------
 * Expects parsed args & will allocate (&free) matrices, and make operation calls 
 * -----------------------------------------------------------------------------*/
error_t sort_and_call(int argc, char *argv[], int flags[], double scalar, matrix_t * first_input_matrix, matrix_t * second_input_matrix, matrix_t * output_matrix)
{
    error_t error = E_OK;

    /** this calls matrix functions */
    switch (flags[OP]) {
    case DUP: /** duplicate **/
        if (flags[IN1] && flags[OUT] && (flags[OP] == DUP)) {
            error = dup_matrix(first_input_matrix, output_matrix);
        }
        break;
    case IDTY: /** identity **/
        if (flags[IN1] && flags[OUT] && (flags[OP] == IDTY)) {
            error = idty_matrix(output_matrix, first_input_matrix->fmt, get_cols(first_input_matrix));
        }
        break;
    case NULL_M: /** null **/
        if (flags[IN1] && flags[OUT] && (flags[OP] == NULL_M)) {
            /** null square
             error = null_matrix(first_input_matrix->rows, first_input_matrix->rows, first_input_matrix->fmt, &output_matrix);
             **/
            error = null_matrix_rect(first_input_matrix->rows, first_input_matrix->columns, first_input_matrix->fmt, output_matrix);
        }
        break;
    case CMP: /** compare **/
        if (flags[IN1] && flags[IN2] && flags[OUT] && (flags[OP] == CMP)) {
            int res;
            res = cmp_matrix(first_input_matrix, second_input_matrix);
            error = create_matrix_and_fill(output_matrix, first_input_matrix->fmt, 1, 1, (double)res);
        }
        break;
    case MULT_S: /** multiply scalar **/
        if (flags[IN1] && flags[OUT] && flags[SC] && (flags[OP] == MULT_S)) {
            /** for mult scalar in place allocate for output_matrix: 	*/
            dup_matrix(first_input_matrix, output_matrix);
            error = multiply_scalar_inplace(output_matrix, scalar);
            /** error = multiply_scalar(scalar, first_input_matrix, &output_matrix); */
        }
        break;
    case MULT: /** multiply **/
        if (flags[IN1] && flags[IN2] && flags[OUT] && (flags[OP] == MULT)) {
			/** allocates for output matrix */
            error = multiply(first_input_matrix, second_input_matrix, output_matrix);
        }
        break;
    case SUM: /** sum **/
        if (flags[IN1] && flags[IN2] && flags[OUT] && (flags[OP] == SUM)) {
            /**for sum in place allocate for output_matrix */
            dup_matrix(second_input_matrix, output_matrix);
            error = sum_inplace(first_input_matrix, output_matrix);
            /** error = sum(first_input_matrix, second_input_matrix, &output_matrix); */
        }
    case TRANS: /** sum **/
        if (flags[IN1] && flags[OUT] && (flags[OP] == TRANS)) {
			/** allocates for output matrix */
            error = transpose_matrix(first_input_matrix, output_matrix);
        }
        break;
    default:
        return error;
        break;
    }
    
    return error;
}



/**----------------------------------------------------------
 *  receives the operation type, sets flags for function calls 
 * ----------------------------------------------------------*/
void set_ops_and_flags( char *op_type, int flags[] )
{
    /** already checked for NULL in calling function */
    if (strncmp(op_type, "dup", 3) == 0) {
		
        flags[OP] = DUP;
    } else if (strncmp(op_type, "null", 4) == 0) {

        flags[OP] = NULL_M;
    } else if (strncmp(op_type, "sum", 3) == 0) {

        flags[OP] = SUM;
    } else if (strncmp(op_type, "mult", 4) == 0) {

        flags[OP] = MULT;
    } else if (strncmp(op_type, "idty", 4) == 0) {

        flags[OP] = IDTY;
    } else if (strncmp(op_type, "cmp", 4) == 0) {

        flags[OP] = CMP;
    } else if (strncmp(op_type, "trans", 5) == 0) {

        flags[OP] = TRANS;
    }else {
        flags[OP] = NONE;
    }
}
