/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeComplError.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeComplError.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int fscales_lineq_constraint_size
 *                int fscales_cineq_constraint_size
 *                const double xCurrent[181]
 *                int mIneq
 *                const double cIneq_data[]
 *                const int finiteLB_data[]
 *                int mLB
 *                const double lb[181]
 *                const int finiteUB_data[]
 *                int mUB
 *                const double ub[181]
 *                const double lambda_data[]
 *                int iL0
 * Return Type  : double
 */
double computeComplError(int fscales_lineq_constraint_size,
                         int fscales_cineq_constraint_size,
                         const double xCurrent[181], int mIneq,
                         const double cIneq_data[], const int finiteLB_data[],
                         int mLB, const double lb[181],
                         const int finiteUB_data[], int mUB,
                         const double ub[181], const double lambda_data[],
                         int iL0)
{
  double nlpComplError;
  int idx;
  int mLinIneq;
  nlpComplError = 0.0;
  mLinIneq = fscales_lineq_constraint_size - 1;
  if ((mIneq + mLB) + mUB > 0) {
    double lbDelta;
    double lbLambda;
    int i;
    int ubOffset;
    for (idx = 0; idx <= mLinIneq; idx++) {
      lbLambda = lambda_data[(iL0 + idx) - 1];
      lbDelta = cIneq_data[idx];
      nlpComplError = fmax(nlpComplError, fmin(fabs(lbDelta * lbLambda),
                                               fmin(fabs(lbDelta), lbLambda)));
    }
    mLinIneq = (iL0 + fscales_lineq_constraint_size) - 2;
    for (idx = 0; idx < fscales_cineq_constraint_size; idx++) {
      lbDelta = cIneq_data[fscales_lineq_constraint_size + idx];
      lbLambda = lambda_data[(mLinIneq + idx) + 1];
      nlpComplError = fmax(nlpComplError, fmin(fabs(lbDelta * lbLambda),
                                               fmin(fabs(lbDelta), lbLambda)));
    }
    mLinIneq = (iL0 + mIneq) - 1;
    ubOffset = mLinIneq + mLB;
    i = (unsigned short)mLB;
    for (idx = 0; idx < i; idx++) {
      lbDelta = xCurrent[finiteLB_data[idx] - 1] - lb[finiteLB_data[idx] - 1];
      lbLambda = lambda_data[mLinIneq + idx];
      nlpComplError = fmax(nlpComplError, fmin(fabs(lbDelta * lbLambda),
                                               fmin(fabs(lbDelta), lbLambda)));
    }
    i = (unsigned short)mUB;
    for (idx = 0; idx < i; idx++) {
      lbDelta = ub[finiteUB_data[idx] - 1] - xCurrent[finiteUB_data[idx] - 1];
      lbLambda = lambda_data[ubOffset + idx];
      nlpComplError = fmax(nlpComplError, fmin(fabs(lbDelta * lbLambda),
                                               fmin(fabs(lbDelta), lbLambda)));
    }
  }
  return nlpComplError;
}

/*
 * File trailer for computeComplError.c
 *
 * [EOF]
 */
