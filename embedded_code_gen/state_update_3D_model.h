/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: state_update_3D_model.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef STATE_UPDATE_3D_MODEL_H
#define STATE_UPDATE_3D_MODEL_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void state_deriv(const double states[16], const double inputs[4],
                 double statederiv[16]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for state_update_3D_model.h
 *
 * [EOF]
 */
