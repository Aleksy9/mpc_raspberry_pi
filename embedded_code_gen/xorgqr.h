/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xorgqr.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef XORGQR_H
#define XORGQR_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void xorgqr(int m, int n, int k, double A_data[], const int A_size[2], int lda,
            const double tau_data[]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for xorgqr.h
 *
 * [EOF]
 */
