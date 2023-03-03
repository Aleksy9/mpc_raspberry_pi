/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgeqp3.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "xgeqp3.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double A_data[]
 *                const int A_size[2]
 *                int m
 *                int n
 *                int jpvt_data[]
 *                double tau_data[]
 *                int *tau_size
 * Return Type  : void
 */
void xgeqp3(double A_data[], const int A_size[2], int m, int n, int jpvt_data[],
            double tau_data[], int *tau_size)
{
  int j;
  int k;
  int ma;
  int minmn;
  ma = A_size[0];
  minmn = A_size[0];
  *tau_size = A_size[1];
  if (minmn <= *tau_size) {
    *tau_size = minmn;
  }
  if (m <= n) {
    minmn = m;
  } else {
    minmn = n;
  }
  if (*tau_size - 1 >= 0) {
    memset(&tau_data[0], 0, (unsigned int)*tau_size * sizeof(double));
  }
  if (minmn < 1) {
    for (j = 0; j < n; j++) {
      jpvt_data[j] = j + 1;
    }
  } else {
    int nfxd;
    nfxd = 0;
    for (j = 0; j < n; j++) {
      if (jpvt_data[j] != 0) {
        nfxd++;
        if (j + 1 != nfxd) {
          int ix;
          int iy;
          ix = j * ma;
          iy = (nfxd - 1) * ma;
          for (k = 0; k < m; k++) {
            double temp;
            int i;
            int temp_tmp;
            temp_tmp = ix + k;
            temp = A_data[temp_tmp];
            i = iy + k;
            A_data[temp_tmp] = A_data[i];
            A_data[i] = temp;
          }
          jpvt_data[j] = jpvt_data[nfxd - 1];
          jpvt_data[nfxd - 1] = j + 1;
        } else {
          jpvt_data[j] = j + 1;
        }
      } else {
        jpvt_data[j] = j + 1;
      }
    }
    if (nfxd > minmn) {
      nfxd = minmn;
    }
    qrf(A_data, A_size, m, n, nfxd, tau_data);
    if (nfxd < minmn) {
      qrpf(A_data, A_size, m, n, nfxd, tau_data, jpvt_data);
    }
  }
}

/*
 * File trailer for xgeqp3.c
 *
 * [EOF]
 */
