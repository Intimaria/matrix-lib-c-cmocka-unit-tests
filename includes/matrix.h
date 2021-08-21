#ifndef H_MATRIX
#define H_MATRIX

#include <stdio.h> /* FILE, printf, scanf etc */
#include <stdlib.h> /* allocation // NULL etc */
#include <string.h> /* *work with strings* */

#include "error.h"
#include "help.h"
#include "list.h"


#define SIZE 2048


typedef enum f {
    m1,
    m2,
    undefined
} format;


typedef struct mat {
    format fmt;
    unsigned int rows, columns;
    double *data;
} matrix_t;


void free_matrix(matrix_t *first_input_matrix);

error_t alloc_matrix(matrix_t *first_input_matrix, format fm, size_t rows, size_t columns);

error_t create_matrix_and_fill(matrix_t *first_input_matrix, format form, size_t rows, size_t columns, double elem);

error_t fill_matrix(matrix_t *first_input_matrix, double elem);

error_t get_element(const matrix_t *first_input_matrix, unsigned int row_position, unsigned int column_position, double * elem);

error_t set_element(matrix_t *first_input_matrix, int row_position, int column_position, const double value);

unsigned int get_rows(const matrix_t *first_input_matrix);

unsigned int get_cols(const matrix_t *first_input_matrix);

error_t get_row(unsigned int row_position, const matrix_t *first_input_matrix, list_t *output_list);

error_t get_col(unsigned int column_position, const matrix_t *first_input_matrix, list_t *output_list);

error_t matrix2list(const matrix_t *first_input_matrix, list_t *output_list);

error_t dup_matrix(const matrix_t *source, matrix_t *destination);

error_t transpose_matrix(matrix_t *first_input_matrix, matrix_t * output_matrix);

error_t null_matrix_rect(unsigned int rows, unsigned int columns, format fm, matrix_t *output_matrix);

error_t null_matrix(unsigned int n, format fm, matrix_t *output_matrix);

error_t idty_matrix(matrix_t *output_matrix, format fm, size_t n);

error_t multiply_scalar_inplace(matrix_t *first_input_matrix, double scalar);

error_t multiply_scalar(double a, const matrix_t *second_input_matrix, matrix_t *output_matrix);

error_t multiply(const matrix_t *first_input_matrix, const matrix_t *second_input_matrix, matrix_t *output_matrix);

error_t sum_inplace(const matrix_t *first_input_matrix, matrix_t *second_input_matrix);

error_t sum(const matrix_t *first_input_matrix, const matrix_t *second_input_matrix, matrix_t *output_matrix);

int cmp_matrix(const matrix_t *first_input_matrix, const matrix_t *second_input_matrix);

error_t resize_matrix(unsigned int new_rows, unsigned int new_columns, matrix_t *first_input_matrix);

error_t show_dimensions(matrix_t *ma);

error_t print_matrix(matrix_t *ma);



/***Reads matrix from file in one of two formats ( M1 is ascii, fmt M2 is binary)
 * It first reads the header (M1 or M2) then any possible comments,
 * the dimensions, rows and columns as ints, and finally the data
 * for the multidimensional array (stored in one array) in either
 * text or binary. Compliment of the write function which writes the same
 * matrix to a file. */
error_t read_matrix(FILE *fp, matrix_t *input_matrix);

/***Writes matrix from variable to file in one of two formats
 * ( M1 is ascii, fmt M2 is binary ).
 * It first writes the header (M1 or M2) then writes the dimensions
 * rows and columns as ints on the next line, and the data
 * for the multidimensional array (stored in one array).
 * Compliment of the read function which reads the same
 * matrix from a file. */
error_t write_matrix(FILE *fp, const matrix_t *output_matrix);

/** Read and allocate for matrixes in input files*/
error_t read_and_allocate(FILE * fp, char * file_in, matrix_t * input_matrix);

error_t read_matrix_from_user( matrix_t * input_matrix);

error_t write_matrix_to_file(FILE *fout, char *file_out, matrix_t *output_matrix);


#endif



