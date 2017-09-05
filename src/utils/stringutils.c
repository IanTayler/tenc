/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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

void zero_end(DynStr *s)
{
    s->s[s->curr] = '\0';
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

/* Convenience function. Only used internally */
void str_append_char_no_zero(DynStr *s, char c)
{
    if (s->curr >=  s->len) {
        /* We reallocate to the next_power of s->curr + 1. The '++' isn't
        actually necessary in the current implementation of next_power but it
        would be in other implementations which are recommended hacks to the
        code (e.g. next_power as the identity function) */
        s->s = realloc(s->s, sizeof(*(s->s)) * next_power(s->curr++));
    }
    s->s[s->curr] = c;
    s->curr++;
}

void str_append_char(DynStr *s, char c)
{
    str_append_char_no_zero(s, c);
    zero_end(s);
}

void str_append_str(DynStr *s, char *str)
{
    for(int i = 0; str[i] != '\0'; i++) {
        str_append_char_no_zero(s, str[i]);
    }
    zero_end(s);
}

void str_append_dynstr(DynStr *str1, DynStr *str2)
{
    str_append_str(str1, str2->s);
}
