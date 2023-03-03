/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computePrimalFeasError.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computePrimalFeasError.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double x[181]
 *                int mLinIneq
 *                int mNonlinIneq
 *                const double cIneq_data[]
 *                const double cEq[160]
 *                const int finiteLB_data[]
 *                int mLB
 *                const double lb[181]
 *                const int finiteUB_data[]
 *                int mUB
 *                const double ub[181]
 * Return Type  : double
 */
double computePrimalFeasError(const double x[181], int mLinIneq,
                              int mNonlinIneq, const double cIneq_data[],
                              const double cEq[160], const int finiteLB_data[],
                              int mLB, const double lb[181],
                              const int finiteUB_data[], int mUB,
                              const double ub[181])
{
  double feasError;
  int idx;
  int mIneq;
  feasError = 0.0;
  mIneq = mNonlinIneq + mLinIneq;
  for (idx = 0; idx < 160; idx++) {
    feasError = fmax(feasError, fabs(cEq[idx]));
  }
  for (idx = 0; idx < mIneq; idx++) {
    feasError = fmax(feasError, cIneq_data[idx]);
  }
  mIneq = (unsigned short)mLB;
  for (idx = 0; idx < mIneq; idx++) {
    feasError =
        fmax(feasError, lb[finiteLB_data[idx] - 1] - x[finiteLB_data[idx] - 1]);
  }
  mIneq = (unsigned short)mUB;
  for (idx = 0; idx < mIneq; idx++) {
    feasError =
        fmax(feasError, x[finiteUB_data[idx] - 1] - ub[finiteUB_data[idx] - 1]);
  }
  return feasError;
}

/*
 * File trailer for computePrimalFeasError.c
 *
 * [EOF]
 */
