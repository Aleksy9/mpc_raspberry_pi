/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzgeqp3.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef XZGEQP3_H
#define XZGEQP3_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void qrf(double A_data[], const int A_size[2], int m, int n, int nfxd,
         double tau_data[]);

void qrpf(double A_data[], const int A_size[2], int m, int n, int nfxd,
          double tau_data[], int jpvt_data[]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for xzgeqp3.h
 *
 * [EOF]
 */
