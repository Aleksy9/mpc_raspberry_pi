/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: linearForm_.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "linearForm_.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : bool obj_hasLinear
 *                int obj_nvar
 *                double workspace_data[]
 *                const double H[32761]
 *                const double f_data[]
 *                const double x_data[]
 * Return Type  : void
 */
void linearForm_(bool obj_hasLinear, int obj_nvar, double workspace_data[],
                 const double H[32761], const double f_data[],
                 const double x_data[])
{
  int beta1;
  int ia;
  int iac;
  beta1 = 0;
  if (obj_hasLinear) {
    beta1 = (unsigned short)obj_nvar;
    if (beta1 - 1 >= 0) {
      memcpy(&workspace_data[0], &f_data[0],
             (unsigned int)beta1 * sizeof(double));
    }
    beta1 = 1;
  }
  if (obj_nvar != 0) {
    int ix;
    if (beta1 != 1) {
      beta1 = (unsigned short)obj_nvar;
      memset(&workspace_data[0], 0, (unsigned int)beta1 * sizeof(double));
    }
    ix = 0;
    beta1 = obj_nvar * (obj_nvar - 1) + 1;
    for (iac = 1; obj_nvar < 0 ? iac >= beta1 : iac <= beta1; iac += obj_nvar) {
      double c;
      int i;
      c = 0.5 * x_data[ix];
      i = (iac + obj_nvar) - 1;
      for (ia = iac; ia <= i; ia++) {
        int i1;
        i1 = ia - iac;
        workspace_data[i1] += H[ia - 1] * c;
      }
      ix++;
    }
  }
}

/*
 * File trailer for linearForm_.c
 *
 * [EOF]
 */
