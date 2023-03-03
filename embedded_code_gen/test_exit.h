/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: test_exit.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef TEST_EXIT_H
#define TEST_EXIT_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_test_exit(b_struct_T *Flags, e_struct_T *memspace,
                 struct_T *MeritFunction, int fscales_lineq_constraint_size,
                 int fscales_cineq_constraint_size, f_struct_T *WorkingSet,
                 c_struct_T *TrialState, g_struct_T *QRManager,
                 const double lb[181], const double ub[181]);

void test_exit(struct_T *MeritFunction, const f_struct_T *WorkingSet,
               c_struct_T *TrialState, const double lb[181],
               const double ub[181], bool *Flags_gradOK, bool *Flags_fevalOK,
               bool *Flags_done, bool *Flags_stepAccepted,
               bool *Flags_failedLineSearch, int *Flags_stepType);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for test_exit.h
 *
 * [EOF]
 */
