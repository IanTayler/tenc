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
    float out; /**< Output */
    float (*actvf)(float); /**< Activation function */
    /**
    * Function used in backpropagation.
    * \param out Will be passed Neuron->out.
    * \param w Will be passed Neuron->w.
    */
    float (*bpf)(float, float);
} Neuron;

/**
* \brief Activates a neuron.
*
* \param n Neuron.
* \param inp Input Tensor.
*
* \return Float that's also saved in n->out.
*/
float tcnn_activate_neuron(Neuron *n, Tensor *inp);

/**
* \brief Free a Neuron and all its members.
*
* \param n Neuron.
*/
void tcnn_free_neuron(Neuron *n);

#endif
