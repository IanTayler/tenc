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

#include <omp.h>

#include "math.h"
#include "tensor.h"
#include "commons.h"

/*************************
           ADD           *
**************************/
void tc_add(Tensor *tdest, Tensor *t2)
{
#if SAFE_MODE
    if (!tc_shape_equal(tdest->shape, t2->shape)) {
        /* Shapes aren't the same */
        fprintf(stderr, "Unequal shapes in tc_add.");
    }
#endif /* SAFE_MODE */
    int_shape_t tensorlen = tc_shape_size(tdest->shape);
#pragma omp parallel for
    for (int i = 0; i < tensorlen; i++) {
        tdest->value_array[i] += t2->value_array[i];
    }
}

void tc_add_and_free(Tensor *tdest, Tensor *t2)
{
    tc_add(tdest, t2);
    tc_free_tensor(t2);
}

Tensor *tc_add_pure(Tensor *t1, Tensor *t2)
{
    /* TODO: make more efficient (don't waste an iteration) */
    Tensor *copy = tc_copy_tensor(t1);
    tc_add(copy, t2);
    return copy;
}

/*************************
           SUB           *
**************************/
void tc_sub(Tensor *tdest, Tensor *t2)
{
#if SAFE_MODE
    if (!tc_shape_equal(tdest->shape, t2->shape)) {
        /* Shapes aren't the same */
        fprintf(stderr, "Unequal shapes in tc_sub.");
    }
#endif /* SAFE_MODE */
    int_shape_t tensorlen = tc_shape_size(tdest->shape);
#pragma omp parallel for
    for (int i = 0; i < tensorlen; i++) {
        tdest->value_array[i] -= t2->value_array[i];
    }
}

void tc_sub_and_free(Tensor *tdest, Tensor *t2)
{
    tc_sub(tdest, t2);
    tc_free_tensor(t2);
}

Tensor *tc_sub_pure(Tensor *t1, Tensor *t2)
{
    /* TODO: make more efficient (don't waste an iteration) */
    Tensor *copy = tc_copy_tensor(t1);
    tc_sub(copy, t2);
    return copy;
}

/*************************
           MUL           *
**************************/
void tc_mul(Tensor *tdest, Tensor *t2)
{
#if SAFE_MODE
    if (!tc_shape_equal(tdest->shape, t2->shape)) {
        /* Shapes aren't the same */
        fprintf(stderr, "Unequal shapes in tc_mul.");
    }
#endif /* SAFE_MODE */
    int_shape_t tensorlen = tc_shape_size(tdest->shape);
#pragma omp parallel for
    for (int i = 0; i < tensorlen; i++) {
        tdest->value_array[i] *= t2->value_array[i];
    }
}

void tc_mul_and_free(Tensor *tdest, Tensor *t2)
{
    tc_mul(tdest, t2);
    tc_free_tensor(t2);
}

Tensor *tc_mul_pure(Tensor *t1, Tensor *t2)
{
    /* TODO: make more efficient (don't waste an iteration) */
    Tensor *copy = tc_copy_tensor(t1);
    tc_mul(copy, t2);
    return copy;
}

/*************************
           DIV           *
**************************/
void tc_div(Tensor *tdest, Tensor *t2)
{
#if SAFE_MODE
    if (!tc_shape_equal(tdest->shape, t2->shape)) {
        /* Shapes aren't the same */
        fprintf(stderr, "Unequal shapes in tc_div.");
    }
#endif /* SAFE_MODE */
    int_shape_t tensorlen = tc_shape_size(tdest->shape);
#pragma omp parallel for
    for (int i = 0; i < tensorlen; i++) {
        float rightval = t2->value_array[i];
        if (rightval == 0.f) {
            rightval = 1;
            fprintf(stderr, "Division by 0 in tc_div");
        }
        tdest->value_array[i] /= rightval;
    }
}

void tc_div_and_free(Tensor *tdest, Tensor *t2)
{
    tc_div(tdest, t2);
    tc_free_tensor(t2);
}

Tensor *tc_div_pure(Tensor *t1, Tensor *t2)
{
    /* TODO: make more efficient (don't waste an iteration) */
    Tensor *copy = tc_copy_tensor(t1);
    tc_div(copy, t2);
    return copy;
}
