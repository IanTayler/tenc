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

#include "minunit-ext.h"
#include "testfunctions.h"

int tests_run = 0;
char *test_running = "TEST.C";

/*
 *  TESTING THE UNIT TEST LIBRARY.
 */
char *mu_fine_test()
{
    test_running = "mu_fine_test";
    mu_assert("MinUnit isn't working properly", 1);
    return 0;
}

char *all_tests()
{
    mu_run_test(mu_fine_test);
    mu_run_test(shape_new_and_free);
    mu_run_test(tensor_new_and_free);

    return 0;
}

int main()
{
    char *mess = all_tests();
    if (mess != 0) {
        printf("Error while running \"%s\":\n%s\n", test_running, mess);
    } else {
        printf("OK\n");
    }
    printf("Ran %d tests.\n", tests_run);

    return mess != 0;
}
