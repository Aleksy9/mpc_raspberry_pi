/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: driver.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef DRIVER_H
#define DRIVER_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void driver(const double bineq_data[], const double lb[181],
            const double ub[181], c_struct_T *TrialState,
            struct_T *MeritFunction,
            const i_coder_internal_stickyStruct *FcnEvaluator,
            e_struct_T *memspace, f_struct_T *WorkingSet, g_struct_T *QRManager,
            h_struct_T *CholManager, d_struct_T *QPObjective,
            int fscales_lineq_constraint_size,
            int fscales_cineq_constraint_size, double Hessian[32761]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for driver.h
 *
 * [EOF]
 */
