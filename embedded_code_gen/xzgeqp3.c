/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzgeqp3.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "xzgeqp3.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double A_data[]
 *                const int A_size[2]
 *                int m
 *                int n
 *                int nfxd
 *                double tau_data[]
 * Return Type  : void
 */
void qrf(double A_data[], const int A_size[2], int m, int n, int nfxd,
         double tau_data[])
{
  double work_data[1803];
  double atmp;
  int i;
  int lda;
  int loop_ub;
  lda = A_size[0];
  loop_ub = A_size[1];
  if (loop_ub - 1 >= 0) {
    memset(&work_data[0], 0, (unsigned int)loop_ub * sizeof(double));
  }
  loop_ub = (unsigned short)nfxd;
  for (i = 0; i < loop_ub; i++) {
    double d;
    int ii;
    int mmi;
    ii = i * lda + i;
    mmi = m - i;
    if (i + 1 < m) {
      atmp = A_data[ii];
      d = xzlarfg(mmi, &atmp, A_data, ii + 2);
      tau_data[i] = d;
      A_data[ii] = atmp;
    } else {
      d = 0.0;
      tau_data[i] = 0.0;
    }
    if (i + 1 < n) {
      atmp = A_data[ii];
      A_data[ii] = 1.0;
      xzlarf(mmi, (n - i) - 1, ii + 1, d, A_data, (ii + lda) + 1, lda,
             work_data);
      A_data[ii] = atmp;
    }
  }
}

/*
 * Arguments    : double A_data[]
 *                const int A_size[2]
 *                int m
 *                int n
 *                int nfxd
 *                double tau_data[]
 *                int jpvt_data[]
 * Return Type  : void
 */
void qrpf(double A_data[], const int A_size[2], int m, int n, int nfxd,
          double tau_data[], int jpvt_data[])
{
  double vn1_data[1803];
  double vn2_data[1803];
  double work_data[1803];
  double d;
  double smax;
  int b_i;
  int i;
  int ix;
  int j;
  int k;
  int ma;
  int minmn;
  ma = A_size[0];
  if (m <= n) {
    minmn = m;
  } else {
    minmn = n;
  }
  ix = A_size[1];
  if (ix - 1 >= 0) {
    memset(&work_data[0], 0, (unsigned int)ix * sizeof(double));
  }
  ix = A_size[1];
  if (ix - 1 >= 0) {
    memset(&vn1_data[0], 0, (unsigned int)ix * sizeof(double));
  }
  ix = A_size[1];
  if (ix - 1 >= 0) {
    memset(&vn2_data[0], 0, (unsigned int)ix * sizeof(double));
  }
  i = nfxd + 1;
  for (j = i; j <= n; j++) {
    d = xnrm2(m - nfxd, A_data, (nfxd + (j - 1) * ma) + 1);
    vn1_data[j - 1] = d;
    vn2_data[j - 1] = d;
  }
  for (b_i = i; b_i <= minmn; b_i++) {
    double s;
    int ii;
    int ii_tmp;
    int ip1;
    int mmi;
    int nmi;
    int pvt;
    ip1 = b_i + 1;
    ii_tmp = (b_i - 1) * ma;
    ii = (ii_tmp + b_i) - 1;
    nmi = (n - b_i) + 1;
    mmi = m - b_i;
    if (nmi < 1) {
      ix = -2;
    } else {
      ix = -1;
      if (nmi > 1) {
        smax = fabs(vn1_data[b_i - 1]);
        for (k = 2; k <= nmi; k++) {
          s = fabs(vn1_data[(b_i + k) - 2]);
          if (s > smax) {
            ix = k - 2;
            smax = s;
          }
        }
      }
    }
    pvt = b_i + ix;
    if (pvt + 1 != b_i) {
      ix = pvt * ma;
      for (k = 0; k < m; k++) {
        int i1;
        j = ix + k;
        smax = A_data[j];
        i1 = ii_tmp + k;
        A_data[j] = A_data[i1];
        A_data[i1] = smax;
      }
      ix = jpvt_data[pvt];
      jpvt_data[pvt] = jpvt_data[b_i - 1];
      jpvt_data[b_i - 1] = ix;
      vn1_data[pvt] = vn1_data[b_i - 1];
      vn2_data[pvt] = vn2_data[b_i - 1];
    }
    if (b_i < m) {
      smax = A_data[ii];
      d = xzlarfg(mmi + 1, &smax, A_data, ii + 2);
      tau_data[b_i - 1] = d;
      A_data[ii] = smax;
    } else {
      d = 0.0;
      tau_data[b_i - 1] = 0.0;
    }
    if (b_i < n) {
      smax = A_data[ii];
      A_data[ii] = 1.0;
      xzlarf(mmi + 1, nmi - 1, ii + 1, d, A_data, (ii + ma) + 1, ma, work_data);
      A_data[ii] = smax;
    }
    for (j = ip1; j <= n; j++) {
      ix = b_i + (j - 1) * ma;
      d = vn1_data[j - 1];
      if (d != 0.0) {
        smax = fabs(A_data[ix - 1]) / d;
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }
        s = d / vn2_data[j - 1];
        s = smax * (s * s);
        if (s <= 1.4901161193847656E-8) {
          if (b_i < m) {
            d = xnrm2(mmi, A_data, ix + 1);
            vn1_data[j - 1] = d;
            vn2_data[j - 1] = d;
          } else {
            vn1_data[j - 1] = 0.0;
            vn2_data[j - 1] = 0.0;
          }
        } else {
          vn1_data[j - 1] = d * sqrt(smax);
        }
      }
    }
  }
}

/*
 * File trailer for xzgeqp3.c
 *
 * [EOF]
 */
