/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: linesearch.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef LINESEARCH_H
#define LINESEARCH_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void linesearch(bool *evalWellDefined, const double bineq_data[],
                int WorkingSet_nVar, int WorkingSet_ldA,
                const double WorkingSet_Aineq_data[], c_struct_T *TrialState,
                double MeritFunction_penaltyParam, double MeritFunction_phi,
                double MeritFunction_phiPrimePlus,
                double MeritFunction_phiFullStep,
                int c_FcnEvaluator_next_next_next_n,
                const i_struct_T *d_FcnEvaluator_next_next_next_n,
                const k_struct_T *e_FcnEvaluator_next_next_next_n,
                bool socTaken, double *alpha, int *exitflag);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for linesearch.h
 *
 * [EOF]
 */
