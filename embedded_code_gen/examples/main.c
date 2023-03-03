/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "nlmpcmoveCodeGeneration.h"
#include "nlmpcmoveCodeGeneration_terminate.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static void argInit_10x16_real_T(double result[160]);

static void argInit_10x4_real_T(double result[40]);

static void argInit_16x1_real_T(double result[16]);

static double argInit_1x1_real_T(void);

static void argInit_4x1_real_T(double result[4]);

static double argInit_real_T(void);

static void argInit_struct1_T(struct1_T *result);

/* Function Definitions */
/*
 * Arguments    : double result[160]
 * Return Type  : void
 */
static void argInit_10x16_real_T(double result[160])
{
  int i;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 160; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[i] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[40]
 * Return Type  : void
 */
static void argInit_10x4_real_T(double result[40])
{
  int i;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 40; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[i] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[16]
 * Return Type  : void
 */
static void argInit_16x1_real_T(double result[16])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 16; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_1x1_real_T(void)
{
  /* Loop over the array to initialize each element. */
  return argInit_real_T();
}

/*
 * Arguments    : double result[4]
 * Return Type  : void
 */
static void argInit_4x1_real_T(double result[4])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : struct1_T *result
 * Return Type  : void
 */
static void argInit_struct1_T(struct1_T *result)
{
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  argInit_16x1_real_T(result->ref);
  result->Parameters[0] = argInit_1x1_real_T();
  argInit_10x16_real_T(result->X0);
  argInit_10x4_real_T(result->MV0);
  result->Slack0 = argInit_real_T();
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_nlmpcmoveCodeGeneration();
  /* Terminate the application.
You do not need to do this more than one time. */
  nlmpcmoveCodeGeneration_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_nlmpcmoveCodeGeneration(void)
{
  struct1_T onlinedata;
  struct2_T info;
  double dv[16];
  double dv1[4];
  double mv[4];
  /* Initialize function 'nlmpcmoveCodeGeneration' input arguments. */
  /* Initialize function input argument 'x'. */
  /* Initialize function input argument 'lastMV'. */
  /* Initialize function input argument 'onlinedata'. */
  /* Call the entry-point 'nlmpcmoveCodeGeneration'. */
  argInit_struct1_T(&onlinedata);
  argInit_16x1_real_T(dv);
  argInit_4x1_real_T(dv1);
  nlmpcmoveCodeGeneration(dv, dv1, &onlinedata, mv, &info);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
