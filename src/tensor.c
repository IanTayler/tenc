/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#include "tensor.h"

/***********************************************
*                     SHAPE                    *
***********************************************/
Shape *tc_new_shape(int length, int_shape_t *shape_arr)
{
    Shape *ptr = malloc(sizeof(*ptr));
    ptr->shape_len = length;
    ptr->shape = shape_arr;
    return ptr;
}

void tc_free_shape(Shape *ptr)
{
    free(ptr->shape);
    free(ptr);
}

int_shape_t tc_shape_size(Shape *shape)
{
    int_shape_t retval = 1;
    int len = shape->shape_len;
    for (int i = 0; i < len; i++) {
        retval *= shape->shape[i];
    }
    return retval;
}

/***********************************************
*                    TENSOR                    *
***********************************************/
Tensor *tc_new_tensor(Shape *shape, float *value_array)
{
    Tensor *ptr = malloc(sizeof(*ptr));
    ptr->shape = shape;
    ptr->value_array = value_array;
    return ptr;
}

void tc_free_tensor(Tensor *ptr)
{
    tc_free_shape(ptr->shape);
    free(ptr->value_array);
    free(ptr);
}

/* INITIALIZERS */

Tensor *tc_zeros(Shape *shape)
{
    int_shape_t nmemb = tc_shape_size(shape);
    float *value_arr = calloc(nmemb, sizeof(*value_arr));
    return tc_new_tensor(shape, value_arr);
}

Tensor *tc_fill(Shape *shape, float value)
{
    int_shape_t size = tc_shape_size(shape);
    float *value_arr = malloc(sizeof(*value_arr) * size);
    /* We're using OpenMP for parallelization */
#pragma omp parallel for
    for (int i = 0; i < size; i++)
        value_arr[i] = value;
    return tc_new_tensor(shape, value_arr);
}
