/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computePrimalFeasError.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef COMPUTEPRIMALFEASERROR_H
#define COMPUTEPRIMALFEASERROR_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double computePrimalFeasError(const double x[181], int mLinIneq,
                              int mNonlinIneq, const double cIneq_data[],
                              const double cEq[160], const int finiteLB_data[],
                              int mLB, const double lb[181],
                              const int finiteUB_data[], int mUB,
                              const double ub[181]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computePrimalFeasError.h
 *
 * [EOF]
 */
