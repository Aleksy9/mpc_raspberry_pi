/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeLinearResiduals.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef COMPUTELINEARRESIDUALS_H
#define COMPUTELINEARRESIDUALS_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void computeLinearResiduals(const double x[181], int nVar,
                            double workspaceIneq_data[],
                            const int *workspaceIneq_size, int mLinIneq,
                            const double AineqT_data[],
                            const double bineq_data[], int ldAi);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeLinearResiduals.h
 *
 * [EOF]
 */
