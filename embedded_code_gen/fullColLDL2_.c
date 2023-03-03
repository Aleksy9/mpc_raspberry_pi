/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fullColLDL2_.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "fullColLDL2_.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : h_struct_T *obj
 *                int LD_offset
 *                int NColsRemain
 * Return Type  : void
 */
void fullColLDL2_(h_struct_T *obj, int LD_offset, int NColsRemain)
{
  int LDimSizeP1;
  int ijA;
  int j;
  int jA;
  int k;
  LDimSizeP1 = obj->ldm;
  for (k = 0; k < NColsRemain; k++) {
    double alpha1;
    double y;
    int LD_diagOffset;
    int i;
    int offset1;
    int subMatrixDim;
    LD_diagOffset = (LD_offset + (LDimSizeP1 + 1) * k) - 1;
    alpha1 = -1.0 / obj->FMat.data[LD_diagOffset];
    subMatrixDim = NColsRemain - k;
    offset1 = LD_diagOffset + 2;
    y = obj->workspace_;
    for (jA = 0; jA <= subMatrixDim - 2; jA++) {
      y = obj->FMat.data[(LD_diagOffset + jA) + 1];
    }
    obj->workspace_ = y;
    if (!(alpha1 == 0.0)) {
      jA = LD_diagOffset + LDimSizeP1;
      for (j = 0; j <= subMatrixDim - 2; j++) {
        if (y != 0.0) {
          double temp;
          int i1;
          temp = y * alpha1;
          i = jA + 2;
          i1 = subMatrixDim + jA;
          for (ijA = i; ijA <= i1; ijA++) {
            obj->FMat.data[ijA - 1] += y * temp;
          }
        }
        jA += obj->ldm;
      }
    }
    alpha1 = 1.0 / obj->FMat.data[LD_diagOffset];
    i = LD_diagOffset + subMatrixDim;
    for (jA = offset1; jA <= i; jA++) {
      obj->FMat.data[jA - 1] *= alpha1;
    }
  }
}

/*
 * File trailer for fullColLDL2_.c
 *
 * [EOF]
 */
