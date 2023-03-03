/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: deleteColMoveEnd.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "deleteColMoveEnd.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "xrotg.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : g_struct_T *obj
 *                int idx
 * Return Type  : void
 */
void deleteColMoveEnd(g_struct_T *obj, int idx)
{
  double c;
  double s;
  double temp;
  int b_k;
  int i;
  int k;
  if (obj->usedPivoting) {
    i = 1;
    while ((i <= obj->ncols) && (obj->jpvt.data[i - 1] != idx)) {
      i++;
    }
    idx = i;
  }
  if (idx >= obj->ncols) {
    obj->ncols--;
  } else {
    int b_i;
    int ix;
    obj->jpvt.data[idx - 1] = obj->jpvt.data[obj->ncols - 1];
    b_i = obj->minRowCol;
    for (k = 0; k < b_i; k++) {
      obj->QR.data[k + obj->ldq * (idx - 1)] =
          obj->QR.data[k + obj->ldq * (obj->ncols - 1)];
    }
    obj->ncols--;
    ix = obj->mrows;
    i = obj->ncols;
    if (ix <= i) {
      i = ix;
    }
    obj->minRowCol = i;
    if (idx < obj->mrows) {
      int b_temp_tmp;
      int endIdx;
      int idxRotGCol;
      int n;
      int temp_tmp;
      ix = obj->mrows - 1;
      endIdx = obj->ncols;
      if (ix <= endIdx) {
        endIdx = ix;
      }
      k = endIdx;
      idxRotGCol = obj->ldq * (idx - 1);
      while (k >= idx) {
        b_i = k + idxRotGCol;
        temp = obj->QR.data[b_i];
        xrotg(&obj->QR.data[(k + idxRotGCol) - 1], &temp, &c, &s);
        obj->QR.data[b_i] = temp;
        obj->QR.data[k + obj->ldq * (k - 1)] = 0.0;
        i = k + obj->ldq * idx;
        n = obj->ncols - idx;
        if (n >= 1) {
          ix = i - 1;
          for (b_k = 0; b_k < n; b_k++) {
            temp = c * obj->QR.data[ix] + s * obj->QR.data[i];
            obj->QR.data[i] = c * obj->QR.data[i] - s * obj->QR.data[ix];
            obj->QR.data[ix] = temp;
            i += obj->ldq;
            ix += obj->ldq;
          }
        }
        b_i = obj->ldq * (k - 1);
        i = obj->ldq + b_i;
        n = obj->mrows;
        for (b_k = 0; b_k < n; b_k++) {
          temp_tmp = i + b_k;
          b_temp_tmp = b_i + b_k;
          temp = c * obj->Q.data[b_temp_tmp] + s * obj->Q.data[temp_tmp];
          obj->Q.data[temp_tmp] =
              c * obj->Q.data[temp_tmp] - s * obj->Q.data[b_temp_tmp];
          obj->Q.data[b_temp_tmp] = temp;
        }
        k--;
      }
      b_i = idx + 1;
      for (k = b_i; k <= endIdx; k++) {
        i = obj->ldq * (k - 1);
        ix = k + i;
        temp = obj->QR.data[ix];
        xrotg(&obj->QR.data[(k + i) - 1], &temp, &c, &s);
        obj->QR.data[ix] = temp;
        i = k * (obj->ldq + 1);
        n = obj->ncols - k;
        if (n >= 1) {
          ix = i - 1;
          for (b_k = 0; b_k < n; b_k++) {
            temp = c * obj->QR.data[ix] + s * obj->QR.data[i];
            obj->QR.data[i] = c * obj->QR.data[i] - s * obj->QR.data[ix];
            obj->QR.data[ix] = temp;
            i += obj->ldq;
            ix += obj->ldq;
          }
        }
        ix = obj->ldq * (k - 1);
        i = obj->ldq + ix;
        n = obj->mrows;
        for (b_k = 0; b_k < n; b_k++) {
          temp_tmp = i + b_k;
          b_temp_tmp = ix + b_k;
          temp = c * obj->Q.data[b_temp_tmp] + s * obj->Q.data[temp_tmp];
          obj->Q.data[temp_tmp] =
              c * obj->Q.data[temp_tmp] - s * obj->Q.data[b_temp_tmp];
          obj->Q.data[b_temp_tmp] = temp;
        }
      }
    }
  }
}

/*
 * File trailer for deleteColMoveEnd.c
 *
 * [EOF]
 */
