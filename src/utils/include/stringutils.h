/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
/**
* \file utils/include/stringutils.h
* \author Ian G. Tayler
* \brief Define utils for strings and the DynStr type.
*/
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stdint.h>

/**
* \brief Type for dynamically allocated, resizable strings.
*/
typedef struct {
    uint32_t curr; /**<Current position in the string. */
    uint32_t len; /**<Number of allocated chars. */
    char *s; /**<Actual string. */
} DynStr;

/**
* \brief Allocates memory for a DynStr with at least at_least chars.
*
* The actually allocated number of bytes will be a power of two, for an
* efficient use of malloc. If memory is more of a restriction than computation
* time, then you should consider recompiling TenC changing the function
* next_power in stringutils.c to something like an identity function.
*
* \param uint32_t at_least Minimum number of chars to allocate.
*
* \return A pointer to a DynStr which evaluates to the empty string. Should
* later be deallocated with free_dynstr.
*/
DynStr *str_alloc_at_least(uint32_t at_least);

/**
* \brief Deallocate a DynStr.
*
* \param ds Pointer to DynStr.
*/
void free_dynstr(DynStr *ds);

/**
* \brief Appends a single char to a DynStr. At the end, ds->s is a valid, zero
* terminated string.
*
* \param ds Pointer to a DynStr.
* \param c Char to append.
*
* \see str_alloc_at_least
*/
void str_append_char(DynStr *ds, char c);

/**
* \brief Appends a single char to a DynStr, without adding a zero to the end.
*
* It's used internally for (probably very small) performance gains in certain
* functions.
*
* \param ds Pointer to a DynStr.
* \param c Char to append.
*
* \see str_append_char
*/
void str_append_char_no_zero(DynStr *ds, char c);

/**
* \brief Adds a 0 to the end of a DynStr.
*
* Should only be used internally, as it isn't realloc-safe like
* str_append_char.
*
* \param ds DynStr.
* \param c char
*/
void zero_end(DynStr *ds);

/**
* \brief Convenience function to append a char array to a DynStr.
*
* \param ds Pointer to Dynstr.
* \param str char[].
* \param len Length of str.
*/
void str_append_str(DynStr *ds, char *str, int len);

/**
* \brief Convenience function to append two DynStrs.
*
* \param str1 Origin/destination DynStr.
* \param str2 DynStr to be appended.
*/
void str_append_dynstr(DynStr *str1, DynStr *str2);

#endif
