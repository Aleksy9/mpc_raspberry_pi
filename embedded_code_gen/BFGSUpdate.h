/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: BFGSUpdate.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef BFGSUPDATE_H
#define BFGSUPDATE_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
bool BFGSUpdate(int nvar, double Bk[32761], const double sk_data[],
                double yk_data[], double workspace_data[]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for BFGSUpdate.h
 *
 * [EOF]
 */
