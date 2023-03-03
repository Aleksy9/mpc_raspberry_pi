/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgemm.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef XGEMM_H
#define XGEMM_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_xgemm(int m, int n, int k, const double A_data[], int ia0, int lda,
             const double B_data[], int ldb, double C_data[], int ldc);

void xgemm(int m, int n, int k, const double A[32761], int lda,
           const double B_data[], int ib0, int ldb, double C_data[], int ldc);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for xgemm.h
 *
 * [EOF]
 */
