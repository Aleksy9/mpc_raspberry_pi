/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: normal.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef NORMAL_H
#define NORMAL_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void normal(const double Hessian[32761], const double grad_data[],
            c_struct_T *TrialState, struct_T *MeritFunction,
            e_struct_T *memspace, f_struct_T *WorkingSet, g_struct_T *QRManager,
            h_struct_T *CholManager, d_struct_T *QPObjective,
            const m_struct_T *qpoptions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for normal.h
 *
 * [EOF]
 */
