/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: saveJacobian.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "saveJacobian.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : c_struct_T *obj
 *                int nVar
 *                int mIneq
 *                const double JacCineqTrans_data[]
 *                int ineqCol0
 *                const double JacCeqTrans_data[]
 *                int ldJ
 * Return Type  : void
 */
void saveJacobian(c_struct_T *obj, int nVar, int mIneq,
                  const double JacCineqTrans_data[], int ineqCol0,
                  const double JacCeqTrans_data[], int ldJ)
{
  static double y_data[3250809];
  int i;
  int iCol;
  int iCol_old;
  int idx_col;
  int k;
  iCol = ldJ * (ineqCol0 - 1);
  iCol_old = -1;
  i = mIneq - ineqCol0;
  for (idx_col = 0; idx_col <= i; idx_col++) {
    int loop_ub;
    int y_size_idx_0;
    int y_size_idx_1;
    y_size_idx_0 = obj->JacCineqTrans_old.size[0];
    y_size_idx_1 = obj->JacCineqTrans_old.size[1];
    loop_ub = y_size_idx_0 * y_size_idx_1;
    if (loop_ub - 1 >= 0) {
      memcpy(&y_data[0], &obj->JacCineqTrans_old.data[0],
             (unsigned int)loop_ub * sizeof(double));
    }
    loop_ub = (unsigned short)nVar;
    for (k = 0; k < loop_ub; k++) {
      y_data[(iCol_old + k) + 1] = JacCineqTrans_data[iCol + k];
    }
    obj->JacCineqTrans_old.size[0] = y_size_idx_0;
    obj->JacCineqTrans_old.size[1] = y_size_idx_1;
    loop_ub = y_size_idx_0 * y_size_idx_1;
    if (loop_ub - 1 >= 0) {
      memcpy(&obj->JacCineqTrans_old.data[0], &y_data[0],
             (unsigned int)loop_ub * sizeof(double));
    }
    iCol += ldJ;
    iCol_old += ldJ;
  }
  iCol = -1;
  iCol_old = -1;
  i = (unsigned short)nVar;
  for (idx_col = 0; idx_col < 160; idx_col++) {
    for (k = 0; k < i; k++) {
      obj->JacCeqTrans_old.data[(iCol_old + k) + 1] =
          JacCeqTrans_data[(iCol + k) + 1];
    }
    iCol += ldJ;
    iCol_old += ldJ;
  }
}

/*
 * File trailer for saveJacobian.c
 *
 * [EOF]
 */
