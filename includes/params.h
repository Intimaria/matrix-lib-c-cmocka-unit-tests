#ifndef H_PARAMS
#define H_PARAMS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"
#include "error.h"

#define FLAGS 5

/** args in */
#define IN1 0
#define IN2 1
#define OUT 2
#define SC  3
#define OP  4

/** operations */
#define NONE   0
#define DUP    1
#define IDTY   2
#define NULL_M 3
#define CMP    4
#define MULT_S 5
#define MULT   6
#define SUM    7
#define TRANS  8


/** parses args - reads values "scalar", "help", "file in 1", "file in 2" and "file out". **/
error_t parse (int argc, char *argv[], int flags[], double *scalar, char **file_in1,char **file_in2, char **file_out, bool *help, bool *args_complete);

/** Sets flags for operations  (mult / cmp.. etc)*/
void set_ops_and_flags( char *op_type, int flags[]);

/** Expects arguments from commandline, validates & calls operations (mult / cmp.. etc). Writes the result to outfile */
error_t sort_and_call(int argc, char *argv[], int flags[], double scalar, matrix_t * first_input_matrix, matrix_t * second_input_matrix, matrix_t * output_matrix);

#endif
