/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: znlmpc_confun.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef ZNLMPC_CONFUN_H
#define ZNLMPC_CONFUN_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void outputBounds(const double runtimedata_OutputMin[160],
                  const double runtimedata_OutputMax[160], const double X[176],
                  double e, double c_data[], int c_size[2], double Jc_data[],
                  int Jc_size[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for znlmpc_confun.h
 *
 * [EOF]
 */
