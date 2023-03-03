/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: all.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "all.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const bool x[160]
 *                bool y[16]
 * Return Type  : void
 */
void all(const bool x[160], bool y[16])
{
  int i;
  int i2;
  i2 = 1;
  for (i = 0; i < 16; i++) {
    int a;
    int ix;
    bool exitg1;
    y[i] = true;
    a = i2 + 9;
    ix = i2;
    i2 += 10;
    exitg1 = false;
    while ((!exitg1) && (ix <= a)) {
      if (!x[ix - 1]) {
        y[i] = false;
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }
}

/*
 * File trailer for all.c
 *
 * [EOF]
 */
