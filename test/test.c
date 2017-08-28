#include <stdio.h>

#include <minunit-ext.h>

 int tests_run = 0;

/*
 *  TESTING THE UNIT TEST LIBRARY.
 */
char *mu_fine_test()
{
    mu_assert("MinUnit isn't working properly", 1);
    return 0;
}

char *all_tests()
{
    mu_run_test(mu_fine_test);

    return 0;
}

int main()
{
    char *mess = all_tests();
    if (mess != 0) {
        printf("ERROR: %s\n", mess);
    } else {
        printf("OK\n");
    }
    printf("Ran %d tests.\n", tests_run);

    return mess != 0;
}
