#ifndef H_ERROR
#define H_ERROR

#include <stdio.h>

/**Types of errors that may ocurr
 * are defined here. T
 */

#define   E_OK								0
#define   E_INPUT_ERROR						1
#define   E_FILE_ERROR						2
#define   E_READ_ERROR						3
#define   E_WRITE_ERROR						4
#define   E_SIZE_ERROR						5
#define   E_INCOMPATIBLE_MATRIX				6
#define   E_FORMAT_ERROR					7
#define   E_NULL							8
#define   E_ALLOC_ERROR						9
#define   E_UNIMPLEMENTED_FUNCTION_ERROR	15
#define   E_UNSPECIFIED_ERROR				20

typedef int error_t;

int error_help(FILE *fp, error_t e);

#endif
