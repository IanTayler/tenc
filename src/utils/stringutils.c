/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for  TenC.  It  should  be  in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <omp.h>

#include "stringutils.h"

uint32_t next_power(uint32_t n)
{
    if (n <= 0)
        n = 1;
    uint32_t log_2_len;
    n = n << 1;
    asm ("bsrl %1, %0\n"
        : "=r" (log_2_len)
        : "r" (n));
    return 1 << log_2_len;
}

void zero_end(DynStr *ds)
{
    ds->s[ds->curr] = '\0';
}

DynStr *str_alloc_at_least(uint32_t at_least)
{
    /* We want to find the next power of 2 for an efficient use of malloc. */
    int alloc_n = next_power(at_least);
    DynStr *str = malloc(sizeof(DynStr));
    str->s = malloc(sizeof(*str->s) * alloc_n);
    str->s[0] = '\0';
    str->curr = 0;
    str->len = alloc_n;
    return str;
}

void free_dynstr(DynStr *ds)
{
    free(ds->s);
    free(ds);
}

/* Convenience function. Should only be used internally */
void str_append_char_no_zero(DynStr *ds, char c)
{
    if (ds->curr >=  ds->len - 1) {
        /* We reallocate to the next_power of s->curr + 1. The '++' isn't
        actually necessary in the current implementation of next_power but it
        would be in other implementations which are recommended hacks to the
        code (e.g. next_power as the identity function) */
        ds->len =  next_power((ds->curr) + 1);
        ds->s = realloc(ds->s, sizeof(*(ds->s)) * ds->len);
    }
    ds->s[ds->curr] = c;
    ds->curr++;
}

void str_append_char(DynStr *ds, char c)
{
    str_append_char_no_zero(ds, c);
    zero_end(ds);
}

void str_append_str(DynStr *ds, char *str)
{
    for(int i = 0; str[i] != '\0'; i++) {
        str_append_char_no_zero(ds, str[i]);
    }
    zero_end(ds);
}

void str_append_dynstr(DynStr *str1, DynStr *str2)
{
    str_append_str(str1, str2->s);
}
