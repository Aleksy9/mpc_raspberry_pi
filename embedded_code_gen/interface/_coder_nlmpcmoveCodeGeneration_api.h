/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_nlmpcmoveCodeGeneration_api.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef _CODER_NLMPCMOVECODEGENERATION_API_H
#define _CODER_NLMPCMOVECODEGENERATION_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef typedef_struct2_T
#define typedef_struct2_T
typedef struct {
  real_T MVopt[44];
  real_T Xopt[176];
  real_T Yopt[176];
  real_T Topt[11];
  real_T Slack;
  real_T ExitFlag;
  real_T Iterations;
  real_T Cost;
} struct2_T;
#endif /* typedef_struct2_T */

#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct {
  real_T ref[16];
  real_T Parameters[1];
  real_T X0[160];
  real_T MV0[40];
  real_T Slack0;
} struct1_T;
#endif /* typedef_struct1_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void nlmpcmoveCodeGeneration(real_T x[16], real_T lastMV[4],
                             struct1_T *onlinedata, real_T mv[4],
                             struct2_T *info);

void nlmpcmoveCodeGeneration_api(const mxArray *const prhs[4], int32_T nlhs,
                                 const mxArray *plhs[3]);

void nlmpcmoveCodeGeneration_atexit(void);

void nlmpcmoveCodeGeneration_initialize(void);

void nlmpcmoveCodeGeneration_terminate(void);

void nlmpcmoveCodeGeneration_xil_shutdown(void);

void nlmpcmoveCodeGeneration_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_nlmpcmoveCodeGeneration_api.h
 *
 * [EOF]
 */
