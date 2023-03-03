/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeFval.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef COMPUTEFVAL_H
#define COMPUTEFVAL_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double computeFval(const d_struct_T *obj, double workspace_data[],
                   const double H[32761], const double f_data[],
                   const double x_data[]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeFval.h
 *
 * [EOF]
 */
