/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#ifndef PPRINT_H
#define PPRINT_H

#include "tensor.h"

/**
* \file include/pprint.h
* \author Ian G. Tayler
* \brief Defines pretty-print functions.
*/

/**
* \brief Gets a string representation of a Tensor.
*
* \param t Tensor.
*
* \return Dynamically allocated string.
*/
char *tc_btfy(Tensor *t);
/**
* \brief Gets a string representation of a Shape.
*
* \param shape Shape.
*
* \return Dynamically allocated string.
*/
char *tc_btfy_shape(Shape *shape);
/**
* \brief Pretty printer for Tensors.
*
* \param t Tensor to be printed.
*/
void tc_pprint(Tensor *t);
/**
* \brief Pretty printer for Shapes.
*
* \param shape Shape to be printed.
*/
void tc_pprint_shape(Shape *shape);
#endif
