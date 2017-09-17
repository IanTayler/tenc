/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#ifndef TENSOR_H
#define TENSOR_H

#include <stdint.h>
#include <stdbool.h>
/**
* \file include/tensor.h
* \author Ian G. Tayler
*
* \brief Defines Tensor type and basic handlers and initializers.
*/

/**
* \brief Initialization procedure for TenC.
*
* Sets random seeds, etc.
*/
void tc_initialize();
/**
 * \brief Integer type for dimension sizes in shapes.
 */
typedef int64_t int_shape_t;
/**
 * \brief Type for Tensor shapes.
 */
typedef struct {
    int len; /**<Number of dimensions in the shape.*/
    int_shape_t *arr; /**<Array holding the size of each dimension.*/
} Shape;

/**
 * \brief Dynamically allocates a Shape.
 *
 * \param length Length of the shape.
 * \param shape_arr Array with the dimensions' size.
 *
 * \return A pointer to a Shape. Should later be deallocated with free_shape.
 */
Shape *tc_new_shape(int length, int_shape_t *shape_arr);

/**
* \brief Deep-copy a Shape.
*
* \param shape Shape.
*
* \return Shape.
*/
Shape *tc_copy_shape(Shape *shape);

/**
 * \brief Deallocates a Shape.
 *
 * \param ptr Pointer to a Shape.
 */
void tc_free_shape(Shape *ptr);
/**
 * \brief Gets the amount of values in a Tensor of a specific Shape.
 *
 * \param ptr Shape.
 *
 * \return int_shape_t holding the number of values in a Tensor that has the
 * input shape.
 */
int_shape_t tc_shape_size(Shape *shape);

/**
* \brief Compare two shapes to see if they're equal.
*
* \param s1 Shape.
* \param s2 Shape.
*
* \return true (1) if they are the same, false (0) if not.
*/
bool tc_shape_equal(Shape *s1, Shape *s2);

/**
 * \brief Type for a float tensor.
 *
 * A Tensor is simply represented as an array of floats, with functions capable
 * of accessing the right value by index, etc.
 *
 * Things to note include:
 *     - These Tensors are statically shaped (i.e. shape is known at
 *       compile-time)
 *     - They hold floats exclusively. Be careful with floating point rounding
 *       error! This library won't hold your hand with respect to that.
 */
typedef struct {
    Shape *shape; /**<Tensor's size in each dimension.*/
    float *value_array; /**<Array with the Tensor's values*/
} Tensor;

/**
 * \brief Dynamically allocates a Tensor.
 *
 * \param shape Tensor's shape.
 * \param value_array One-dimensional array with all the values.
 *
 * \return Pointer to a Tensor. Should be deallocated with free_tensor.
 */
Tensor *tc_new_tensor(Shape *shape, float *value_array);

/**
* \brief Deep-copy a Tensor.
*
* \param t Tensor.
*
* \return Tensor.
*/
Tensor *tc_copy_tensor(Tensor *t);

/**
* \brief Get a Tensor representing a shape.
*
* \param shape Shape
*
* \return Tensor
*/
Tensor *tc_shape_to_tensor(Shape *shape);

/**
 * \brief Deallocates a Tensor.
 *
 * \param ptr Pointer to a Tensor.
 */
void tc_free_tensor(Tensor *ptr);

/**
 * \brief Create a Tensor and initialize all elements to a certain value.
 *
 * \param shape Shape of the returned Tensor.
 * \param value Float that will be used to initialize all elements in the
 * Tensor.
 *
 * \return Pointer to a Tensor.
 *
 * \note You should later free the Tensor with free_tensor.
 *
 * \see tc_zeros tc_zeros_like tc_ones tc_ones_like
 */
Tensor *tc_fill(Shape *shape, float value);

/**
 * \brief Create a Tensor and initialize it to all zeros.
 *
 * \param shape Shape of the returned Tensor.
 *
 * \return Pointer to a Tensor.
 *
 * \note You should later free the Tensor with free_tensor.
 *
 * \see tc_fill tc_zeros_like tc_ones tc_ones_like
 */
Tensor *tc_zeros(Shape *shape);

/**
 * \brief Create a Tensor and initialize it to all zeros, copying the shape
 * from another Tensor.
 *
 * \param t Tensor from which to copy the shape.
 *
 * \return Pointer to a Tensor.
 *
 * \note You should later free the Tensor with free_tensor.
 *
 * \see tc_fill tc_zeros tc_ones tc_ones_like
 */
Tensor *tc_zeros_like(Tensor *t);

/**
 * \brief Create a Tensor and initialize it to all ones.
 *
 * \param shape Shape of the returned Tensor.
 *
 * \return Pointer to a Tensor.
 *
 * \note You should later free the Tensor with free_tensor.
 *
 * \see tc_fill tc_zeros tc_zeros_like tc_ones_like
 */
Tensor *tc_ones(Shape *shape);

/**
 * \brief Create a Tensor and initialize it to all ones, copying the shape
 * from another Tensor.
 *
 * \param t Tensor from which to copy the shape.
 *
 * \return Pointer to a Tensor.
 *
 * \note You should later free the Tensor with free_tensor.
 *
 * \see tc_fill tc_zeros tc_zeros_like tc_ones
 */
Tensor *tc_ones_like(Tensor *t);

/**
* \brief Create a Tensor with values drawn from a generator function.
*
* \param shape Shape.
* \param fn Function with no arguments returning a float.
*
* \note Generating a Tensor using this fucntion will be substantially slower
* than using tc_fill and similar functions. The main reason being that we don't
* parallelize this function to avoid problems with repeated results when using
* a random generator function (probably the most common use case for this
* function).
*
* \return Pointer to a Tensor.
*/
Tensor *tc_generate(Shape *shape, float (*fn)(void));

#endif
