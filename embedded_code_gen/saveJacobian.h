/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: saveJacobian.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef SAVEJACOBIAN_H
#define SAVEJACOBIAN_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void saveJacobian(c_struct_T *obj, int nVar, int mIneq,
                  const double JacCineqTrans_data[], int ineqCol0,
                  const double JacCeqTrans_data[], int ldJ);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for saveJacobian.h
 *
 * [EOF]
 */
