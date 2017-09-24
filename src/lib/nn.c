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
#include "nn.h"

void tcnn_free_neuron(Neuron *n)
{
    tc_free_tensor(n->w);
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
