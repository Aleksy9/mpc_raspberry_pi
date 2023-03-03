/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgemm.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "xgemm.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                int k
 *                const double A_data[]
 *                int ia0
 *                int lda
 *                const double B_data[]
 *                int ldb
 *                double C_data[]
 *                int ldc
 * Return Type  : void
 */
void b_xgemm(int m, int n, int k, const double A_data[], int ia0, int lda,
             const double B_data[], int ldb, double C_data[], int ldc)
{
  int cr;
  int ic;
  int w;
  if ((m != 0) && (n != 0)) {
    int br;
    int i;
    int i1;
    int lastColC;
    lastColC = ldc * (n - 1);
    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      i = cr + 1;
      i1 = cr + m;
      if (i <= i1) {
        memset(&C_data[i + -1], 0,
               (unsigned int)((i1 - i) + 1) * sizeof(double));
      }
    }
    br = -1;
    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      int ar;
      ar = ia0;
      i = cr + 1;
      i1 = cr + m;
      for (ic = i; ic <= i1; ic++) {
        double temp;
        temp = 0.0;
        for (w = 0; w < k; w++) {
          temp += A_data[(w + ar) - 1] * B_data[(w + br) + 1];
        }
        C_data[ic - 1] += temp;
        ar += lda;
      }
      br += ldb;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                int k
 *                const double A[32761]
 *                int lda
 *                const double B_data[]
 *                int ib0
 *                int ldb
 *                double C_data[]
 *                int ldc
 * Return Type  : void
 */
void xgemm(int m, int n, int k, const double A[32761], int lda,
           const double B_data[], int ib0, int ldb, double C_data[], int ldc)
{
  int cr;
  int ib;
  int ic;
  if ((m != 0) && (n != 0)) {
    int br;
    int i;
    int i1;
    int lastColC;
    br = ib0;
    lastColC = ldc * (n - 1);
    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      i = cr + 1;
      i1 = cr + m;
      if (i <= i1) {
        memset(&C_data[i + -1], 0,
               (unsigned int)((i1 - i) + 1) * sizeof(double));
      }
    }
    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      int ar;
      ar = -1;
      i = br + k;
      for (ib = br; ib < i; ib++) {
        int i2;
        i1 = cr + 1;
        i2 = cr + m;
        for (ic = i1; ic <= i2; ic++) {
          C_data[ic - 1] += B_data[ib - 1] * A[(ar + ic) - cr];
        }
        ar += lda;
      }
      br += ldb;
    }
  }
}

/*
 * File trailer for xgemm.c
 *
 * [EOF]
 */
