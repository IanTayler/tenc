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

#include "tensor.h"

/***********************************************
*                     SHAPE                    *
***********************************************/
Shape *new_shape(int length, int_shape_t *shape_arr)
{
    Shape *ptr = malloc(sizeof(Shape));
    ptr->shape_len = length;
    ptr->shape = shape_arr;
    return ptr;
}

void free_shape(Shape *ptr)
{
    free(ptr->shape);
    free(ptr);
}

/***********************************************
*                    TENSOR                    *
***********************************************/
Tensor *new_tensor(Shape *shape, float *value_array)
{
    Tensor *ptr = malloc(sizeof(Tensor));
    ptr->shape = shape;
    ptr->value_array = value_array;
    return ptr;
}

void free_tensor(Tensor *ptr)
{
    free_shape(ptr->shape);
    free(ptr->value_array);
    free(ptr);
}
