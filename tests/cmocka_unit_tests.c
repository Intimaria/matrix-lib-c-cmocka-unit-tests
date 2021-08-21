#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../includes/matrix.h"    
#include "../includes/list.h"
#include "../includes/error.h"

matrix_t matrix;
matrix_t m;

error_t e;
FILE * fp;

// helper function
static matrix_t create_new_default_matrix( int rows, int cols, int fmt, double value){
    matrix_t  default_matrix;
    create_matrix_and_fill(&default_matrix, fmt, rows, cols, value);
    return default_matrix;
}

// Test Cases
static void test_create_matrix_alloc_success(void **state){
    (void)state;

    m =  create_new_default_matrix(2, 3, m2, 2);
    assert_non_null (m.data[5]);
}
static void test_create_matrix_value_success(void **state){
    (void)state;

    m =  create_new_default_matrix(2, 3, m2, 2);
    assert_float_equal (m.data[0], 2, 2);
}
static void test_free_matrix_success(void **state){
    (void)state;
    m =  create_new_default_matrix(2, 3, m2, 1);
    free_matrix(&m);
    assert_null(m.data);
}
static void test_matrix_null_create_success(void **state){
    (void)state;
    assert_int_equal ( null_matrix(2, m2, &m), E_OK);
}
static void test_matrix_null_value_success(void **state){
    (void)state;
    null_matrix(2, m2, &m);
    assert_float_equal (m.data[0], 0.0, 2);
}
static void test_matrix_idty_success(void **state){
 (void)state;

    idty_matrix(&m, m2, 2);
    assert_float_equal (m.data[0], 1.0, 2);
    assert_float_equal (m.data[1], 0.0, 2);
}
static void test_get_dimensions_rows_success(void **state){
    (void)state;
    m =  create_new_default_matrix(2, 3, m2, 1);
    assert_int_equal (get_rows(&m), 2);
}
static void test_get_dimensions_cols_success(void **state){
    (void)state;
    m =  create_new_default_matrix(2, 3, m2, 1);
    assert_int_equal (get_cols(&m), 3);
}
static void test_get_dimensions_rows_null_fail(void **state){
    (void)state;
    matrix_t m1;
    assert_int_equal (get_rows(&m1), 0);
}
static void test_get_dimensions_cols_null_fail(void **state){
    (void)state;
    matrix_t m1;
    assert_int_equal (get_cols(&m1), 0);
}

static void test_get_elem_success(void **state){
    (void)state; 
    double d;
    m =  create_new_default_matrix(2, 2, m2, 2);
    get_element(&m, 1, 1, &d);
    assert_float_equal(d, 2, 2);
}

static void test_get_elem_incompatible_fail(void **state){
    (void)state;
    double d;
    m =  create_new_default_matrix(2, 2, m2, 0);
    assert_int_equal(get_element(&m, 3, 3, &d), -1*E_INCOMPATIBLE_MATRIX);
}


static void test_set_elem_success(void **state){
    (void)state;

    m =  create_new_default_matrix(3, 3, m2, 0);
    set_element(&m, 1, 1, 2);
    assert_float_equal(m.data[0], 2, 2);
}

static void test_set_elem_incompatible_fail(void **state){
    (void)state;

    m =  create_new_default_matrix(2, 2, m2, 0);
    assert_int_equal(set_element(&m, 3, 3, 2.2), -1*E_INCOMPATIBLE_MATRIX);
}


static void test_sum_matrix_incompatible_no_size_fail(void **state){
    (void)state;
    matrix_t result;
    //expected fail due to wrong dimensions
    m =  create_new_default_matrix(0, 0, m2, 0);
    assert_int_equal(sum(&m, &matrix, &result), -1*E_INCOMPATIBLE_MATRIX);
}

static void test_sum_matrix_incompatible_dimensions_fail(void **state){
    (void)state;
    matrix_t result;
    //expected fail due to wrong dimensions
    m =  create_new_default_matrix(6, 1, m2, 2);
    assert_int_equal(sum(&m, &matrix, &result), -1*E_INCOMPATIBLE_MATRIX);
}

static void test_sum_matrix_neutral_sucess(void **state){
    (void)state;
    matrix_t result;
    //neutral sum with 0
    m =  create_new_default_matrix(3, 4, m2, 0);

    sum(&m, &matrix, &result);
    assert_float_equal(matrix.data[0], result.data[0],2);

    free_matrix(&result);
}

static void test_sum_matrix_success(void **state){
    (void)state;
    matrix_t result;
    //normal sum expected success
    m =  create_new_default_matrix(3, 4, m2, 2);

    sum(&m, &matrix, &result);
    assert_float_equal(matrix.data[0]+2, result.data[0], 2);

    free_matrix(&result);
}

static void test_mult_matrix_null_pointer_fail(void **state){
    (void)state;
    matrix_t result, null_pointer;
    null_pointer.data = NULL;
    //expected fail due to wrong dimensions
    assert_int_equal(multiply(&m, &null_pointer, &result), -1*E_NULL);

}

static void test_mult_matrix_incompatible_nosize_fail(void **state){
    (void)state;
    matrix_t result;

    //expected fail due to wrong dimensions
     m =  create_new_default_matrix(0, 0, m2, 0);
    assert_int_equal(multiply(&m, &matrix, &result), -1*E_INCOMPATIBLE_MATRIX);

}

static void test_mult_matrix_incompatible_dimensions_fail(void **state){
    (void)state;
    matrix_t result;

    //expected fail due to wrong dimensions
    m =  create_new_default_matrix(3, 6, m2, 0);
    assert_int_equal(multiply(&m, &matrix, &result), -1*E_INCOMPATIBLE_MATRIX);
}

static void test_mult_matrix_neutral_success(void **state){
    (void)state;
    matrix_t result;

    //neutral product with idty
    idty_matrix(&m, m2, 4);
    multiply(&matrix, &m, &result);
    assert_float_equal(matrix.data[0], result.data[0], 2);

    free_matrix(&result);
}
static void test_mult_matrix_success(void **state){
    (void)state;
    matrix_t result;
    //normal product expected success
    m =  create_new_default_matrix(4, 3, m2, 2);
    multiply(&matrix, &m, &result);
    assert_float_equal(30.80, result.data[0], 2);

    free_matrix(&result);
}
static void test_dup_matrix_success(void **state){
    (void)state;
    dup_matrix(&matrix, &m);
    
    assert_float_equal(matrix.data[0], m.data[0], 2);
    assert_float_equal(matrix.data[1], m.data[1], 2);
    assert_float_equal(matrix.data[5], m.data[5], 2);
}
static void test_mult_scalar_matrix_fail(void **state){
    (void)state;
    matrix_t result;
    //normal product expected success
    assert_int_equal(multiply_scalar (2.2, &m, &result), -1*E_NULL);
}
static void test_mult_scalar_matrix_success(void **state){
    (void)state;
    matrix_t result;

    //normal product expected success
    multiply_scalar (2.2, &matrix, &result);

    assert_float_equal(matrix.data[0]*2.2, result.data[0], 2);
    assert_float_equal(matrix.data[1]*2.2, result.data[1], 2);
    assert_float_equal(matrix.data[2]*2.2, result.data[2], 2);

    free_matrix(&result);
}

static void test_compare_matrix_success(void **state){
    (void)state;
    assert_int_equal(cmp_matrix(&matrix,&matrix), 1);
}
static void test_compare_matrix_fail(void **state){
    (void)state;
    m =  create_new_default_matrix(2, 3, m2, 1);
    assert_int_equal(cmp_matrix(&matrix, &m), 0);
}
static void test_resize_matrix_smaller_success(void **state){

    (void)state;
    e = idty_matrix(&m, m2, 5);
    assert_int_equal(e, E_OK);
    //smaller
    e = resize_matrix(2, 2, &m);
    assert_int_equal(e, E_OK);
    assert_int_equal(get_rows(&m),2);
    assert_int_equal(get_cols(&m),2);
}

static void test_resize_matrix_bigger_success(void **state){

    (void)state;
    e = idty_matrix(&m, m2, 5);
    assert_int_equal(e, E_OK);
    //bigger
    e = resize_matrix(15, 15, &m);
    assert_int_equal(e, E_OK);
    assert_int_equal(get_rows(&m),15);
    assert_int_equal(get_cols(&m),15);
}


static int set_up(void **state){
    (void)state;
    return 0;
}
static int tear_down(void **state){
    free(*state);
    free_matrix(&m);
    return 0;
} 

static int set_up_group(void **state)
{

    (void)state;

    matrix.fmt  = m2;
    matrix.rows = 3;
    matrix.columns = 4;
    double n[12] = {2.3, 5.6, 2.1, 5.4, 
                    7.6, 8.7, 3.4, 7.8, 
                    3.5, 2.3, 1.2, 5.6};
    
	matrix.data = (double*)malloc(sizeof(double)*12);

	for (size_t i = 0; i < 12; i++)
	{
		matrix.data[i] = n[i];
	}
    return 0;
}

static int tear_down_group(void **state)
{
    free(*state);
    free_matrix(&matrix);
    return 0;
}

int main(void)
{
    const struct CMUnitTest tests_matrix[] = {
        cmocka_unit_test_setup_teardown(test_create_matrix_alloc_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_create_matrix_value_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_matrix_null_create_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_matrix_null_value_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_matrix_idty_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_set_elem_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_set_elem_incompatible_fail, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_get_elem_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_get_elem_incompatible_fail, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_sum_matrix_incompatible_no_size_fail, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_sum_matrix_incompatible_dimensions_fail, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_sum_matrix_neutral_sucess, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_sum_matrix_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_mult_matrix_null_pointer_fail, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_mult_matrix_incompatible_nosize_fail, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_mult_matrix_incompatible_dimensions_fail, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_mult_matrix_neutral_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_mult_matrix_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_dup_matrix_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_get_dimensions_rows_null_fail, set_up, NULL),
        cmocka_unit_test_setup_teardown(test_get_dimensions_cols_null_fail, set_up, NULL),
        cmocka_unit_test_setup_teardown(test_resize_matrix_smaller_success, set_up, tear_down),
        cmocka_unit_test_setup_teardown(test_resize_matrix_bigger_success, set_up, tear_down),
        cmocka_unit_test(test_get_dimensions_rows_success),
        cmocka_unit_test(test_get_dimensions_cols_success),
        cmocka_unit_test(test_free_matrix_success),
        cmocka_unit_test(test_mult_scalar_matrix_success),
        cmocka_unit_test(test_mult_scalar_matrix_fail),
        cmocka_unit_test(test_compare_matrix_success),
        cmocka_unit_test(test_compare_matrix_fail),
        };

    return cmocka_run_group_tests(tests_matrix, set_up_group, tear_down_group);
}