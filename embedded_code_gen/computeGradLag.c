/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeGradLag.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeGradLag.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double workspace_data[]
 *                int ldA
 *                int nVar
 *                const double grad_data[]
 *                int mIneq
 *                const double AineqTrans_data[]
 *                const double AeqTrans_data[]
 *                const int finiteFixed_data[]
 *                int mFixed
 *                const int finiteLB_data[]
 *                int mLB
 *                const int finiteUB_data[]
 *                int mUB
 *                const double lambda_data[]
 * Return Type  : void
 */
void computeGradLag(double workspace_data[], int ldA, int nVar,
                    const double grad_data[], int mIneq,
                    const double AineqTrans_data[],
                    const double AeqTrans_data[], const int finiteFixed_data[],
                    int mFixed, const int finiteLB_data[], int mLB,
                    const int finiteUB_data[], int mUB,
                    const double lambda_data[])
{
  int i;
  int i1;
  int ia;
  int iac;
  int idx;
  int ix;
  i = (unsigned short)nVar;
  memcpy(&workspace_data[0], &grad_data[0], (unsigned int)i * sizeof(double));
  i = (unsigned short)mFixed;
  for (idx = 0; idx < i; idx++) {
    workspace_data[finiteFixed_data[idx] - 1] += lambda_data[idx];
  }
  ix = mFixed;
  i = ldA * 159 + 1;
  for (iac = 1; ldA < 0 ? iac >= i : iac <= i; iac += ldA) {
    idx = (iac + nVar) - 1;
    for (ia = iac; ia <= idx; ia++) {
      i1 = ia - iac;
      workspace_data[i1] += AeqTrans_data[ia - 1] * lambda_data[ix];
    }
    ix++;
  }
  if (mIneq != 0) {
    ix = mFixed + 160;
    i = ldA * (mIneq - 1) + 1;
    for (iac = 1; ldA < 0 ? iac >= i : iac <= i; iac += ldA) {
      idx = (iac + nVar) - 1;
      for (ia = iac; ia <= idx; ia++) {
        i1 = ia - iac;
        workspace_data[i1] += AineqTrans_data[ia - 1] * lambda_data[ix];
      }
      ix++;
    }
  }
  ix = (mFixed + mIneq) + 160;
  i = (unsigned short)mLB;
  for (idx = 0; idx < i; idx++) {
    workspace_data[finiteLB_data[idx] - 1] -= lambda_data[ix + idx];
  }
  ix += (unsigned short)mLB;
  i = (unsigned short)mUB;
  for (idx = 0; idx < i; idx++) {
    workspace_data[finiteUB_data[idx] - 1] += lambda_data[ix + idx];
  }
}

/*
 * File trailer for computeGradLag.c
 *
 * [EOF]
 */
