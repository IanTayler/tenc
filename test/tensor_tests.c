/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/

#include "tensor.h"
#include "minunit-ext.h"
#include "testfunctions.h"

/* test initialization and deallocation of shapes */
char *tensor_new_and_free()
{
    test_running = "tensor_new_and_free";

}
