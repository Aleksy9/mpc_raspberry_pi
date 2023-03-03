/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgerc.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "xgerc.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                double alpha1
 *                int ix0
 *                const double y_data[]
 *                double A_data[]
 *                int ia0
 *                int lda
 * Return Type  : void
 */
void xgerc(int m, int n, double alpha1, int ix0, const double y_data[],
           double A_data[], int ia0, int lda)
{
  int ijA;
  int j;
  if (!(alpha1 == 0.0)) {
    int jA;
    jA = ia0;
    for (j = 0; j < n; j++) {
      double temp;
      temp = y_data[j];
      if (temp != 0.0) {
        int i;
        temp *= alpha1;
        i = m + jA;
        for (ijA = jA; ijA < i; ijA++) {
          A_data[ijA - 1] += A_data[((ix0 + ijA) - jA) - 1] * temp;
        }
      }
      jA += lda;
    }
  }
}

/*
 * File trailer for xgerc.c
 *
 * [EOF]
 */
