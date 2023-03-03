/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: phaseone.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef PHASEONE_H
#define PHASEONE_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void phaseone(const double H[32761], const double f_data[],
              c_struct_T *solution, e_struct_T *memspace,
              f_struct_T *workingset, g_struct_T *qrmanager,
              h_struct_T *cholmanager, d_struct_T *objective,
              m_struct_T *options, const m_struct_T *runTimeOptions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for phaseone.h
 *
 * [EOF]
 */
