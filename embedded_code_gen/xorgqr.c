/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xorgqr.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "xorgqr.h"
#include "rt_nonfinite.h"
#include "xgerc.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                int k
 *                double A_data[]
 *                const int A_size[2]
 *                int lda
 *                const double tau_data[]
 * Return Type  : void
 */
void xorgqr(int m, int n, int k, double A_data[], const int A_size[2], int lda,
            const double tau_data[])
{
  double work_data[1803];
  int b_i;
  int b_k;
  int c_i;
  int ia;
  int iac;
  if (n >= 1) {
    int i;
    int itau;
    i = n - 1;
    for (b_i = k; b_i <= i; b_i++) {
      ia = b_i * lda;
      b_k = m - 1;
      memset(&A_data[ia], 0,
             (unsigned int)(((b_k + ia) - ia) + 1) * sizeof(double));
      A_data[ia + b_i] = 1.0;
    }
    itau = k - 1;
    b_i = (short)A_size[1];
    if (b_i - 1 >= 0) {
      memset(&work_data[0], 0, (unsigned int)b_i * sizeof(double));
    }
    for (c_i = k; c_i >= 1; c_i--) {
      int iaii;
      iaii = c_i + (c_i - 1) * lda;
      if (c_i < n) {
        int ic0;
        int lastc;
        int lastv;
        A_data[iaii - 1] = 1.0;
        b_i = (m - c_i) - 1;
        ic0 = iaii + lda;
        if (tau_data[itau] != 0.0) {
          bool exitg2;
          lastv = b_i + 2;
          b_i += iaii;
          while ((lastv > 0) && (A_data[b_i] == 0.0)) {
            lastv--;
            b_i--;
          }
          lastc = n - c_i;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            int exitg1;
            b_i = ic0 + (lastc - 1) * lda;
            ia = b_i;
            do {
              exitg1 = 0;
              if (ia <= (b_i + lastv) - 1) {
                if (A_data[ia - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  ia++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = 0;
        }
        if (lastv > 0) {
          if (lastc != 0) {
            if (lastc - 1 >= 0) {
              memset(&work_data[0], 0, (unsigned int)lastc * sizeof(double));
            }
            b_i = 0;
            i = ic0 + lda * (lastc - 1);
            for (iac = ic0; lda < 0 ? iac >= i : iac <= i; iac += lda) {
              double c;
              c = 0.0;
              b_k = (iac + lastv) - 1;
              for (ia = iac; ia <= b_k; ia++) {
                c += A_data[ia - 1] * A_data[((iaii + ia) - iac) - 1];
              }
              work_data[b_i] += c;
              b_i++;
            }
          }
          xgerc(lastv, lastc, -tau_data[itau], iaii, work_data, A_data, ic0,
                lda);
        }
      }
      if (c_i < m) {
        b_i = iaii + 1;
        i = (iaii + m) - c_i;
        for (b_k = b_i; b_k <= i; b_k++) {
          A_data[b_k - 1] *= -tau_data[itau];
        }
      }
      A_data[iaii - 1] = 1.0 - tau_data[itau];
      i = (unsigned short)(c_i - 1);
      for (b_i = 0; b_i < i; b_i++) {
        A_data[(iaii - b_i) - 2] = 0.0;
      }
      itau--;
    }
  }
}

/*
 * File trailer for xorgqr.c
 *
 * [EOF]
 */
