/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: factorQR.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "factorQR.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : g_struct_T *obj
 *                const double A_data[]
 *                int mrows
 *                int ncols
 *                int ldA
 * Return Type  : void
 */
void factorQR(g_struct_T *obj, const double A_data[], int mrows, int ncols,
              int ldA)
{
  double tau_data[1803];
  int i;
  int idx;
  int ix0;
  int k;
  int minmana;
  bool guard1 = false;
  i = mrows * ncols;
  guard1 = false;
  if (i > 0) {
    for (idx = 0; idx < ncols; idx++) {
      ix0 = ldA * idx;
      minmana = obj->ldq * idx;
      i = (unsigned short)mrows;
      for (k = 0; k < i; k++) {
        obj->QR.data[minmana + k] = A_data[ix0 + k];
      }
    }
    guard1 = true;
  } else if (i == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }
  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt.data[idx] = idx + 1;
    }
    if (mrows <= ncols) {
      i = mrows;
    } else {
      i = ncols;
    }
    obj->minRowCol = i;
    ix0 = obj->QR.size[0];
    minmana = obj->QR.size[1];
    if (ix0 <= minmana) {
      minmana = ix0;
    }
    if (minmana - 1 >= 0) {
      memset(&tau_data[0], 0, (unsigned int)minmana * sizeof(double));
    }
    if (i >= 1) {
      qrf(obj->QR.data, obj->QR.size, mrows, ncols, i, tau_data);
    }
    obj->tau.size[0] = minmana;
    if (minmana - 1 >= 0) {
      memcpy(&obj->tau.data[0], &tau_data[0],
             (unsigned int)minmana * sizeof(double));
    }
  }
}

/*
 * File trailer for factorQR.c
 *
 * [EOF]
 */
