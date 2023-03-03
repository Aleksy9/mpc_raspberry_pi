/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeGradLag.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef COMPUTEGRADLAG_H
#define COMPUTEGRADLAG_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void computeGradLag(double workspace_data[], int ldA, int nVar,
                    const double grad_data[], int mIneq,
                    const double AineqTrans_data[],
                    const double AeqTrans_data[], const int finiteFixed_data[],
                    int mFixed, const int finiteLB_data[], int mLB,
                    const int finiteUB_data[], int mUB,
                    const double lambda_data[]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeGradLag.h
 *
 * [EOF]
 */
