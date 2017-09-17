/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for  TenC.  It  should  be  in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/

#ifndef ERRORUTILS_H
#define ERRORUTILS_H

#include "tensor.h"

/**
* \file utils/include/errorutils.h
* \author Ian G. Tayler
* \brief Define utils for errors and alerts.
*/

/**
* \brief Print an error if two Tensors have a different shape.
*
* \param t1 Tensor.
* \param t2 Tensor.
* \param fn_name String (char *).
*/
void alert_unequal_shapes(Tensor *t1, Tensor *t2, char *fn_name);

#endif
