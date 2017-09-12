/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#ifndef MATH_H
#define MATH_H
#include "tensor.h"

/**
* \file include/math.h
* \author Ian G. Tayler
*
* \brief Defines mathematical functions for Tensors.
*/

/**
* \brief Add two Tensor-s element-wise, save the result in the first one.
*
* \param tdest Tensor. One of the terms of the sum, and also the destination.
* \param t2 Tensor. Same Shape as tdest.
*
* \note There is no return value. The result is saved in Tensor tdest.
* Therefore, you will lose whatever information you had in tdest.
*
* \see tc_add_pure tc_add_and_free
*/
void tc_add(Tensor *tdest, Tensor *t2);

/**
* \brief Add two Tensor-s element-wise. Save the result in tdest, free t2
*
* \param tdest Tensor. Destination.
* \param t2 Tensor. Same Shape as tdest. Will be freed.
* \see tc_add tc_add_pure
*/
void tc_add_and_free(Tensor *tdest, Tensor *t2);

/**
* \brief Add two Tensor-s element-wise, return a pointer to the sum-Tensor.
*
* \param t1 Tensor.
* \param t2 Tensor. Same Shape as t1.
*
* \return Tensor (pointer) with the element-wise sum.
*
* \see tc_add_and_free tc_add
*/
Tensor *tc_add_pure(Tensor *t1, Tensor *t2);

/**
* \brief Subtract two Tensor-s element-wise, save the result in the first one.
*
* \param tdest Tensor. One of the terms of the subtraction, and also the
* destination.
* \param t2 Tensor. Same Shape as tdest.
*
* \note There is no return value. The result is saved in Tensor tdest.
* Therefore, you will lose whatever information you had in tdest.
*
* \see tc_sub_pure tc_sub_and_free
*/
void tc_sub(Tensor *tdest, Tensor *t2);

/**
* \brief Subtract two Tensor-s element-wise. Save the result in tdest, free t2.
*
* \param tdest Tensor. Destination.
* \param t2 Tensor. Same Shape as tdest. Will be freed.
* \see tc_sub tc_sub_pure
*/
void tc_sub_and_free(Tensor *tdest, Tensor *t2);

/**
* \brief Subtract two Tensor-s element-wise, return a pointer to Tensor.
*
* \param t1 Tensor.
* \param t2 Tensor. Same Shape as t1.
*
* \return Tensor (pointer) with the element-wise subtraction.
*
* \see tc_sub_and_free tc_sub
*/
Tensor *tc_sub_pure(Tensor *t1, Tensor *t2);

/**
* \brief Multiply two Tensor-s element-wise, save the result in the first one.
*
* \param tdest Tensor. One of the terms of the multiplication, and also the
* destination.
* \param t2 Tensor. Same Shape as tdest.
*
* \note There is no return value. The result is saved in Tensor tdest.
* Therefore, you will lose whatever information you had in tdest.
*
* \see tc_mul_pure tc_mul_and_free
*/
void tc_mul(Tensor *tdest, Tensor *t2);

/**
* \brief Multiply two Tensor-s element-wise. Save the result in tdest, free t2.
*
* \param tdest Tensor. Destination.
* \param t2 Tensor. Same Shape as tdest. Will be freed.
* \see tc_mul tc_mul_pure
*/
void tc_mul_and_free(Tensor *tdest, Tensor *t2);

/**
* \brief Multiply two Tensor-s element-wise, return a pointer to Tensor.
*
* \param t1 Tensor.
* \param t2 Tensor. Same Shape as t1.
*
* \return Tensor (pointer) with the element-wise multiplication.
*
* \see tc_mul_and_free tc_mul
*/
Tensor *tc_mul_pure(Tensor *t1, Tensor *t2);

/**
* \brief Divide two Tensor-s element-wise, save the result in the first one.
*
* \param tdest Tensor. One of the terms of the division, and also the
* destination.
* \param t2 Tensor. Same Shape as tdest.
*
* \note There is no return value. The result is saved in Tensor tdest.
* Therefore, you will lose whatever information you had in tdest.
*
* \note For this function, division by 0 is the identity (i.e. x / 0 == x), but
* prints a warning to stderr.
*
* \see tc_div_pure tc_div_and_free
*/
void tc_div(Tensor *tdest, Tensor *t2);

/**
* \brief Divide two Tensor-s element-wise. Save the result in tdest, free t2.
*
* \param tdest Tensor. Destination.
* \param t2 Tensor. Same Shape as tdest. Will be freed.
*
* \note For this function, division by 0 is the identity (i.e. x / 0 == x), but
* prints a warning to stderr.
* \see tc_mul tc_mul_pure
*/
void tc_div_and_free(Tensor *tdest, Tensor *t2);

/**
* \brief Divide two Tensor-s element-wise, return a pointer to Tensor.
*
* \param t1 Tensor.
* \param t2 Tensor. Same Shape as t1.
*
* \return Tensor (pointer) with the element-wise multiplication.
*
* \note For this function, division by 0 is the identity (i.e. x / 0 == x), but
* prints a warning to stderr.
*
* \see tc_div_and_free tc_div
*/
Tensor *tc_div_pure(Tensor *t1, Tensor *t2);

#endif
