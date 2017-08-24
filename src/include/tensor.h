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
 /**
 * \file include/tensor.h
 * \author Ian G. Tayler
 *
 * \brief Defines Tensor type and basic handlers and initializers.
 */
/**
 * \brief Integer type for dimension sizes in shapes.
 */
typedef long int int_shape_t;
/**
 * \brief Type for Tensor shapes.
 */
typedef struct {
    int shape_len; /**<Number of dimensions in the shape.*/
    int_shape_t *shape; /**<Array holding the size of each dimension.*/
} Shape;

/**
 * \brief Dynamically allocates a Shape.
 *
 * \param length Length of the shape.
 * \param shape_arr Array with the dimensions' size.
 *
 * \return A pointer to a Shape. Should later be deallocated with free_shape.
 */
Shape *new_shape(int length, int_shape_t *shape_arr);

/**
 * \brief Deallocates a Shape.
 *
 * \param ptr Pointer to a Shape.
 */
void free_shape(Shape *ptr);
/**
 * \brief Type for a float tensor.
 *
 * A Tensor is simply represented as an array of floats, with functions capable
 * of accessing the right value by index, etc.
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
Tensor *new_tensor(Shape *shape, float *value_array);

/**
 * \brief Deallocates a Tensor.
 *
 * \param ptr Pointer to a Tensor.
 */
void free_tensor(Tensor *ptr);

#endif
