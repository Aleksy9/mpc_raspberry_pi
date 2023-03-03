/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: updateWorkingSetForNewQP.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "updateWorkingSetForNewQP.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double xk[181]
 *                f_struct_T *WorkingSet
 *                int mIneq
 *                int mNonlinIneq
 *                const double cIneq_data[]
 *                const double cEq[160]
 *                int mLB
 *                const double lb[181]
 *                int mUB
 *                const double ub[181]
 *                int mFixed
 * Return Type  : void
 */
void updateWorkingSetForNewQP(const double xk[181], f_struct_T *WorkingSet,
                              int mIneq, int mNonlinIneq,
                              const double cIneq_data[], const double cEq[160],
                              int mLB, const double lb[181], int mUB,
                              const double ub[181], int mFixed)
{
  int b_i;
  int i;
  int iEq0;
  int idx;
  int iw0;
  int k;
  int nVar;
  nVar = WorkingSet->nVar;
  iw0 = WorkingSet->ldA * mFixed;
  iEq0 = 0;
  i = nVar - 1;
  for (idx = 0; idx < 160; idx++) {
    double d;
    d = -cEq[idx];
    WorkingSet->beq[idx] = d;
    WorkingSet->bwset.data[mFixed + idx] = d;
    for (b_i = 0; b_i <= i; b_i++) {
      WorkingSet->ATwset.data[iw0 + b_i] = WorkingSet->Aeq.data[iEq0 + b_i];
    }
    iw0 += WorkingSet->ldA;
    iEq0 += WorkingSet->ldA;
  }
  i = (unsigned short)mIneq;
  for (idx = 0; idx < i; idx++) {
    WorkingSet->bineq.data[idx] = -cIneq_data[idx];
  }
  i = (unsigned short)mLB;
  for (idx = 0; idx < i; idx++) {
    WorkingSet->lb.data[WorkingSet->indexLB.data[idx] - 1] =
        -lb[WorkingSet->indexLB.data[idx] - 1] +
        xk[WorkingSet->indexLB.data[idx] - 1];
  }
  i = (unsigned short)mUB;
  for (idx = 0; idx < i; idx++) {
    WorkingSet->ub.data[WorkingSet->indexUB.data[idx] - 1] =
        ub[WorkingSet->indexUB.data[idx] - 1] -
        xk[WorkingSet->indexUB.data[idx] - 1];
  }
  i = (unsigned short)mFixed;
  for (idx = 0; idx < i; idx++) {
    WorkingSet->ub.data[WorkingSet->indexFixed.data[idx] - 1] =
        ub[WorkingSet->indexFixed.data[idx] - 1] -
        xk[WorkingSet->indexFixed.data[idx] - 1];
    WorkingSet->bwset.data[idx] = ub[WorkingSet->indexFixed.data[idx] - 1] -
                                  xk[WorkingSet->indexFixed.data[idx] - 1];
  }
  if (WorkingSet->nActiveConstr > mFixed + 160) {
    iw0 = mFixed + 161;
    i = WorkingSet->nActiveConstr;
    for (idx = iw0; idx <= i; idx++) {
      switch (WorkingSet->Wid.data[idx - 1]) {
      case 4:
        WorkingSet->bwset.data[idx - 1] =
            WorkingSet->lb
                .data[WorkingSet->indexLB
                          .data[WorkingSet->Wlocalidx.data[idx - 1] - 1] -
                      1];
        break;
      case 5:
        WorkingSet->bwset.data[idx - 1] =
            WorkingSet->ub
                .data[WorkingSet->indexUB
                          .data[WorkingSet->Wlocalidx.data[idx - 1] - 1] -
                      1];
        break;
      default: {
        WorkingSet->bwset.data[idx - 1] =
            WorkingSet->bineq.data[WorkingSet->Wlocalidx.data[idx - 1] - 1];
        if ((mNonlinIneq > 0) &&
            (WorkingSet->Wlocalidx.data[idx - 1] >= mNonlinIneq)) {
          int i1;
          iEq0 = WorkingSet->ldA * (idx - 1);
          b_i = WorkingSet->ldA * (WorkingSet->Wlocalidx.data[idx - 1] - 1);
          i1 = (unsigned short)nVar;
          for (k = 0; k < i1; k++) {
            WorkingSet->ATwset.data[iEq0 + k] = WorkingSet->Aineq.data[b_i + k];
          }
        }
      } break;
      }
    }
  }
}

/*
 * File trailer for updateWorkingSetForNewQP.c
 *
 * [EOF]
 */
