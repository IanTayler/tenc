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

#include "tensor.h"
#include "tcmath.h"
#include "nn.h"

float tcnn_activate_neuron(Neuron *n, Tensor *inp)
{
    float retv = tc_linear_comb(inp, n->w);
    retv += n->b;
    retv = n->actvf(retv);
    return retv;
}

void tcnn_free_neuron(Neuron *n)
{
    tc_free_tensor(n->w);
    free(n);
}
