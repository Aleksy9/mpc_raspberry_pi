/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: partialColLDL3_.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "partialColLDL3_.h"
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
void partialColLDL3_(h_struct_T *obj, int LD_offset, int NColsRemain)
{
  int LD_diagOffset;
  int LDimSizeP1;
  int i;
  int i1;
  int i2;
  int ia;
  int iac;
  int idx;
  int ix;
  int iy0;
  int j;
  int k;
  int subRows;
  LDimSizeP1 = obj->ldm + 1;
  i = NColsRemain - 1;
  for (k = 0; k < 48; k++) {
    double y;
    subRows = (NColsRemain - k) - 1;
    LD_diagOffset = (LD_offset + LDimSizeP1 * k) - 1;
    for (idx = 0; idx <= subRows; idx++) {
      obj->workspace_ = obj->FMat.data[LD_diagOffset + idx];
    }
    for (idx = 0; idx <= i; idx++) {
      obj->workspace2_ = obj->workspace_;
    }
    idx = obj->ldm;
    y = obj->workspace2_;
    if ((NColsRemain != 0) && (k != 0)) {
      ix = LD_offset + k;
      i1 = obj->ldm * (k - 1) + 1;
      for (iac = 1; idx < 0 ? iac >= i1 : iac <= i1; iac += idx) {
        i2 = (iac + NColsRemain) - 1;
        for (ia = iac; ia <= i2; ia++) {
          y += obj->workspace_ * -obj->FMat.data[ix - 1];
        }
        ix += obj->ldm;
      }
    }
    obj->workspace2_ = y;
    for (idx = 0; idx <= i; idx++) {
      obj->workspace_ = y;
    }
    for (idx = 0; idx <= subRows; idx++) {
      obj->FMat.data[LD_diagOffset + idx] = obj->workspace_;
    }
    for (idx = 0; idx < subRows; idx++) {
      i1 = (LD_diagOffset + idx) + 1;
      obj->FMat.data[i1] /= obj->FMat.data[LD_diagOffset];
    }
  }
  for (j = 48; j <= i; j += 48) {
    int i3;
    int m;
    int subBlockSize;
    LD_diagOffset = NColsRemain - j;
    if (LD_diagOffset >= 48) {
      subBlockSize = 48;
    } else {
      subBlockSize = LD_diagOffset;
    }
    i1 = (j + subBlockSize) - 1;
    for (k = j; k <= i1; k++) {
      m = (j + subBlockSize) - k;
      iy0 = (LD_offset + LDimSizeP1 * k) - 1;
      for (idx = 0; idx < 48; idx++) {
        obj->workspace2_ =
            obj->FMat.data[((LD_offset + k) + idx * obj->ldm) - 1];
      }
      ix = k + 1;
      idx = obj->ldm;
      if (m != 0) {
        i2 = (k + obj->ldm * 47) + 1;
        for (iac = ix; idx < 0 ? iac >= i2 : iac <= i2; iac += idx) {
          i3 = (iac + m) - 1;
          for (ia = iac; ia <= i3; ia++) {
            subRows = (iy0 + ia) - iac;
            obj->FMat.data[subRows] += obj->workspace_ * -obj->workspace2_;
          }
        }
      }
    }
    if (j + subBlockSize < NColsRemain) {
      m = LD_diagOffset - subBlockSize;
      k = ((LD_offset + subBlockSize) + LDimSizeP1 * j) - 1;
      i1 = subBlockSize - 1;
      for (idx = 0; idx < 48; idx++) {
        ix = (LD_offset + j) + idx * obj->ldm;
        for (subRows = 0; subRows <= i1; subRows++) {
          obj->workspace2_ = obj->FMat.data[(ix + subRows) - 1];
        }
      }
      LD_diagOffset = obj->ldm;
      idx = obj->ldm;
      if ((m != 0) && (subBlockSize != 0)) {
        ix = k + obj->ldm * (subBlockSize - 1);
        subRows = 0;
        for (iy0 = k; idx < 0 ? iy0 >= ix : iy0 <= ix; iy0 += idx) {
          subRows++;
          i1 = subRows + LD_diagOffset * 47;
          for (iac = subRows; LD_diagOffset < 0 ? iac >= i1 : iac <= i1;
               iac += LD_diagOffset) {
            i2 = iy0 + 1;
            i3 = iy0 + m;
            for (ia = i2; ia <= i3; ia++) {
              obj->FMat.data[ia - 1] += -obj->workspace2_ * obj->workspace_;
            }
          }
        }
      }
    }
  }
}

/*
 * File trailer for partialColLDL3_.c
 *
 * [EOF]
 */
