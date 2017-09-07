/*****************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>              *
 * This file is part of TenC.                                                *
 *                                                                           *
 * TenC  is  distributed  as  free  software under the Artistic License 2.0. *
 * You  should  have received a copy of the license together with the source *
 * files  for Markovman. It should be in the main directory, in a file named *
 * 'LICENSE'.                                                                *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "pprint.h"
#include "tensor.h"
#include "stringutils.h"

/**
* \brief Base length of short dynamically allocated strings.
*
* We don't need it to be a power of two because str_alloc_at_least handles
* efficient use of malloc.
*/
#define BASE_LEN 63

/**
* \brief Base length of long dynamically allocated strings.
*
* We don't need it to be a power of two because str_alloc_at_least handles
* efficient use of malloc.
*/
#define BASE_LONG_LEN 255

/* Copy all the values in src to dest, starting from index init */
void copy_shapearr_from(int_shape_t *dest, int_shape_t *src, int len, int init)
{
    if (init < 0)
        init = 0;
#pragma omp parallel for
    for (int i = init; i < len; i++)
        dest[i] = src[i];
}

int all_zeros(int_shape_t *shp, int len)
{
    for (int i = 0; i < len; i++) {
        if (shp[i] > 0)
            return 0;
    }
    /* If we got here, there were all zeros */
    return 1;
}

void write_element(DynStr *ds, Tensor *t, int *elempos)
{
    /* we also use BASE_LEN for this, although it isn't its original intended
    use */
    char s[BASE_LEN];
    snprintf(s, BASE_LEN - 1, "%.7g", t->value_array[*elempos]);
    str_append_str(ds, s);
    (*elempos)++;
}


char *tc_btfy(Tensor *t)
{
    DynStr *ds = str_alloc_at_least(BASE_LEN);
    int_shape_t *shp = t->shape->shape;
    int shplen = t->shape->shape_len;
    /* Get a temporary copy of the shape array which will be modified in the
    process */
    int_shape_t *tmpshp = malloc(sizeof(*tmpshp) * shplen);

    /*
        STRING-BUILDING LOOP
    */
    /* position in the tmpshp array */
    int pos = 0;
    copy_shapearr_from(tmpshp, shp, shplen, pos);
    /* position in the Tensor element array */
    int elempos = 0;
    str_append_char_no_zero(ds, '[');
    while (!all_zeros(tmpshp, shplen)) {
        if (pos < shplen - 1 && tmpshp[pos+1] <= 0) {
            /* copy the values to the tmpshp, starting from index pos */
            copy_shapearr_from(tmpshp, shp, shplen, pos+1);
        }
        for (; pos < shplen - 1; pos++) {
            str_append_char_no_zero(ds, '[');
        }
        for (int i = 0; i < tmpshp[pos]; i++) {
            if (i == 0) {
                str_append_char_no_zero(ds, ' ');
                str_append_char_no_zero(ds, ' ');
            }
            write_element(ds, t, &elempos); /* this does elempos++ */
            str_append_char_no_zero(ds, ' ');
            str_append_char_no_zero(ds, ' ');
        }
        /* set the last value to zero */
        tmpshp[pos] = 0;
        while (tmpshp[pos] <= 0 && pos > 0) {
            pos--;
            str_append_char_no_zero(ds, ']');
            tmpshp[pos]--;
        }
    }
    str_append_char(ds, ']');
    /*
        END OF STRING-BUILDING LOOP
    */

    /* We want to return a char array, not a DynStr. So we copy the char
    pointer ds->s, then free the pointer to the DynStr and finally return the
    char array */
    char *rets = ds->s;
    free(ds); /* note this isn't free_dynstr */
    return rets;
}


char *tc_long_btfy(Tensor *t)
{
    fprintf(stderr, "ERROR: tc_long_btfy not implemented.");
    return "ERROR";
}


void tc_pprint(Tensor *t)
{
    char *str = tc_btfy(t);
    printf("%s\n", str);
    free(str);
}


void tc_long_pprint(Tensor *t)
{
    char *str = tc_long_btfy(t);
    printf("%s\n", str);
    free(str);
}
