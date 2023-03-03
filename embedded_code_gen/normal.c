/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: normal.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "normal.h"
#include "addAeqConstr.h"
#include "driver1.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double Hessian[32761]
 *                const double grad_data[]
 *                c_struct_T *TrialState
 *                struct_T *MeritFunction
 *                e_struct_T *memspace
 *                f_struct_T *WorkingSet
 *                g_struct_T *QRManager
 *                h_struct_T *CholManager
 *                d_struct_T *QPObjective
 *                const m_struct_T *qpoptions
 * Return Type  : void
 */
void normal(const double Hessian[32761], const double grad_data[],
            c_struct_T *TrialState, struct_T *MeritFunction,
            e_struct_T *memspace, f_struct_T *WorkingSet, g_struct_T *QRManager,
            h_struct_T *CholManager, d_struct_T *QPObjective,
            const m_struct_T *qpoptions)
{
  m_struct_T b_qpoptions;
  m_struct_T c_qpoptions;
  int idx;
  int k;
  bool nonlinEqRemoved;
  b_qpoptions = *qpoptions;
  c_qpoptions = *qpoptions;
  b_driver(Hessian, grad_data, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, &b_qpoptions, &c_qpoptions);
  if (TrialState->state > 0) {
    double constrViolationEq;
    double constrViolationIneq;
    double d;
    double penaltyParamTrial;
    penaltyParamTrial = MeritFunction->penaltyParam;
    constrViolationEq = 0.0;
    for (k = 0; k < 160; k++) {
      constrViolationEq += fabs(TrialState->cEq[k]);
    }
    constrViolationIneq = 0.0;
    k = (unsigned short)WorkingSet->sizes[2];
    for (idx = 0; idx < k; idx++) {
      d = TrialState->cIneq.data[idx];
      if (d > 0.0) {
        constrViolationIneq += d;
      }
    }
    constrViolationIneq += constrViolationEq;
    constrViolationEq = MeritFunction->linearizedConstrViol;
    MeritFunction->linearizedConstrViol = 0.0;
    constrViolationEq += constrViolationIneq;
    if ((constrViolationEq > 2.2204460492503131E-16) &&
        (TrialState->fstar > 0.0)) {
      if (TrialState->sqpFval == 0.0) {
        d = 1.0;
      } else {
        d = 1.5;
      }
      penaltyParamTrial = d * TrialState->fstar / constrViolationEq;
    }
    if (penaltyParamTrial < MeritFunction->penaltyParam) {
      MeritFunction->phi =
          TrialState->sqpFval + penaltyParamTrial * constrViolationIneq;
      if ((MeritFunction->initFval +
           penaltyParamTrial * (MeritFunction->initConstrViolationEq +
                                MeritFunction->initConstrViolationIneq)) -
              MeritFunction->phi >
          (double)MeritFunction->nPenaltyDecreases * MeritFunction->threshold) {
        MeritFunction->nPenaltyDecreases++;
        if ((MeritFunction->nPenaltyDecreases << 1) >
            TrialState->sqpIterations) {
          MeritFunction->threshold *= 10.0;
        }
        MeritFunction->penaltyParam = fmax(penaltyParamTrial, 1.0E-10);
      } else {
        MeritFunction->phi = TrialState->sqpFval +
                             MeritFunction->penaltyParam * constrViolationIneq;
      }
    } else {
      MeritFunction->penaltyParam = fmax(penaltyParamTrial, 1.0E-10);
      MeritFunction->phi = TrialState->sqpFval +
                           MeritFunction->penaltyParam * constrViolationIneq;
    }
    MeritFunction->phiPrimePlus = fmin(
        TrialState->fstar - MeritFunction->penaltyParam * constrViolationIneq,
        0.0);
  }
  sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
               WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid.data,
               WorkingSet->Wlocalidx.data, memspace->workspace_double.data);
  nonlinEqRemoved = (WorkingSet->mEqRemoved > 0);
  while ((WorkingSet->mEqRemoved > 0) &&
         (WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1] >= 1)) {
    addAeqConstr(WorkingSet,
                 WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1]);
    WorkingSet->mEqRemoved--;
  }
  if (nonlinEqRemoved) {
    for (idx = 0; idx < 160; idx++) {
      WorkingSet->Wlocalidx.data[WorkingSet->sizes[0] + idx] = idx + 1;
    }
  }
}

/*
 * File trailer for normal.c
 *
 * [EOF]
 */
