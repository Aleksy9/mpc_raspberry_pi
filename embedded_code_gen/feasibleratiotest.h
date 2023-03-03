/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: feasibleratiotest.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef FEASIBLERATIOTEST_H
#define FEASIBLERATIOTEST_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void feasibleratiotest(
    const double solution_xstar_data[], const double solution_searchDir_data[],
    double workspace_data[], const int workspace_size[2], int workingset_nVar,
    int workingset_ldA, const double workingset_Aineq_data[],
    const double workingset_bineq_data[], const double workingset_lb_data[],
    const double workingset_ub_data[], const int workingset_indexLB_data[],
    const int workingset_indexUB_data[], const int workingset_sizes[5],
    const int workingset_isActiveIdx[6],
    const bool workingset_isActiveConstr_data[],
    const int workingset_nWConstr[5], bool isPhaseOne, double *alpha,
    bool *newBlocking, int *constrType, int *constrIdx);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for feasibleratiotest.h
 *
 * [EOF]
 */
