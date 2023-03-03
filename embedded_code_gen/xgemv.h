/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgemv.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef XGEMV_H
#define XGEMV_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_xgemv(int m, int n, const double A_data[], int lda,
             const double x_data[], double y_data[]);

void c_xgemv(int m, int n, const double A_data[], int lda,
             const double x_data[], int ix0, double y_data[]);

void d_xgemv(int m, int n, const double A[32761], int lda,
             const double x_data[], double y_data[]);

void e_xgemv(int n, const double A_data[], int lda, const double x_data[],
             double y_data[]);

void xgemv(int m, int n, const double A_data[], int lda, const double x_data[],
           double y_data[]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for xgemv.h
 *
 * [EOF]
 */
