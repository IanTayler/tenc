/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for  TenC.  It  should  be  in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#ifndef NN_H
#define NN_H

#include "tensor.h"

/**
* \file include/nn.h
* \author Ian G. Tayler
* \brief Defines neural net-related types and functions.
*/

/**
* \brief Neuron for neural nets.
*/
typedef struct {
    Tensor *w; /**< Weights */
    float b; /**< Bias */
} Neuron;

/**
* \brief Free a Neuron and all its members.
*
* \param n Neuron.
*/
void tcnn_free_neuron(Neuron *n);

/**
* \brief Type for Layers.
*/
typedef struct {
    Shape *input_shape; /**< Input shape */
    int_shape_t size; /**< Number of Neurons */
    Neuron **neurons; /**< Array of Neurons */
    Tensor *out; /**< Tensor with the outputs for each Neuron */
    float (*actvf)(float); /**< Activation function */
    /**
    * Function used in backpropagation.
    *
    * Should be the differentiation of the activation function.
    */
    float (*bpf)(float);
} Layer;

/**
* \brief Deallocate a Layer.
*
* \param l Layer.
*/
void tcnn_free_layer(Layer *l);

/**
* \brief Create a network Layer with a ReLU function as nonlinearity.
*
* \param in_shape Input Shape.
* \param out_shape Output Shape. Determines the amount of Neurons.
*
* \return Layer.
*/
Layer *tcnn_relu_layer(Shape *in_shape, Shape *out_shape);

/**
* \brief Create a network Layer with a ReLU6 function as nonlinearity.
*
* \param in_shape Input Shape.
* \param out_shape Output Shape. Determines the amount of Neurons.
*
* \return Layer.
*/
Layer *tcnn_relu6_layer(Shape *in_shape, Shape *out_shape);

/**
* \brief Create a network Layer with tanh as nonlinearity.
*
* \param in_shape Input Shape.
* \param out_shape Output Shape. Determines the amount of Neurons.
*
* \return Layer.
*/
Layer *tcnn_tanh_layer(Shape *in_shape, Shape *out_shape);

/**
* \brief Create a network Layer with a sigmoid function as nonlinearity.
*
* \param in_shape Input Shape.
* \param out_shape Output Shape. Determines the amount of Neurons.
*
* \return Layer.
*/
Layer *tcnn_sigmoid_layer(Shape *in_shape, Shape *out_shape);

/**
* \brief Create a Layer with custom activation function and weight initializer.
*
* \param in_shape Input Shape.
* \param out_shape Output Shape.
* \param actvf Pointer to activation function.
* \param bpf Pointer to backpropagation function. (Differentiation of actvf.)
* \param init Pointer to initialization function for weight Tensors.
*
* \return You should later free this Layer with tcnn_free_layer.
*
* \return Layer.
*/
Layer *tcnn_custom_layer(Shape *in_shape, Shape *out_shape,
                         float (*actvf)(float), float (*bpf)(float),
                         float (*init)(void));
/**
* \brief Type for networks.
*/
typedef struct _network {
    int pos; /**< Current position in the Layer array */
    int size; /**< Number of Layer-s */
    Layer **layers; /**< Array of Layer-s */
    float (*loss)(struct _network *n); /**< Loss function */
} Network;

#endif
