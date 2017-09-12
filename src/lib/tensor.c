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
#include <stdbool.h>

#include <omp.h>

#include "tensor.h"

/***********************************************
*                     SHAPE                    *
***********************************************/
Shape *tc_new_shape(int length, int_shape_t *shape_arr)
{
    Shape *ptr = malloc(sizeof(*ptr));
    ptr->len = length;
    ptr->arr = shape_arr;
    return ptr;
}

Shape *tc_copy_shape(Shape *shape)
{
    int_shape_t *copy_arr = malloc(sizeof(*copy_arr) * shape->len);
#pragma omp parallel for
    for (int i = 0; i < shape->len; i++) {
        copy_arr[i] = shape->arr[i];
    }
    Shape *copy = tc_new_shape(shape->len, copy_arr);
    return copy;
}

void tc_free_shape(Shape *ptr)
{
    free(ptr->arr);
    free(ptr);
}

int_shape_t tc_shape_size(Shape *shape)
{
    int_shape_t retval = 1;
    int len = shape->len;
    for (int i = 0; i < len; i++) {
        retval *= shape->arr[i];
    }
    return retval;
}

bool tc_shape_equal(Shape *s1, Shape *s2)
{
    if (s1->len != s2->len) {
        return false;
    }
    for (int i = 0; i < s1->len; i++) {
        if (s1->arr[i] != s2->arr[i]) {
            return false;
        }
    }
    /* If we've gotten here, the shapes are equal */
    return true;
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

Tensor *tc_copy_tensor(Tensor *t)
{
    Shape *copy_shape = tc_copy_shape(t->shape);
    int_shape_t shape_size = tc_shape_size(copy_shape);
    float *copy_arr = malloc(sizeof(*copy_arr) * shape_size);
#pragma omp parallel for
    for (int i = 0; i < shape_size; i++) {
        copy_arr[i] = t->value_array[i];
    }
    Tensor *copy = tc_new_tensor(copy_shape, copy_arr);
    return copy;
}

Tensor *tc_shape_to_tensor(Shape *shape)
{
    int_shape_t *shape_shape_arr = malloc(sizeof(*shape_shape_arr));
    shape_shape_arr[0] = shape->len;
    Shape *shape_shape = tc_new_shape(1, shape_shape_arr);
    float *value_array = malloc(sizeof(float) * shape->len);
    for (int i =0; i < shape->len; i++) {
        value_array[i] = (float)shape->arr[i];
    }
    Tensor *ptr = tc_new_tensor(shape_shape, value_array);
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

Tensor *tc_zeros_like(Tensor *t)
{
    return tc_zeros(t->shape);
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

Tensor *tc_ones(Shape *shape)
{
    /* TODO: search for a faster way */
    return tc_fill(shape, 1.0f);
}

Tensor *tc_ones_like(Tensor *t)
{
    return tc_ones(t->shape);
}
