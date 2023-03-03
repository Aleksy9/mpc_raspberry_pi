/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: checkVectorNonFinite.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "checkVectorNonFinite.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double vec[160]
 * Return Type  : int
 */
int b_checkVectorNonFinite(const double vec[160])
{
  int idx_current;
  int status;
  bool allFinite;
  status = 1;
  allFinite = true;
  idx_current = 0;
  while (allFinite && (idx_current + 1 <= 160)) {
    allFinite = ((!rtIsInf(vec[idx_current])) && (!rtIsNaN(vec[idx_current])));
    idx_current++;
  }
  if (!allFinite) {
    idx_current--;
    if (rtIsNaN(vec[idx_current])) {
      status = -3;
    } else if (vec[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }
  return status;
}

/*
 * Arguments    : int N
 *                const double vec_data[]
 *                int iv0
 * Return Type  : int
 */
int checkVectorNonFinite(int N, const double vec_data[], int iv0)
{
  int idx_current;
  int idx_end;
  int status;
  bool allFinite;
  status = 1;
  allFinite = true;
  idx_current = iv0;
  idx_end = (iv0 + N) - 1;
  while (allFinite && (idx_current <= idx_end)) {
    double allFinite_tmp;
    allFinite_tmp = vec_data[idx_current - 1];
    allFinite = ((!rtIsInf(allFinite_tmp)) && (!rtIsNaN(allFinite_tmp)));
    idx_current++;
  }
  if (!allFinite) {
    idx_current -= 2;
    if (rtIsNaN(vec_data[idx_current])) {
      status = -3;
    } else if (vec_data[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }
  return status;
}

/*
 * File trailer for checkVectorNonFinite.c
 *
 * [EOF]
 */
