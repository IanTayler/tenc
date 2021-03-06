/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for  TenC.  It  should  be  in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#include <stdio.h>
#include <math.h>

#include <omp.h>

#include "tcmath.h"
#include "tensor.h"
#include "commons.h"
#include "errorutils.h"

/*************************
           ADD           *
**************************/
void tc_add(Tensor *tdest, Tensor *t2)
{
#if SAFE_MODE
    alert_unequal_shapes(tdest, t2, "tc_add");
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
    alert_unequal_shapes(tdest, t2, "tc_sub");
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
    alert_unequal_shapes(tdest, t2, "tc_mul");
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
    alert_unequal_shapes(tdest, t2, "tc_div");
#endif /* SAFE_MODE */
    int_shape_t tensorlen = tc_shape_size(tdest->shape);
#pragma omp parallel for
    for (int i = 0; i < tensorlen; i++) {
        float rightval = t2->value_array[i];
        if (rightval == 0.f) {
            rightval = 1;
            fprintf(stderr, "Division by 0 in tc_div\n");
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

/*************************
         REDUCE          *
**************************/
float tc_reduce_fn(Tensor *t, float (*fn)(float, float), float init)
{
    int_shape_t shape_size = tc_shape_size(t->shape);
    float acc = init;
    for (int i = 0; i < shape_size; i++) {
        acc = fn(acc, t->value_array[i]);
    }
    return acc;
}

float sum(float a, float b)
{
    return a + b;
}

float tc_reduce_sum(Tensor *t)
{
    return tc_reduce_fn(t, &sum, 0.f);
}

float mul(float a, float b)
{
    return a * b;
}

float tc_reduce_mul(Tensor *t)
{
    return tc_reduce_fn(t, &mul, 1.f);
}

float tc_dot_product(Tensor *t1, Tensor *t2)
{
    int_shape_t shape_size = tc_shape_size(t1->shape);
#if SAFE_MODE
    alert_unequal_shapes(t1, t2, "tc_linear_comb");
#endif /* SAFE_MODE */
    float out = 0;
    for (int i = 0; i < shape_size; i++) {
        out += t1->value_array[i] * t2->value_array[i];
    }
    return out;
}

/*************************
      NON-LINEARITIES    *
**************************/
float tc_relu(float x)
{
    if (x <= 0.f) {
        return 0.f;
    }
    return x;
}

float tc_relu_diff(float x)
{
    if (x < 0.f) {
        return 0.f;
    }
    return 1.f;
}

float tc_relu6(float x)
{
    if (x <= 0.f) {
        return 0.f;
    } else if (x >= 6.f) {
        return 6.f;
    }
    return x;
}

float tc_relu6_diff(float x)
{
    if (x < 0.f || x >= 6.f) {
        return 0.f;
    }
    return 1.f;
}

float tc_tanh(float x)
{
    return tanhf(x);
}

float tc_tanh_diff(float x)
{
    float tanh_out = tc_tanh(x);
    return 1.f - tanh_out * tanh_out;
}

float tc_sigmoid(float x)
{
    return 1.f / (1.f - expf(-x));
}

float tc_sigmoid_diff(float x)
{
    float sigmoid_out = tc_sigmoid(x);
    return sigmoid_out * (1 - sigmoid_out);;
}

/*************************
      COMPARISONS AND    *
      BOOLEAN TENSORS    *
**************************/

bool tc_near_equal_floats(float a, float b, int places)
{
    return fabsf(a - b) < powf(0.1f, (float)places);
}

void tc_near_equal(Tensor *t1, Tensor *t2, int places)
{
#if SAFE_MODE
    if (tc_shape_equal(t1->shape, t2->shape)) {
        alert_unequal_shapes(t1, t2, "tc_near_equal");
    }
#endif /* SAFE_MODE */
    int_shape_t size = tc_shape_size(t1->shape);
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        t1->value_array[i] = tc_near_equal_floats(
            t1->value_array[i], t2->value_array[i], places
        ) ? 1.f : 0.f;
    }
}

bool tc_all_near(Tensor *t, float value, int places)
{
    int_shape_t size = tc_shape_size(t->shape);
    for (int i = 0; i < size; i++) {
        if (!tc_near_equal_floats(t->value_array[i], value, places)) {
            return false;
        }
    }
    return true;
}

bool tc_reduce_all(Tensor *t, int places)
{
    int_shape_t size = tc_shape_size(t->shape);
    for (int i = 0; i < size; i++) {
        if (tc_near_equal_floats(t->value_array[i], 0.f, places)) {
            return false;
        }
    }
    return true;
}
