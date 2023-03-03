/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: updateWorkingSetForNewQP.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef UPDATEWORKINGSETFORNEWQP_H
#define UPDATEWORKINGSETFORNEWQP_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void updateWorkingSetForNewQP(const double xk[181], f_struct_T *WorkingSet,
                              int mIneq, int mNonlinIneq,
                              const double cIneq_data[], const double cEq[160],
                              int mLB, const double lb[181], int mUB,
                              const double ub[181], int mFixed);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for updateWorkingSetForNewQP.h
 *
 * [EOF]
 */
