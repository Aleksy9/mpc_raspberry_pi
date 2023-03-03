/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fmincon.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef FMINCON_H
#define FMINCON_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void fmincon(const i_struct_T *fun_workspace_runtimedata,
             const j_struct_T *fun_workspace_userdata, const double x0[181],
             const double Aineq_data[], const double bineq_data[],
             int bineq_size, const double lb[181], const double ub[181],
             const i_struct_T *nonlcon_workspace_runtimedata,
             const j_struct_T *nonlcon_workspace_userdata, double x[181],
             double *fval, double *exitflag, l_struct_T *output);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for fmincon.h
 *
 * [EOF]
 */
