/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: loadProblem.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef LOADPROBLEM_H
#define LOADPROBLEM_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void loadProblem(f_struct_T *obj, int mIneq, int mLinIneq,
                 const double Aineq_data[], int mLB, int mUB, int mFixed,
                 int mConstrMax);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for loadProblem.h
 *
 * [EOF]
 */
