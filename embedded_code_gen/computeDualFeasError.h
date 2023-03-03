/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeDualFeasError.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef COMPUTEDUALFEASERROR_H
#define COMPUTEDUALFEASERROR_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void computeDualFeasError(int nVar, const double gradLag_data[], bool *gradOK,
                          double *val);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeDualFeasError.h
 *
 * [EOF]
 */
