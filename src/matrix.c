#include "../includes/matrix.h"

#define SIZE 2048

/**---------------------------------------------------------------------
 * Frees the data inside the matrix struct, the values in the array
 * remember that IDTY, NULL, ADD, DUP, READ, MULT etc all allocate 
 * for a new matrix, so must free output_matrix after writing to file /or before 
 * reusing matrix variable
 * ---------------------------------------------------------------------*/
void free_matrix(matrix_t *first_input_matrix)
{
    if (!first_input_matrix->data) {
        return;
    }
    free(first_input_matrix->data);
    first_input_matrix->data = NULL;
}
/**---------------------------------------------------------------------
Helper function, receives matrix & allocates for it, but the data values are uniniated.
* ----------------------------------------------------------------------*/
error_t alloc_matrix(matrix_t *matrix, format fm, size_t rows, size_t columns)
{
    (matrix)->rows = rows;
    (matrix)->columns = columns;
    (matrix)->fmt = fm;
    if (((matrix)->data = (double*)malloc(sizeof(double)*rows*columns)) == NULL) {
        fprintf(stderr,"Allocation error. \n");
        return -E_ALLOC_ERROR;
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Helper function, receives allocated matrix & fills it with double elem.
* ----------------------------------------------------------------------*/
error_t fill_matrix(matrix_t *first_input_matrix, double elem)
{
    size_t i;
    for (i = 0; i < ((*first_input_matrix).rows*(*first_input_matrix).columns); i++) {
        (*first_input_matrix).data[i] = elem;
    }
    if (i != ((*first_input_matrix).rows*(*first_input_matrix).columns)) {
        fprintf(stderr,"Write error. \n");
        return -E_WRITE_ERROR;
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Creates a matrix of a specified size, format & fills with double elem.
* ----------------------------------------------------------------------*/
error_t create_matrix_and_fill(matrix_t *first_input_matrix, format fm, size_t rows, size_t columns, double elem)
{
	error_t error;
	error = alloc_matrix(first_input_matrix, fm, rows, columns);
	if (error == E_OK)
		error = fill_matrix(first_input_matrix, elem);
    return error;
}
/**---------------------------------------------------------------------
Returns the element in a specified location (must exist) in given matrix. 
* ----------------------------------------------------------------------*/
error_t get_element(const matrix_t *first_input_matrix, unsigned int row_position, unsigned int column_position, double * elem)
{
    if ((row_position > first_input_matrix->rows) || (column_position > first_input_matrix->columns)) {
        return  -E_INCOMPATIBLE_MATRIX;
    }
    row_position--;
    column_position--;
    *elem = first_input_matrix->data [ (row_position * first_input_matrix->columns) + column_position ];
    return E_OK;
}

/**---------------------------------------------------------------------
Sets an element in a specified location (must exist) in given matrix. 
* ----------------------------------------------------------------------*/
error_t set_element(matrix_t *first_input_matrix, int row_position, int column_position, const double value)
{
    if ((row_position > (*first_input_matrix).rows) || (column_position > (*first_input_matrix).columns)) {
        fprintf(stderr,"Incompatible dimensions. \n");
        return  -E_INCOMPATIBLE_MATRIX;
    }
    row_position--;
    column_position--;
    double * pointer_double;
    pointer_double = (((double*)(*first_input_matrix).data) + (((*first_input_matrix).columns)*row_position) + column_position);
    *pointer_double = value;
    return E_OK;
}
/**---------------------------------------------------------------------
Returns the number of rows in the matrix as an unsigned int
* ----------------------------------------------------------------------*/
unsigned int get_rows(const matrix_t *first_input_matrix)
{
    if (first_input_matrix != NULL) {
        return first_input_matrix->rows;
    } else
        return 0;
}
/**---------------------------------------------------------------------
Returns the number of columns in the matrix as an unsigned int
* ----------------------------------------------------------------------*/
unsigned int get_cols(const matrix_t *first_input_matrix)
{
    if (first_input_matrix != NULL) {
        return first_input_matrix->columns;
    } else
        return 0;
}
/**---------------------------------------------------------------------
Returns the values in a row in the matrix inside a list
* ----------------------------------------------------------------------*/
error_t get_row(unsigned int row_position, const matrix_t *first_input_matrix, list_t *output_list)
{
    row_position--;
    double * row;
    size_t i;
    row = first_input_matrix->data;
    row += (row_position*(first_input_matrix->columns));
    for ( i = 0;  i < (first_input_matrix->columns); i++) {
        add_back(output_list, (row[i]));
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Returns the values in a column in the matrix inside a list
* ----------------------------------------------------------------------*/
error_t get_col(unsigned int column_position, const matrix_t *first_input_matrix, list_t *output_list)
{
    column_position--;
    double * col;
    int i;
    col = first_input_matrix->data;
    col +=  column_position;
    for ( i= 0;  i < (first_input_matrix->rows); i++) {
        add_back(output_list, *(col));
        col += first_input_matrix->columns;
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Returns the values in the matrix inside a list
* ----------------------------------------------------------------------*/
error_t matrix2list(const matrix_t *first_input_matrix, list_t *output_list)
{
    int i;
    for (i = 0; i < (first_input_matrix->rows)*(first_input_matrix->columns); i++)
        add_back(output_list, first_input_matrix->data[i]);
    return E_OK;
}
/**---------------------------------------------------------------------
Duplicates a given source matrix, allocates duplicate second matrix as destination. 
* ----------------------------------------------------------------------*/
error_t dup_matrix(const matrix_t *source, matrix_t *destination)
{
    error_t error = alloc_matrix(destination, source->fmt, source->rows, source->columns);
    if (error < 0) {
        fprintf(stderr,"Allocation error. \n");
        return -E_ALLOC_ERROR;
    }
    int i;
    for (i = 0; i < (source->rows)*(source->columns); i++) {
        destination->data[i] = source->data[i];
    }
    return E_OK;
}

/**---------------------------------------------------------------------
Given a source matrix, allocates & then transposes matrix into second matrix as destination. 
* ----------------------------------------------------------------------*/
error_t transpose_matrix(matrix_t *first_input_matrix, matrix_t * output_matrix){
	error_t error = alloc_matrix(output_matrix, first_input_matrix->fmt, first_input_matrix->columns, first_input_matrix->rows);
	size_t i, j;
    for (i = 0; i < first_input_matrix->rows; i++) {
        for (j = 0; j < first_input_matrix->columns; j++) {
           output_matrix->data[ (i * first_input_matrix->columns) + j] = first_input_matrix->data[ (i * first_input_matrix->columns) + j ];
        }
	}
	return error;
}
/**---------------------------------------------------------------------
 * Creates null matrix from given dimensions (for non square null matrix)
 * Expects rows, columns and format type. Saves to *output_matrix.
 * ---------------------------------------------------------------------*/
error_t null_matrix_rect(unsigned int rows, unsigned int columns, format fm, matrix_t *output_matrix)
{
    output_matrix->rows = rows;
    output_matrix->columns = columns;
    output_matrix->fmt = fm;
    if (! (output_matrix->data = (double*)calloc(rows*columns, sizeof(double)))) {
        fprintf(stderr,"Allocation error.\n");
        return -E_ALLOC_ERROR;
    }
    return E_OK;
}
/**---------------------------------------------------------------------
 Creates square null matrix. Expects unsigned int "n" and format type.
 * ---------------------------------------------------------------------*/
error_t null_matrix(unsigned int n, format fm, matrix_t *output_matrix)
{
    return create_matrix_and_fill(output_matrix, fm, n, n, 0);
}
/**---------------------------------------------------------------------
Creates an identity matrix of a specified size, format. Stores in *output_matrix.
* ----------------------------------------------------------------------*/
error_t idty_matrix(matrix_t *output_matrix, format fm, size_t n)
{
    /** allocate for output_matrix & fill with 0 */
    int error = create_matrix_and_fill(output_matrix, fm, n, n, 0);
    if (error < 0) {
        return -E_ALLOC_ERROR;
    }
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j)
                (*output_matrix).data[ (i * n) + j ] = 1.0;
        }
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Multiplies a matrix by a scalar. Stores the result in input matrix. 
* ----------------------------------------------------------------------*/
error_t multiply_scalar_inplace(matrix_t *first_input_matrix, double scalar)
{
    if ((first_input_matrix == NULL) || ((*first_input_matrix).data == NULL)) {
        fprintf(stderr,"Null error. \n");
        return -E_NULL;
    }
    size_t i;
    for (i = 0; i < ((*first_input_matrix).rows)*((*first_input_matrix).columns); i++) {
        (*first_input_matrix).data[i] = (*first_input_matrix).data[i] * scalar;
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Multiplies a matrix by a scalar. Stores the result in *output_matrix. 
* ----------------------------------------------------------------------*/
error_t multiply_scalar(double a, const matrix_t *second_input_matrix, matrix_t *output_matrix)
{
    if ((second_input_matrix == NULL) || ((*second_input_matrix).data == NULL)) {
        fprintf(stderr,"Null matrix error. \n");
        return -E_NULL;
    }
    error_t error = dup_matrix(second_input_matrix, output_matrix);
    if (error < 0) {
        fprintf(stderr,"Allocation error. \n");
        return -E_ALLOC_ERROR;
    }
    size_t i;
    for (i = 0; i < (second_input_matrix->rows)*(second_input_matrix->columns); i++) {
        (*output_matrix).data[i] = second_input_matrix->data[i] * a;
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Multiplies two matrices of compatible size. Stores result in *output_matrix. O(n^3)
* ----------------------------------------------------------------------*/
error_t multiply(const matrix_t *first_input_matrix, const matrix_t *second_input_matrix, matrix_t *output_matrix)
{
    if ((first_input_matrix->data == NULL) || (second_input_matrix->data == NULL)) {
        fprintf(stderr, "Null error.\n");
        return -E_NULL;
    }
    size_t i, j, k;
    error_t error;
    if (first_input_matrix->columns != second_input_matrix->rows) {
        fprintf(stderr, "Matrixes are of incompatible dimensions. \n");
        return  -E_INCOMPATIBLE_MATRIX;
    }
    /** allocate for output_matrix */
    error = alloc_matrix(output_matrix, first_input_matrix->fmt, first_input_matrix->rows, second_input_matrix->columns);
    if (error < 0) {
        fprintf(stderr, "Allocation error. \n");
        return -E_ALLOC_ERROR;
    }
    double value1, value2, sum;
    for (i = 1; i <= (first_input_matrix->rows) ; i++) {
        for (j = 1; j <= (second_input_matrix->columns) ; j++) {
            sum = 0;
            for (k = 1; k <= (second_input_matrix->rows) ; k++) {
                get_element( first_input_matrix, i, k, &value1);
                get_element( second_input_matrix, k, j, &value2);
                sum += value1 * value2;
            }
            set_element(output_matrix, i, j, sum);
        }
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Sums two matrices of compatible size. Stores result in input matrix. 
* ----------------------------------------------------------------------*/
error_t sum_inplace(const matrix_t *first_input_matrix, matrix_t *second_input_matrix)
{
    if ((first_input_matrix == NULL) || (first_input_matrix->data == NULL) || ((second_input_matrix) == NULL) || ((*second_input_matrix).data == NULL)) {
        fprintf(stderr,"Null matrix error. \n");
        return -E_NULL;
    }
    /*** will sum first_input_matrix with second_input_matrix element by element, first_input_matrix and second_input_matrix must equal.*/
    if ((first_input_matrix->columns != (*second_input_matrix).columns) || (first_input_matrix->rows != (*second_input_matrix).rows)) {
        fprintf(stderr,"Matrixes are of incompatible dimensions. \n");
        return  -E_INCOMPATIBLE_MATRIX;
    }
    size_t i;
    for (i = 0; i < ((first_input_matrix->columns)*(first_input_matrix->rows)); i++) {
        (*second_input_matrix).data[i] = first_input_matrix->data[i] + (*second_input_matrix).data[i];
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Sums two matrices of compatible size. Stores result in *output_matrix. 
* ----------------------------------------------------------------------*/
error_t sum(const matrix_t *first_input_matrix, const matrix_t *second_input_matrix, matrix_t *output_matrix)
{
    /** first_input_matrix and second_input_matrix must equal size.*/
    if (first_input_matrix->columns != second_input_matrix->columns || first_input_matrix->rows != second_input_matrix->rows) {
        fprintf(stderr,"Matrixes are of incompatible dimensions. \n");
        return  -E_INCOMPATIBLE_MATRIX;
    }
    /** allocate for output_matrix */
    int error = alloc_matrix(output_matrix, first_input_matrix->fmt, first_input_matrix->rows, first_input_matrix->columns);
    if (error < 0) {
        fprintf(stderr,"Allocation error. \n");
        return -E_ALLOC_ERROR;
    }
    size_t i;
    for (i = 0; i < ((first_input_matrix->columns)*(first_input_matrix->rows)); i++) {
        (*output_matrix).data[i] = first_input_matrix->data[i] + second_input_matrix->data[i];
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Compares two matrices: returns 1 if they are equal, 0 if they are different. 
* ----------------------------------------------------------------------*/
int cmp_matrix(const matrix_t *first_input_matrix, const matrix_t *second_input_matrix)
{
    if ((first_input_matrix->rows != second_input_matrix->rows) || (first_input_matrix->columns != second_input_matrix->columns))
        return 0;
    int ok = 1;
    size_t i = 0;
    while ((ok) && (i < (first_input_matrix->rows)*(first_input_matrix->columns))) {
        ok = (first_input_matrix->data[i] == second_input_matrix->data[i]);
        i++;
    }
    return ok;
}
/**---------------------------------------------------------------------
Resize a matrix: fills with 0s if bigger, cuts excess data if smaller.
* ----------------------------------------------------------------------*/
error_t resize_matrix(unsigned int new_rows, unsigned int new_columns, matrix_t *first_input_matrix)
{
    size_t previous_size = ((first_input_matrix->rows)*(first_input_matrix->columns));
    first_input_matrix->rows = new_rows;
    first_input_matrix->columns = new_columns;
    first_input_matrix->data = (double*)realloc(first_input_matrix->data, ((first_input_matrix->columns)*(first_input_matrix->rows))*sizeof(double));
    if (!first_input_matrix->data) {
        fprintf(stderr, "Allocation error. \n");
        return -E_ALLOC_ERROR;
    }
    for (size_t i = previous_size; i < (new_rows * new_columns); i++) {
        first_input_matrix->data[i] = 0.0f;
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Prints dimnesions: rows, columns of matrix to stdout.
* ----------------------------------------------------------------------*/
error_t show_dimensions(matrix_t *first_input_matrix)
{
    if (first_input_matrix == NULL) {
        fprintf(stderr,"Null error.\n");
        return -E_NULL;
    } else {
        printf("rows: %d columns: %d\n", (*first_input_matrix).rows, (*first_input_matrix).columns);
    }
    return E_OK;
}
/**---------------------------------------------------------------------
Prints matrix to stdout: rows, columns, format and full array.
* ----------------------------------------------------------------------*/
error_t print_matrix(matrix_t *first_input_matrix)
{
    size_t i,j;
    if (((first_input_matrix->fmt) < m1) || ((first_input_matrix->fmt) > m2)) {
        fprintf(stderr,"Matrix has an unimplemented format.\n");
        return -E_FORMAT_ERROR;
    }
    if (first_input_matrix->fmt == 1)
        printf("The format is: M2\n");
        
    else if (first_input_matrix->fmt == 0)
        printf("The format is: M1\n");
        
    else printf("The format is: unimplemented");
    
    printf("Rows: %d\n", first_input_matrix->rows);
    printf("Cols: %d\n", first_input_matrix->columns);
    
    for (i = 0; i < first_input_matrix->rows; i++) {
        for (j = 0; j < first_input_matrix->columns; j++) {
            printf("%2.2lf | ", first_input_matrix->data[ (i * first_input_matrix->columns) + j ]); //
        }
        printf("\n");
    }
    return E_OK;
}

/**---------------------------------------------------------------------
 * Reads matrix from file format: M1 for ascii, M2 for binary
 * It first reads the header (M1 or M2) then any comments,
 * the dimensions: rows and columns as ints, and then the data
 * for the multidimensional array (stored as single array) codified 
 * in either ascii text or binary. Complements the write function 
 * which writes the same matrix back out to a file. 
 * ---------------------------------------------------------------------*/
error_t read_matrix(FILE *fp, matrix_t *m)
{
    /** stores HEADER M1 or M2 **/
    char buf[SIZE];
    buf[0]=buf[1]=0;

    int i;
    double n;

    /** reads HEADER M1 or M2 **/
    if (!fgets(buf, sizeof(buf), fp)) {
        return -E_READ_ERROR;
    }
    if (buf[0] != 'M' || (buf[1] != '1' && buf[1] != '2')) {
        return -E_FORMAT_ERROR;
    }
    switch (buf[1]) {
    case '1':
        m->fmt = m1;
        break;
    case '2':
        m->fmt = m2;
        break;
    default:
        m->fmt = undefined;
        break;
    }

    /** gets comment lines but does not store them **/
    char c = getc(fp);

    while (c == '#') {
        while (getc(fp) != '\n');
        c = getc(fp);
    }
    ungetc(c, fp);

    /** reads dimensions **/
    if (fscanf(fp, "%d %d", &m->rows, &m->columns) != 2) {
        return -E_READ_ERROR;
    }
    if (getc(fp) == EOF) {
        return -E_READ_ERROR;
    }

    /** reads data from array **/
    switch (m->fmt) {
    case m1: {   /** ASCII **/
        if (!(m->data = (double*)malloc(sizeof(double)*(m->rows)*(m->columns)))) { // 8*rows*columns
            return -E_ALLOC_ERROR;
        }

        for (i = 0; i < ((m->rows)*(m->columns)); i++) {
            if ((fscanf(fp, "%lf", &n)) == 1) {
                *(m->data + i) = n;
            } else return -E_READ_ERROR;
        }
    }
    break;
    case m2: {   /** binary **/
        if (!(m->data = (double*)malloc(sizeof(double)*(m->rows)*(m->columns)))) { // 8*rows*columns
            return -E_ALLOC_ERROR;
        }

        size_t read = fread((double*)m->data, sizeof(double), ((m->columns)*(m->rows)), fp);
        if (read != ((m->columns)*(m->rows))) {
            return -E_READ_ERROR;
        }
    }
    break;
    default: {
        return -E_FORMAT_ERROR;
    }
    break;
    }

    return E_OK;
}
/**---------------------------------------------------------------------
 * Writes matrix from variable to file in one of two formats
 * (M1 is ascii text, fmt M2 is binary).
 * It first writes the header (M1 or M2) then writes the dimensions
 * on the next line: rows and columns as ints, then the data
 * for the multidimensional array (stored in a single array).
 * Complements the read function which reads the same
 * matrix from a file. 
 * ---------------------------------------------------------------------*/
error_t write_matrix(FILE *fp, const matrix_t *m)
{
    error_t error = 1;
    int i, j;


    /** writes header - defines format **/
    if (m->fmt == m1) {
        error = fprintf(fp,"%s\n", "M1");
    } else if (m->fmt == m2) {

        error = fprintf(fp,"%s\n", "M2");
    } else {
        error = -E_FORMAT_ERROR;
    }
    if (error <= 0) {
        error = -E_WRITE_ERROR;
    }

    /** writes the dimensions - Rows then Columns as integer values.
     * fprintf(): "If successful, the total number of characters
     *  written is returned otherwise, a negative number is returned."
     * **/
    if (fprintf(fp, "%d %d\n", m->rows, m->columns) < 0) {
        error = -E_WRITE_ERROR;
    }

    /** writes data to file from array **/
    switch (m->fmt) {
    case m1: {   /** ASCII **/

        for (i = 0; i < (m->rows); i++) {
            for (j = 0; j < (m->columns); j++) {
                error += fprintf(fp, "%.2lf ", m->data[ (i * m->columns) + j ]);
            }
            fprintf(fp, "\n");
        }
        if (error != ((m->rows)*(m->columns))) {
            error = -E_WRITE_ERROR;
        }
        free(m->data);
    }
    break;
    case m2: {   /** binary **/
        error = fwrite(m->data, sizeof(double), m->rows*m->columns, fp);
        if (error != ((m->rows)*(m->columns))) {
            error = E_WRITE_ERROR;
        }
        free(m->data);
    }
    default: {
        error = -E_FORMAT_ERROR;
    }
    }
    error = E_OK;

    return error;
}

/**---------------------------------------------------------------------
 * Reads matrix from user input: 
 * It sets the header as ascii (M1), then reads the dimensions: 
 * rows and columns as ints, then allocates space for the data array
 * and reads the values one by one from the user input, 
 * for the multidimensional array (stored as single array).
 * ---------------------------------------------------------------------*/
error_t read_matrix_from_user( matrix_t * input_matrix) {

   input_matrix->fmt = m1;
   double input_value;

   fprintf( stdout, "Enter number of rows : \n");
   scanf( "%d", &input_matrix->rows);
  
   fprintf( stdout, "Enter number of columns : \n");
   scanf( "%d", &input_matrix->columns);
   if (!(input_matrix->data = (double*)malloc(sizeof(double)* (input_matrix->rows) * (input_matrix->columns)))){
   	return -E_ALLOC_ERROR;
   }
   for (int i = 0; i < ((input_matrix->rows )*(input_matrix->columns)); i++) {
      fprintf( stdout, "Enter double : \n");
      if ((scanf( "%lf", &input_value)) == 1) {
            *(input_matrix->data + i) = input_value;
            } else return -E_WRITE_ERROR;
      }
   return 0;
}

/** --------------------------------------------------------------------
 * helper function which calls on read_matrix, read from an input file,
 * expects an empty matrix, allocates memory, fills it according to what
 * the input file specifies and returns matrix ready for use in local mem. 
 * ---------------------------------------------------------------------*/
error_t read_and_allocate(FILE *fp, char *file_in, matrix_t *m)
{
    error_t error;
    fp = fopen(file_in, "rb");
    if (!fp) {
		printf("can't open file %s\n", file_in);
        return -E_FILE_ERROR;
    } else {
        error = read_matrix(fp, m);
        fclose(fp);
        return error;
    }
}

/** --------------------------------------------------------------------
 * helper function which calls on write_matrix, expects the out file,
 * expects an allocated matrix and writes it to the file. 
 * ---------------------------------------------------------------------*/
error_t write_matrix_to_file(FILE *fout, char *file_out, matrix_t *output_matrix){
			error_t error;
            fout = fopen(file_out, "wb");
			if (!fout) {
				perror("Error");
				return -E_FILE_ERROR;
			}
			/** write matrix frees output_matrix memory */
			error = write_matrix(fout, output_matrix);
			fclose(fout);
			return error;
}
