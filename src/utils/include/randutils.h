/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for  TenC.  It  should  be  in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#ifndef RANDUTILS_H
#define RANDUTILS_H

/**
* \file src/utils/include/randutils.h
* \brief Defines functions for random generation of numbers.
* \author Ian G. Tayler
*/

/**
* \brief Random float between two floats.
*/
float random_float_range(float min, float max);

/**
* \brief Random float between 0 and 1.
*/
float random_float();

#endif
