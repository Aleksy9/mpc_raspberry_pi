/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: strcmp.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "strcmp.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const char a[7]
 * Return Type  : bool
 */
bool b_strcmp(const char a[7])
{
  static const char b[7] = {'f', 'm', 'i', 'n', 'c', 'o', 'n'};
  int ret;
  ret = memcmp(&a[0], &b[0], 7);
  return ret == 0;
}

/*
 * File trailer for strcmp.c
 *
 * [EOF]
 */
