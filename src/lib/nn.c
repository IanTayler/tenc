/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for  TenC.  It  should  be  in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/

#include <stdlib.h>

#include <omp.h>

#include "tensor.h"
#include "tcmath.h"
#include "randutils.h"
#include "nn.h"

void tcnn_free_neuron(Neuron *n)
{
    /* Note Neurons in the same Layer normally share a Shape, so we don't want
    * to free it every time we free a Neuron. */
    tc_free_tensor_w_shared_shape(n->w);
    free(n);
}

void tcnn_free_layer(Layer *l)
{
#pragma omp parallel for
    for (int i = 0; i < l->size; i++) {
        tcnn_free_neuron(l->neurons[i]);
    }
    tc_free_tensor(l->out);
    tc_free_shape(l->input_shape);
    free(l);
}

Neuron *generate_neuron(Shape *shape, float (*init)(void))
{
    Tensor *w = tc_generate(shape, init);
    Neuron *n = malloc(sizeof(*n));
    n->w = w;
    n->b = init();
    return n;
}

Layer *tcnn_custom_layer(Shape *in_shape, Shape *out_shape,
                         float (*actvf)(float), float (*bpf)(float),
                         float (*init)(void))
{
    Layer *l = malloc(sizeof(*l));
    l->input_shape = in_shape;
    l->size = tc_shape_size(out_shape);
    l->neurons = malloc(sizeof(*(l->neurons)) * l->size);
    /* We don't want to parallelize this because we're probably using a random
    * init and parallelizing it could result in repeated pseudo-random numbers
    * across neurons. */
    for (int i = 0; i < l->size; i++) {
        l->neurons[i] = generate_neuron(in_shape, init);
    }
    l->out = tc_zeros(out_shape);
    l->actvf = actvf;
    l->bpf = bpf;
    return l;
}

Layer *tcnn_relu_layer(Shape *in_shape, Shape *out_shape)
{
    return tcnn_custom_layer(
        in_shape, out_shape, &tc_relu, &tc_relu_diff, &random_float
    );
}

Layer *tcnn_relu6_layer(Shape *in_shape, Shape *out_shape)
{
    return tcnn_custom_layer(
        in_shape, out_shape, &tc_relu6, &tc_relu6_diff, &random_float
    );
}

Layer *tcnn_tanh_layer(Shape *in_shape, Shape *out_shape)
{
    return tcnn_custom_layer(
        in_shape, out_shape, &tc_tanh, &tc_tanh_diff, &random_float
    );
}

Layer *tcnn_sigmoid_layer(Shape *in_shape, Shape *out_shape)
{
    return tcnn_custom_layer(
        in_shape, out_shape, &tc_sigmoid, &tc_sigmoid_diff, &random_float
    );
}
