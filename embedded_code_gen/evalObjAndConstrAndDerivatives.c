/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evalObjAndConstrAndDerivatives.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "evalObjAndConstrAndDerivatives.h"
#include "computeConstraintsAndUserJacobian_.h"
#include "cost_fct_3D_model.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int c_obj_next_next_next_next_next_
 *                const i_struct_T *d_obj_next_next_next_next_next_
 *                const k_struct_T *e_obj_next_next_next_next_next_
 *                const double x[181]
 *                double grad_workspace_data[]
 *                double Cineq_workspace_data[]
 *                int ineq0
 *                double Ceq_workspace[160]
 *                double JacIneqTrans_workspace_data[]
 *                int iJI_col
 *                int ldJI
 *                double JacEqTrans_workspace_data[]
 *                int ldJE
 *                double *fval
 *                int *status
 * Return Type  : void
 */
void evalObjAndConstrAndDerivatives(
    int c_obj_next_next_next_next_next_,
    const i_struct_T *d_obj_next_next_next_next_next_,
    const k_struct_T *e_obj_next_next_next_next_next_, const double x[181],
    double grad_workspace_data[], double Cineq_workspace_data[], int ineq0,
    double Ceq_workspace[160], double JacIneqTrans_workspace_data[],
    int iJI_col, int ldJI, double JacEqTrans_workspace_data[], int ldJE,
    double *fval, int *status)
{
  static const signed char b_iv[800] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1};
  double varargout_2[181];
  double X[176];
  double xa[176];
  double b_x[160];
  double U[44];
  double Umv[44];
  double a[40];
  double dv[20];
  double Gfuu_tmp;
  double d;
  double d1;
  double d2;
  double dx;
  double f;
  int i;
  int idx_current;
  int j;
  memset(&X[0], 0, 176U * sizeof(double));
  memset(&Umv[0], 0, 44U * sizeof(double));
  for (idx_current = 0; idx_current < 40; idx_current++) {
    dx = 0.0;
    for (j = 0; j < 20; j++) {
      dx += (double)iv[idx_current + 40 * j] * x[j + 160];
    }
    a[idx_current] = dx;
  }
  for (idx_current = 0; idx_current < 4; idx_current++) {
    for (j = 0; j < 10; j++) {
      Umv[j + 11 * idx_current] = a[idx_current + (j << 2)];
    }
  }
  memcpy(&b_x[0], &x[0], 160U * sizeof(double));
  for (idx_current = 0; idx_current < 16; idx_current++) {
    for (j = 0; j < 10; j++) {
      X[(j + 11 * idx_current) + 1] = b_x[idx_current + (j << 4)];
    }
    X[11 * idx_current] =
        e_obj_next_next_next_next_next_->runtimedata.x[idx_current];
  }
  for (i = 0; i < 4; i++) {
    Umv[11 * i + 10] = Umv[11 * i + 9];
    memcpy(&U[i * 11], &Umv[i * 11], 11U * sizeof(double));
  }
  *fval = cost_fct_3D_model(
      X, e_obj_next_next_next_next_next_->userdata.References);
  memset(&a[0], 0, 40U * sizeof(double));
  for (idx_current = 0; idx_current < 176; idx_current++) {
    dx = fabs(X[idx_current]);
    xa[idx_current] = dx;
    if (dx < 1.0) {
      xa[idx_current] = 1.0;
    }
  }
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 16; j++) {
      dx = 1.0E-6 * xa[j];
      idx_current = (i + 11 * j) + 1;
      X[idx_current] += dx;
      f = cost_fct_3D_model(
          X, e_obj_next_next_next_next_next_->userdata.References);
      X[idx_current] -= dx;
      b_x[j + (i << 4)] = (f - *fval) / dx;
    }
  }
  for (idx_current = 0; idx_current < 44; idx_current++) {
    dx = fabs(U[idx_current]);
    Umv[idx_current] = dx;
    if (dx < 1.0) {
      Umv[idx_current] = 1.0;
    }
  }
  f = cost_fct_3D_model(X,
                        e_obj_next_next_next_next_next_->userdata.References);
  dx = Umv[0];
  d = Umv[1];
  d1 = Umv[2];
  d2 = Umv[3];
  Gfuu_tmp = f - *fval;
  for (i = 0; i < 9; i++) {
    idx_current = i << 2;
    a[idx_current] = Gfuu_tmp / (1.0E-6 * dx);
    a[idx_current + 1] = Gfuu_tmp / (1.0E-6 * d);
    a[idx_current + 2] = Gfuu_tmp / (1.0E-6 * d1);
    a[idx_current + 3] = Gfuu_tmp / (1.0E-6 * d2);
  }
  Gfuu_tmp = f - *fval;
  a[36] = Gfuu_tmp / (1.0E-6 * Umv[0]);
  a[37] = Gfuu_tmp / (1.0E-6 * Umv[1]);
  a[38] = Gfuu_tmp / (1.0E-6 * Umv[2]);
  a[39] = Gfuu_tmp / (1.0E-6 * Umv[3]);
  for (idx_current = 0; idx_current < 20; idx_current++) {
    dx = 0.0;
    for (j = 0; j < 40; j++) {
      dx += (double)b_iv[idx_current + 20 * j] * a[j];
    }
    dv[idx_current] = dx;
  }
  memcpy(&varargout_2[0], &b_x[0], 160U * sizeof(double));
  memcpy(&varargout_2[160], &dv[0], 20U * sizeof(double));
  varargout_2[180] = (f - f) / (2.0 * (fmax(1.0E-6, fabs(x[180])) * 1.0E-6));
  memcpy(&grad_workspace_data[0], &varargout_2[0], 181U * sizeof(double));
  *status = 1;
  if (rtIsInf(*fval) || rtIsNaN(*fval)) {
    if (rtIsNaN(*fval)) {
      *status = -3;
    } else if (*fval < 0.0) {
      *status = -1;
    } else {
      *status = -2;
    }
  } else {
    bool allFinite;
    allFinite = true;
    idx_current = 0;
    while (allFinite && (idx_current + 1 <= 181)) {
      allFinite = ((!rtIsInf(grad_workspace_data[idx_current])) &&
                   (!rtIsNaN(grad_workspace_data[idx_current])));
      idx_current++;
    }
    if (!allFinite) {
      idx_current--;
      if (rtIsNaN(grad_workspace_data[idx_current])) {
        *status = -3;
      } else if (grad_workspace_data[idx_current] < 0.0) {
        *status = -1;
      } else {
        *status = -2;
      }
    }
  }
  if (*status == 1) {
    *status = c_computeConstraintsAndUserJaco(
        c_obj_next_next_next_next_next_, d_obj_next_next_next_next_next_, x,
        Cineq_workspace_data, ineq0, Ceq_workspace, JacIneqTrans_workspace_data,
        iJI_col, ldJI, JacEqTrans_workspace_data, ldJE);
  }
}

/*
 * File trailer for evalObjAndConstrAndDerivatives.c
 *
 * [EOF]
 */
