/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: nlmpcmoveCodeGeneration_types.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef NLMPCMOVECODEGENERATION_TYPES_H
#define NLMPCMOVECODEGENERATION_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct2_T
#define typedef_struct2_T
typedef struct {
  double MVopt[44];
  double Xopt[176];
  double Yopt[176];
  double Topt[11];
  double Slack;
  double ExitFlag;
  double Iterations;
  double Cost;
} struct2_T;
#endif /* typedef_struct2_T */

#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct {
  double ref[16];
  double Parameters[1];
  double X0[160];
  double MV0[40];
  double Slack0;
} struct1_T;
#endif /* typedef_struct1_T */

#endif
/*
 * File trailer for nlmpcmoveCodeGeneration_types.h
 *
 * [EOF]
 */
