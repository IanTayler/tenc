/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/

#include <stdlib.h>

#include "tensor.h"
#include "tcmath.h"
#include "minunit-ext.h"
#include "testfunctions.h"
#include "randutils.h"

char *shape_new_and_free()
{
    test_running = "shape_new_and_free";
    int shapelen = 3;
    int_shape_t *shapearr = malloc(sizeof(*shapearr) * shapelen);
    shapearr[0] = 2;
    shapearr[1] = 4097;
    shapearr[2] = 45000;
    Shape *s = tc_new_shape(shapelen, shapearr);
    Shape *s2 = malloc(sizeof(*s2));
    s2->len = shapelen;
    s2->arr = shapearr;
    mu_assert_running(
        "tc_new_shape is failing to produce the expected Shape",
        tc_shape_equal(s, s2),
        {
            tc_free_shape(s);
            /* This will suffice because they share pointers */
            free(s2);
        }
    );
    tc_free_shape(s);
    free(s2);
    return 0;
}
/* test initialization and deallocation of shapes */
char *tensor_new_and_free()
{
    test_running = "tensor_new_and_free";
    Shape *s = tc_matrix_shape(4, 5);
    int_shape_t size = tc_shape_size(s);
    float *arr = calloc(size, sizeof(*arr));
    Tensor *t = tc_new_tensor(s, arr);
    tc_free_tensor(t);
    /* We got here without throwing an error, so we pass this test.
    TODO: think of possible assertions. */
    return 0;
}

#define DEFAULT_PLACES 6

/* test Tensor initializers like tc_zeros and tc_ones */
char *zeros_works()
{
    test_running = "zeros_works";
    Shape *s = tc_3d_shape(120, 120, 3);
    Tensor *t = tc_zeros(s);
    bool check = tc_all_near(t, 0.f, DEFAULT_PLACES);
    mu_assert_running(
        "tc_zeros is returning non-zeroes.",
        check, {
            tc_free_tensor(t);
        }
    );
    tc_free_tensor(t);
    return 0;
}

char *ones_works()
{
    test_running = "ones_works";
    Shape *s = tc_4d_shape(15, 120, 120, 3);
    Tensor *t = tc_ones(s);
    bool check = tc_all_near(t, 1.f, DEFAULT_PLACES);
    mu_assert_running(
        "tc_ones is returning non-ones.",
        check, {
            tc_free_tensor(t);
        }
    );
    tc_free_tensor(t);
    return 0;
}

char *fill_works()
{
    test_running = "fill_works";
    Shape *s = tc_4d_shape(15, 120, 120, 3);
    float randval = random_float();
    Tensor *t = tc_fill(s, randval);
    bool check = tc_all_near(t, randval, DEFAULT_PLACES);
    mu_assert_running(
        "tc_fill is filling with wrong values.",
        check, {
            tc_free_tensor(t);
        }
    );
    tc_free_tensor(t);
    return 0;
}

char *tensor_copy_works()
{
    test_running = "tensor_copy_works";
    Tensor *t = tc_fill(tc_vector_shape(780), random_float());
    Tensor *copy = tc_copy_tensor(t);
    tc_near_equal(t, copy, DEFAULT_PLACES); /* saves result to t */
    bool check = tc_reduce_all(t, DEFAULT_PLACES);
    bool check2 = tc_all_near(t, 1.f, DEFAULT_PLACES);
    mu_assert_running(
        "Equality between Tensor and copy doesn't reduce_all to true.",
        check,
        {
            tc_free_tensor(t);
            tc_free_tensor(copy);
        }
    );
    mu_assert_running(
        "Equality between Tensor and copy doesn't yield all near ones.",
        check2,
        {
            tc_free_tensor(t);
            tc_free_tensor(copy);
        }
    );
    tc_free_tensor(t);
    tc_free_tensor(copy);
    return 0;
}
