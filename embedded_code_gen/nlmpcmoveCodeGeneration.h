/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: nlmpcmoveCodeGeneration.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef NLMPCMOVECODEGENERATION_H
#define NLMPCMOVECODEGENERATION_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_nlmpcmoveCodeGeneration_anonF(
    const double runtimedata_x[16], const double runtimedata_OutputMin[160],
    const double runtimedata_OutputMax[160], double runtimedata_Parameters,
    const double z[181], double varargout_1_data[], int varargout_1_size[2],
    double varargout_2[160], double varargout_3_data[], int varargout_3_size[2],
    double varargout_4[28960]);

extern void nlmpcmoveCodeGeneration(const double x[16], const double lastMV[4],
                                    struct1_T *onlinedata, double mv[4],
                                    struct2_T *info);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for nlmpcmoveCodeGeneration.h
 *
 * [EOF]
 */
