/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeFval.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeFval.h"
#include "linearForm_.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const d_struct_T *obj
 *                double workspace_data[]
 *                const double H[32761]
 *                const double f_data[]
 *                const double x_data[]
 * Return Type  : double
 */
double computeFval(const d_struct_T *obj, double workspace_data[],
                   const double H[32761], const double f_data[],
                   const double x_data[])
{
  double val;
  int idx;
  int k;
  switch (obj->objtype) {
  case 5:
    val = obj->gammaScalar * x_data[obj->nvar - 1];
    break;
  case 3: {
    linearForm_(obj->hasLinear, obj->nvar, workspace_data, H, f_data, x_data);
    val = 0.0;
    if (obj->nvar >= 1) {
      int i;
      i = (unsigned short)obj->nvar;
      for (k = 0; k < i; k++) {
        val += x_data[k] * workspace_data[k];
      }
    }
  } break;
  default: {
    int i;
    linearForm_(obj->hasLinear, obj->nvar, workspace_data, H, f_data, x_data);
    i = obj->nvar + 1;
    k = obj->maxVar - 1;
    for (idx = i; idx <= k; idx++) {
      workspace_data[idx - 1] = 0.5 * obj->beta * x_data[idx - 1] + obj->rho;
    }
    val = 0.0;
    if (k >= 1) {
      i = (unsigned short)k;
      for (k = 0; k < i; k++) {
        val += x_data[k] * workspace_data[k];
      }
    }
  } break;
  }
  return val;
}

/*
 * File trailer for computeFval.c
 *
 * [EOF]
 */
