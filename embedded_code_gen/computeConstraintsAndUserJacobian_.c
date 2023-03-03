/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeConstraintsAndUserJacobian_.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeConstraintsAndUserJacobian_.h"
#include "checkVectorNonFinite.h"
#include "nlmpcmoveCodeGeneration.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int c_obj_next_next_next_next_next_
 *                const i_struct_T *d_obj_next_next_next_next_next_
 *                const double x[181]
 *                double Cineq_workspace_data[]
 *                int ineq0
 *                double Ceq_workspace[160]
 *                double JacIneqTrans_workspace_data[]
 *                int iJI_col
 *                int ldJI
 *                double JacEqTrans_workspace_data[]
 *                int ldJE
 * Return Type  : int
 */
int c_computeConstraintsAndUserJaco(
    int c_obj_next_next_next_next_next_,
    const i_struct_T *d_obj_next_next_next_next_next_, const double x[181],
    double Cineq_workspace_data[], int ineq0, double Ceq_workspace[160],
    double JacIneqTrans_workspace_data[], int iJI_col, int ldJI,
    double JacEqTrans_workspace_data[], int ldJE)
{
  static double varargout_3_data[57920];
  static double varargout_4[28960];
  double varargout_1_data[320];
  double varargout_2[160];
  int col;
  int col_end;
  int idx_mat;
  int row;
  int status;
  if (c_obj_next_next_next_next_next_ > 0) {
    int varargout_1_size[2];
    int varargout_3_size[2];
    c_nlmpcmoveCodeGeneration_anonF(
        d_obj_next_next_next_next_next_->x,
        d_obj_next_next_next_next_next_->OutputMin,
        d_obj_next_next_next_next_next_->OutputMax,
        d_obj_next_next_next_next_next_->Parameters[0], x, varargout_1_data,
        varargout_1_size, varargout_2, varargout_3_data, varargout_3_size,
        varargout_4);
    col = (unsigned short)c_obj_next_next_next_next_next_;
    for (row = 0; row < col; row++) {
      Cineq_workspace_data[(ineq0 + row) - 1] = varargout_1_data[row];
    }
    memcpy(&Ceq_workspace[0], &varargout_2[0], 160U * sizeof(double));
    col = varargout_3_size[0];
    for (col_end = 0; col_end < col; col_end++) {
      row = varargout_3_size[1];
      for (idx_mat = 0; idx_mat < row; idx_mat++) {
        JacIneqTrans_workspace_data[col_end +
                                    ldJI * ((iJI_col + idx_mat) - 1)] =
            varargout_3_data[col_end + varargout_3_size[0] * idx_mat];
      }
    }
    for (col_end = 0; col_end < 181; col_end++) {
      for (idx_mat = 0; idx_mat < 160; idx_mat++) {
        JacEqTrans_workspace_data[col_end + ldJE * idx_mat] =
            varargout_4[col_end + 181 * idx_mat];
      }
    }
  } else {
    int varargout_1_size[2];
    int varargout_3_size[2];
    c_nlmpcmoveCodeGeneration_anonF(
        d_obj_next_next_next_next_next_->x,
        d_obj_next_next_next_next_next_->OutputMin,
        d_obj_next_next_next_next_next_->OutputMax,
        d_obj_next_next_next_next_next_->Parameters[0], x, varargout_1_data,
        varargout_1_size, varargout_2, varargout_3_data, varargout_3_size,
        varargout_4);
    memcpy(&Ceq_workspace[0], &varargout_2[0], 160U * sizeof(double));
    for (col_end = 0; col_end < 181; col_end++) {
      for (idx_mat = 0; idx_mat < 160; idx_mat++) {
        JacEqTrans_workspace_data[col_end + ldJE * idx_mat] =
            varargout_4[col_end + 181 * idx_mat];
      }
    }
  }
  status = checkVectorNonFinite(c_obj_next_next_next_next_next_,
                                Cineq_workspace_data, ineq0);
  if (status == 1) {
    status = b_checkVectorNonFinite(Ceq_workspace);
    if (status == 1) {
      bool allFinite;
      allFinite = true;
      row = -1;
      col = iJI_col;
      col_end = (iJI_col + c_obj_next_next_next_next_next_) - 1;
      while (allFinite && (col <= col_end)) {
        row = -1;
        while (allFinite && (row + 2 <= 181)) {
          idx_mat = (row + ldJI * (col - 1)) + 1;
          allFinite = ((!rtIsInf(JacIneqTrans_workspace_data[idx_mat])) &&
                       (!rtIsNaN(JacIneqTrans_workspace_data[idx_mat])));
          row++;
        }
        col++;
      }
      if (!allFinite) {
        idx_mat = row + ldJI * (col - 2);
        if (rtIsNaN(JacIneqTrans_workspace_data[idx_mat])) {
          status = -3;
        } else if (JacIneqTrans_workspace_data[idx_mat] < 0.0) {
          status = -1;
        } else {
          status = -2;
        }
      } else {
        allFinite = true;
        row = -1;
        col = -1;
        while (allFinite && (col + 2 <= 160)) {
          row = -1;
          while (allFinite && (row + 2 <= 181)) {
            idx_mat = (row + ldJE * (col + 1)) + 1;
            allFinite = ((!rtIsInf(JacEqTrans_workspace_data[idx_mat])) &&
                         (!rtIsNaN(JacEqTrans_workspace_data[idx_mat])));
            row++;
          }
          col++;
        }
        if (!allFinite) {
          idx_mat = row + ldJE * col;
          if (rtIsNaN(JacEqTrans_workspace_data[idx_mat])) {
            status = -3;
          } else if (JacEqTrans_workspace_data[idx_mat] < 0.0) {
            status = -1;
          } else {
            status = -2;
          }
        }
      }
    }
  }
  return status;
}

/*
 * File trailer for computeConstraintsAndUserJacobian_.c
 *
 * [EOF]
 */
