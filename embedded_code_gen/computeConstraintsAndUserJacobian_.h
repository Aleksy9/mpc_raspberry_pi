/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeConstraintsAndUserJacobian_.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef COMPUTECONSTRAINTSANDUSERJACOBIAN__H
#define COMPUTECONSTRAINTSANDUSERJACOBIAN__H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int c_computeConstraintsAndUserJaco(
    int c_obj_next_next_next_next_next_,
    const i_struct_T *d_obj_next_next_next_next_next_, const double x[181],
    double Cineq_workspace_data[], int ineq0, double Ceq_workspace[160],
    double JacIneqTrans_workspace_data[], int iJI_col, int ldJI,
    double JacEqTrans_workspace_data[], int ldJE);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeConstraintsAndUserJacobian_.h
 *
 * [EOF]
 */
