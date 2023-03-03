/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeFval_ReuseHx.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeFval_ReuseHx.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const d_struct_T *obj
 *                double workspace_data[]
 *                const double f_data[]
 *                const double x_data[]
 * Return Type  : double
 */
double computeFval_ReuseHx(const d_struct_T *obj, double workspace_data[],
                           const double f_data[], const double x_data[])
{
  double val;
  int k;
  switch (obj->objtype) {
  case 5:
    val = obj->gammaScalar * x_data[obj->nvar - 1];
    break;
  case 3: {
    if (obj->hasLinear) {
      int i;
      i = (unsigned short)obj->nvar;
      for (k = 0; k < i; k++) {
        workspace_data[k] = 0.5 * obj->Hx.data[k] + f_data[k];
      }
      val = 0.0;
      if (obj->nvar >= 1) {
        for (k = 0; k < i; k++) {
          val += x_data[k] * workspace_data[k];
        }
      }
    } else {
      val = 0.0;
      if (obj->nvar >= 1) {
        int i;
        i = (unsigned short)obj->nvar;
        for (k = 0; k < i; k++) {
          val += x_data[k] * obj->Hx.data[k];
        }
      }
      val *= 0.5;
    }
  } break;
  default: {
    int maxRegVar_tmp;
    maxRegVar_tmp = obj->maxVar - 1;
    if (obj->hasLinear) {
      int i;
      i = (unsigned short)obj->nvar;
      if (i - 1 >= 0) {
        memcpy(&workspace_data[0], &f_data[0],
               (unsigned int)i * sizeof(double));
      }
      i = obj->maxVar - obj->nvar;
      for (k = 0; k <= i - 2; k++) {
        workspace_data[obj->nvar + k] = obj->rho;
      }
      i = (unsigned short)(obj->maxVar - 1);
      for (k = 0; k < i; k++) {
        workspace_data[k] += 0.5 * obj->Hx.data[k];
      }
      val = 0.0;
      if (maxRegVar_tmp >= 1) {
        for (k = 0; k < i; k++) {
          val += x_data[k] * workspace_data[k];
        }
      }
    } else {
      int i;
      val = 0.0;
      if (maxRegVar_tmp >= 1) {
        i = (unsigned short)maxRegVar_tmp;
        for (k = 0; k < i; k++) {
          val += x_data[k] * obj->Hx.data[k];
        }
      }
      val *= 0.5;
      i = obj->nvar + 1;
      for (k = i; k <= maxRegVar_tmp; k++) {
        val += x_data[k - 1] * obj->rho;
      }
    }
  } break;
  }
  return val;
}

/*
 * File trailer for computeFval_ReuseHx.c
 *
 * [EOF]
 */
