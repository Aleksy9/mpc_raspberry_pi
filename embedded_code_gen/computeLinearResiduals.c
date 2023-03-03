/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeLinearResiduals.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeLinearResiduals.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double x[181]
 *                int nVar
 *                double workspaceIneq_data[]
 *                const int *workspaceIneq_size
 *                int mLinIneq
 *                const double AineqT_data[]
 *                const double bineq_data[]
 *                int ldAi
 * Return Type  : void
 */
void computeLinearResiduals(const double x[181], int nVar,
                            double workspaceIneq_data[],
                            const int *workspaceIneq_size, int mLinIneq,
                            const double AineqT_data[],
                            const double bineq_data[], int ldAi)
{
  double y_data[1803];
  int ia;
  int iac;
  int iy;
  if (mLinIneq > 0) {
    int i;
    int y_size;
    y_size = *workspaceIneq_size;
    if (y_size - 1 >= 0) {
      memcpy(&y_data[0], &workspaceIneq_data[0],
             (unsigned int)y_size * sizeof(double));
    }
    i = (unsigned short)mLinIneq;
    if (i - 1 >= 0) {
      memcpy(&y_data[0], &bineq_data[0], (unsigned int)i * sizeof(double));
    }
    if (y_size - 1 >= 0) {
      memcpy(&workspaceIneq_data[0], &y_data[0],
             (unsigned int)y_size * sizeof(double));
    }
    for (iy = 0; iy < i; iy++) {
      workspaceIneq_data[iy] = -workspaceIneq_data[iy];
    }
    iy = 0;
    i = ldAi * (mLinIneq - 1) + 1;
    for (iac = 1; ldAi < 0 ? iac >= i : iac <= i; iac += ldAi) {
      double c;
      c = 0.0;
      y_size = (iac + nVar) - 1;
      for (ia = iac; ia <= y_size; ia++) {
        c += AineqT_data[ia - 1] * x[ia - iac];
      }
      workspaceIneq_data[iy] += c;
      iy++;
    }
  }
}

/*
 * File trailer for computeLinearResiduals.c
 *
 * [EOF]
 */
