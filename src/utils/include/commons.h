/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for  TenC.  It  should  be  in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#ifndef COMMONS_H
#define COMMONS_H

#include <stdbool.h>
/**
* \file include/commons.h
* \author Ian G. Tayler
* \brief Defines very basic macros and constants to be used throughout TenC.
*/
/**
* \brief Checks for integrity before performing operations.
*
* Setting SAFE_MODE to false (i.e. 0) will make your program much harder to
* debug but it will also make it faster, perhaps substantially so.
*/
#define SAFE_MODE true
#endif
