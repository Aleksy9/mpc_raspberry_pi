/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evalObjAndConstr.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef EVALOBJANDCONSTR_H
#define EVALOBJANDCONSTR_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void evalObjAndConstr(int c_obj_next_next_next_next_next_,
                      const i_struct_T *d_obj_next_next_next_next_next_,
                      const k_struct_T *e_obj_next_next_next_next_next_,
                      const double x[181], double Cineq_workspace_data[],
                      int ineq0, double Ceq_workspace[160], double *fval,
                      int *status);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for evalObjAndConstr.h
 *
 * [EOF]
 */
