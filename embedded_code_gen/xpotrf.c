/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xpotrf.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "xpotrf.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int n
 *                double A_data[]
 *                int lda
 * Return Type  : int
 */
int xpotrf(int n, double A_data[], int lda)
{
  int ia;
  int iac;
  int info;
  int j;
  int nmj;
  bool exitg1;
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j <= n - 1)) {
    double ssq;
    int idxA1j;
    int idxAjj;
    int iy;
    idxA1j = j * lda;
    idxAjj = idxA1j + j;
    ssq = 0.0;
    if (j >= 1) {
      for (nmj = 0; nmj < j; nmj++) {
        iy = idxA1j + nmj;
        ssq += A_data[iy] * A_data[iy];
      }
    }
    ssq = A_data[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = sqrt(ssq);
      A_data[idxAjj] = ssq;
      if (j + 1 < n) {
        int i;
        int ia0;
        int idxAjjp1;
        nmj = (n - j) - 2;
        ia0 = (idxA1j + lda) + 1;
        idxAjjp1 = idxAjj + lda;
        if ((j != 0) && (nmj + 1 != 0)) {
          iy = idxAjjp1;
          i = ia0 + lda * nmj;
          for (iac = ia0; lda < 0 ? iac >= i : iac <= i; iac += lda) {
            double c;
            c = 0.0;
            idxAjj = (iac + j) - 1;
            for (ia = iac; ia <= idxAjj; ia++) {
              c += A_data[ia - 1] * A_data[(idxA1j + ia) - iac];
            }
            A_data[iy] -= c;
            iy += lda;
          }
        }
        ssq = 1.0 / ssq;
        i = (idxAjjp1 + lda * nmj) + 1;
        for (nmj = idxAjjp1 + 1; lda < 0 ? nmj >= i : nmj <= i; nmj += lda) {
          A_data[nmj - 1] *= ssq;
        }
      }
      j++;
    } else {
      A_data[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }
  return info;
}

/*
 * File trailer for xpotrf.c
 *
 * [EOF]
 */
