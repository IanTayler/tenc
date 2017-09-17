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

#include "errorutils.h"
#include "tensor.h"
#include "pprint.h"

void alert_unequal_shapes(Tensor *t1, Tensor *t2, char *fn_name)
{
    if (!tc_shape_equal(t1->shape, t2->shape)) {
        /* Shapes aren't the same */
        fprintf(stderr, "Unequal shapes in %s.\n", fn_name);
        fprintf(stderr, "Shape 1: %s\n", tc_btfy_shape(t1->shape));
        fprintf(stderr, "Shape 2: %s\n", tc_btfy_shape(t2->shape));
    }
}
