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
#include "minunit-ext.h"
#include "testfunctions.h"

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
