/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgemv.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "xgemv.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                const double A_data[]
 *                int lda
 *                const double x_data[]
 *                double y_data[]
 * Return Type  : void
 */
void b_xgemv(int m, int n, const double A_data[], int lda,
             const double x_data[], double y_data[])
{
  int ia;
  int iac;
  int iy;
  if (n != 0) {
    int i;
    i = (unsigned short)n;
    for (iy = 0; iy < i; iy++) {
      y_data[iy] = -y_data[iy];
    }
    iy = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      double c;
      int i1;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A_data[ia - 1] * x_data[ia - iac];
      }
      y_data[iy] += c;
      iy++;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                const double A_data[]
 *                int lda
 *                const double x_data[]
 *                int ix0
 *                double y_data[]
 * Return Type  : void
 */
void c_xgemv(int m, int n, const double A_data[], int lda,
             const double x_data[], int ix0, double y_data[])
{
  int ia;
  int iac;
  int iy;
  if (n != 0) {
    int i;
    i = (unsigned short)n;
    for (iy = 0; iy < i; iy++) {
      y_data[iy] = -y_data[iy];
    }
    iy = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      double c;
      int i1;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A_data[ia - 1] * x_data[((ix0 + ia) - iac) - 1];
      }
      y_data[iy] += c;
      iy++;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                const double A[32761]
 *                int lda
 *                const double x_data[]
 *                double y_data[]
 * Return Type  : void
 */
void d_xgemv(int m, int n, const double A[32761], int lda,
             const double x_data[], double y_data[])
{
  int ia;
  int iac;
  if ((m != 0) && (n != 0)) {
    int i;
    int ix;
    i = (unsigned short)m;
    memset(&y_data[0], 0, (unsigned int)i * sizeof(double));
    ix = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      int i1;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        int i2;
        i2 = ia - iac;
        y_data[i2] += A[ia - 1] * x_data[ix];
      }
      ix++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double A_data[]
 *                int lda
 *                const double x_data[]
 *                double y_data[]
 * Return Type  : void
 */
void e_xgemv(int n, const double A_data[], int lda, const double x_data[],
             double y_data[])
{
  int ia;
  int iac;
  int iy;
  if (n != 0) {
    int i;
    i = (unsigned short)n;
    for (iy = 0; iy < i; iy++) {
      y_data[iy] = -y_data[iy];
    }
    iy = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      double c;
      int i1;
      c = 0.0;
      i1 = iac + 180;
      for (ia = iac; ia <= i1; ia++) {
        c += A_data[ia - 1] * x_data[ia - iac];
      }
      y_data[iy] += c;
      iy++;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                const double A_data[]
 *                int lda
 *                const double x_data[]
 *                double y_data[]
 * Return Type  : void
 */
void xgemv(int m, int n, const double A_data[], int lda, const double x_data[],
           double y_data[])
{
  int ia;
  int iac;
  if (m != 0) {
    int i;
    int iy;
    memset(&y_data[0], 0, (unsigned int)n * sizeof(double));
    iy = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      double c;
      int i1;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A_data[ia - 1] * x_data[ia - iac];
      }
      y_data[iy] += c;
      iy++;
    }
  }
}

/*
 * File trailer for xgemv.c
 *
 * [EOF]
 */
