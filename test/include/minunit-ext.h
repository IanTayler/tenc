/*********************************************************
 *                     minunit-ext.h                     *
 * DISTRIBUTE FREELY AS IF IN IN THE PUBLIC DOMAIN, WITH *
 * THE UNDERSTANDING  THAT IT COMES  WITH  ABSOLUTELY NO *
 * WARRANTY.                                             *
 *********************************************************/
#ifndef EXP_MINUINT_EXT_H
#define EXP_MINUINT_EXT_H
/** \file: test/minunit-ext.h
 * \author Jera Design and Ian G. Tayler
 *
 * \brief A very minimal unit test library.
 *
 * \see http://www.jera.com/techinfo/jtns/jtn002.html
 */

/**
 * \brief Macro to assert equality in a unit test.
 *
 * This macro checks whether 'test' is a true value. If it is, then
 * the macro does nothing. Otherwise, it will pass a message as the
 * return value of the function in which the macro will be expanded.
 *
 * \param message This message will be the return value of whichever
 * function implements mu_assert. It should be a message to be sent
 * if the assertion fails.
 *
 * \param test This is the value being asserted. It should evaluate
 * to a true value in successful tests.
 *
 * \note MinUnit macro.
 */
 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)

/**
 * \brief Macro to run a test.
 *
 * This macro is used to run a 'test' function, which should return
 * 0 if everything is alright. This macro should be included in functions
 * with a *char return type.
 * \param test A pointer to a function that resturns 0 if everything is
 * alright and a message (*char) if there's an error.
 *
 * \note MinUnit macro.
 */
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)

/**
 * \brief Macro to assert equality in a unit test, freeing a pointer.
 *
 * This macro behaves very similarly to #mu_assert(), the main
 * difference being that this macro frees a pointer passed as the
 * first argument of the macro before returning.
 *
 *
 * \param message This message will be the return value of whichever
 * function implements mu_assert. It should be a message to be sent
 * if the assertion fails.
 *
 * \param test This is the value being asserted. It should evaluate
 * to a true value in successful tests.
 *
 * \param pointer This pointer will be freed before returning if the
 * test fails.
 *
 * \note This macro was defined by Ian Tayler in 2017 and doesn't
 * belong to MinUnit
 */
#define mu_assert_freeing(message, test, pointer) do { if (!(test)) { \
    free(pointer); return message; } } while (0)

/**
 * \brief Macro to assert equality in a unit test, running a block if the test
 * fails.
 *
 * Like #mu_assert_freeing(), but running a full block of code instead
 * of just freeing a pointer before returning.
 *
 * \note This macro was defined by Ian Tayler in 2017 and doesn't
 * belong to MinUnit
 */
#define mu_assert_running(message, test, block) do { if (!(test)) { block; \
    return message; } } while (0)

/** \var int tests_run
 * \brief Global set to the amount of tests that ran.
 *
 * This variable gets increased when mu_run_test runs, and it should
 * hold the amount of tests ran at the end of the test program.
 * \see mu_run_test
 */
 extern int tests_run;

 #endif
