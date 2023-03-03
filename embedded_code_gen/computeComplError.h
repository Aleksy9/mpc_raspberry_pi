/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeComplError.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef COMPUTECOMPLERROR_H
#define COMPUTECOMPLERROR_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double computeComplError(int fscales_lineq_constraint_size,
                         int fscales_cineq_constraint_size,
                         const double xCurrent[181], int mIneq,
                         const double cIneq_data[], const int finiteLB_data[],
                         int mLB, const double lb[181],
                         const int finiteUB_data[], int mUB,
                         const double ub[181], const double lambda_data[],
                         int iL0);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeComplError.h
 *
 * [EOF]
 */
