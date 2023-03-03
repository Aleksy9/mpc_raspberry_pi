/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: relaxed.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "relaxed.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver1.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "sortLambdaQP.h"
#include "xgemv.h"
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
 *                m_struct_T *qpoptions
 * Return Type  : void
 */
void relaxed(const double Hessian[32761], const double grad_data[],
             c_struct_T *TrialState, struct_T *MeritFunction,
             e_struct_T *memspace, f_struct_T *WorkingSet,
             g_struct_T *QRManager, h_struct_T *CholManager,
             d_struct_T *QPObjective, m_struct_T *qpoptions)
{
  m_struct_T b_qpoptions;
  m_struct_T c_qpoptions;
  double beta;
  double constrViolation;
  double rho;
  double s;
  double smax;
  int b_mIneq;
  int i;
  int idx;
  int idx_max;
  int idx_positive_tmp;
  int mIneq;
  int nActiveLBArtificial;
  int nVarOrig;
  bool tf;
  nVarOrig = WorkingSet->nVar;
  mIneq = WorkingSet->sizes[2];
  beta = 0.0;
  i = (unsigned short)WorkingSet->nVar;
  for (idx = 0; idx < i; idx++) {
    beta += Hessian[idx + 181 * idx];
  }
  beta /= (double)WorkingSet->nVar;
  if (TrialState->sqpIterations <= 1) {
    b_mIneq = QPObjective->nvar;
    if (QPObjective->nvar < 1) {
      idx_max = 0;
    } else {
      idx_max = 1;
      if (QPObjective->nvar > 1) {
        smax = fabs(grad_data[0]);
        for (idx = 2; idx <= b_mIneq; idx++) {
          s = fabs(grad_data[idx - 1]);
          if (s > smax) {
            idx_max = idx;
            smax = s;
          }
        }
      }
    }
    rho = 100.0 * fmax(1.0, fabs(grad_data[idx_max - 1]));
  } else {
    b_mIneq = WorkingSet->mConstr;
    if (WorkingSet->mConstr < 1) {
      idx_max = 0;
    } else {
      idx_max = 1;
      if (WorkingSet->mConstr > 1) {
        smax = fabs(TrialState->lambdasqp.data[0]);
        for (idx = 2; idx <= b_mIneq; idx++) {
          s = fabs(TrialState->lambdasqp.data[idx - 1]);
          if (s > smax) {
            idx_max = idx;
            smax = s;
          }
        }
      }
    }
    rho = fabs(TrialState->lambdasqp.data[idx_max - 1]);
  }
  QPObjective->nvar = WorkingSet->nVar;
  QPObjective->beta = beta;
  QPObjective->rho = rho;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 4;
  setProblemType(WorkingSet, 2);
  b_mIneq = WorkingSet->sizes[2] + 1;
  idx_max = WorkingSet->sizes[3] - WorkingSet->sizes[2];
  i = (unsigned short)WorkingSet->sizes[2];
  if (i - 1 >= 0) {
    memcpy(&memspace->workspace_double.data[0], &WorkingSet->bineq.data[0],
           (unsigned int)i * sizeof(double));
  }
  b_xgemv(nVarOrig, WorkingSet->sizes[2], WorkingSet->Aineq.data,
          WorkingSet->ldA, TrialState->xstar.data,
          memspace->workspace_double.data);
  for (idx = 0; idx < i; idx++) {
    constrViolation = memspace->workspace_double.data[idx];
    TrialState->xstar.data[nVarOrig + idx] =
        (double)(constrViolation > 0.0) * constrViolation;
  }
  memcpy(&memspace->workspace_double.data[0], &WorkingSet->beq[0],
         160U * sizeof(double));
  b_xgemv(nVarOrig, 160, WorkingSet->Aeq.data, WorkingSet->ldA,
          TrialState->xstar.data, memspace->workspace_double.data);
  for (idx = 0; idx < 160; idx++) {
    idx_positive_tmp = b_mIneq + idx;
    constrViolation = memspace->workspace_double.data[idx];
    if (constrViolation <= 0.0) {
      TrialState->xstar.data[(nVarOrig + idx_positive_tmp) - 1] = 0.0;
      TrialState->xstar.data[(nVarOrig + idx_positive_tmp) + 159] =
          -constrViolation;
      addBoundToActiveSetMatrix_(WorkingSet, 4,
                                 (idx_max + idx_positive_tmp) - 320);
      if (constrViolation >= -1.0E-6) {
        addBoundToActiveSetMatrix_(WorkingSet, 4,
                                   (idx_max + idx_positive_tmp) - 160);
      }
    } else {
      i = nVarOrig + idx_positive_tmp;
      TrialState->xstar.data[i - 1] = constrViolation;
      TrialState->xstar.data[i + 159] = 0.0;
      addBoundToActiveSetMatrix_(WorkingSet, 4,
                                 (idx_max + idx_positive_tmp) - 160);
      if (constrViolation <= 1.0E-6) {
        addBoundToActiveSetMatrix_(WorkingSet, 4,
                                   (idx_max + idx_positive_tmp) - 320);
      }
    }
  }
  b_mIneq = qpoptions->MaxIterations;
  qpoptions->MaxIterations =
      (qpoptions->MaxIterations + WorkingSet->nVar) - nVarOrig;
  b_qpoptions = *qpoptions;
  c_qpoptions = *qpoptions;
  b_driver(Hessian, grad_data, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, &b_qpoptions, &c_qpoptions);
  qpoptions->MaxIterations = b_mIneq;
  idx_max = WorkingSet->sizes[3] - 321;
  nActiveLBArtificial = 0;
  for (idx = 0; idx < 160; idx++) {
    bool b_tf;
    b_mIneq = (WorkingSet->isActiveIdx[3] + idx_max) + idx;
    tf = WorkingSet->isActiveConstr.data[b_mIneq];
    b_tf = WorkingSet->isActiveConstr.data[b_mIneq + 160];
    memspace->workspace_int.data[idx] = tf;
    memspace->workspace_int.data[idx + 160] = b_tf;
    nActiveLBArtificial = (nActiveLBArtificial + tf) + b_tf;
  }
  i = (unsigned short)WorkingSet->sizes[2];
  for (idx = 0; idx < i; idx++) {
    tf = WorkingSet->isActiveConstr
             .data[((WorkingSet->isActiveIdx[3] + idx_max) -
                    WorkingSet->sizes[2]) +
                   idx];
    memspace->workspace_int.data[idx + 320] = tf;
    nActiveLBArtificial += tf;
  }
  if (TrialState->state != -6) {
    b_mIneq = (WorkingSet->nVarMax - nVarOrig) - 1;
    idx_positive_tmp = nVarOrig + 1;
    smax = 0.0;
    s = 0.0;
    if (b_mIneq >= 1) {
      idx_max = nVarOrig + b_mIneq;
      for (idx = idx_positive_tmp; idx <= idx_max; idx++) {
        smax += fabs(TrialState->xstar.data[idx - 1]);
      }
    }
    if (b_mIneq >= 1) {
      i = (unsigned short)b_mIneq;
      for (idx = 0; idx < i; idx++) {
        constrViolation = TrialState->xstar.data[nVarOrig + idx];
        s += constrViolation * constrViolation;
      }
    }
    rho = (TrialState->fstar - rho * smax) - beta / 2.0 * s;
    beta = MeritFunction->penaltyParam;
    smax = 0.0;
    for (idx = 0; idx < 160; idx++) {
      smax += fabs(TrialState->cEq[idx]);
    }
    s = 0.0;
    i = (unsigned short)mIneq;
    for (idx = 0; idx < i; idx++) {
      constrViolation = TrialState->cIneq.data[idx];
      if (constrViolation > 0.0) {
        s += constrViolation;
      }
    }
    constrViolation = smax + s;
    smax = MeritFunction->linearizedConstrViol;
    s = 0.0;
    if (b_mIneq >= 1) {
      idx_max = nVarOrig + b_mIneq;
      for (idx = idx_positive_tmp; idx <= idx_max; idx++) {
        s += fabs(TrialState->xstar.data[idx - 1]);
      }
    }
    MeritFunction->linearizedConstrViol = s;
    smax = (constrViolation + smax) - s;
    if ((smax > 2.2204460492503131E-16) && (rho > 0.0)) {
      if (TrialState->sqpFval == 0.0) {
        beta = 1.0;
      } else {
        beta = 1.5;
      }
      beta = beta * rho / smax;
    }
    if (beta < MeritFunction->penaltyParam) {
      MeritFunction->phi = TrialState->sqpFval + beta * constrViolation;
      if ((MeritFunction->initFval +
           beta * (MeritFunction->initConstrViolationEq +
                   MeritFunction->initConstrViolationIneq)) -
              MeritFunction->phi >
          (double)MeritFunction->nPenaltyDecreases * MeritFunction->threshold) {
        MeritFunction->nPenaltyDecreases++;
        if ((MeritFunction->nPenaltyDecreases << 1) >
            TrialState->sqpIterations) {
          MeritFunction->threshold *= 10.0;
        }
        MeritFunction->penaltyParam = fmax(beta, 1.0E-10);
      } else {
        MeritFunction->phi =
            TrialState->sqpFval + MeritFunction->penaltyParam * constrViolation;
      }
    } else {
      MeritFunction->penaltyParam = fmax(beta, 1.0E-10);
      MeritFunction->phi =
          TrialState->sqpFval + MeritFunction->penaltyParam * constrViolation;
    }
    MeritFunction->phiPrimePlus =
        fmin(rho - MeritFunction->penaltyParam * constrViolation, 0.0);
    b_mIneq = WorkingSet->isActiveIdx[1] - 1;
    for (idx = 0; idx < 160; idx++) {
      if ((memspace->workspace_int.data[idx] != 0) &&
          (memspace->workspace_int.data[idx + 160] != 0)) {
        tf = true;
      } else {
        tf = false;
      }
      i = b_mIneq + idx;
      TrialState->lambda.data[i] *= (double)tf;
    }
    b_mIneq = WorkingSet->isActiveIdx[2];
    idx_max = WorkingSet->nActiveConstr;
    for (idx = b_mIneq; idx <= idx_max; idx++) {
      if (WorkingSet->Wid.data[idx - 1] == 3) {
        TrialState->lambda.data[idx - 1] *=
            (double)memspace->workspace_int
                .data[WorkingSet->Wlocalidx.data[idx - 1] + 319];
      }
    }
  }
  b_mIneq = WorkingSet->sizes[0];
  i = WorkingSet->sizes[3] - WorkingSet->sizes[2];
  idx = WorkingSet->nActiveConstr;
  while ((idx > b_mIneq + 160) && (nActiveLBArtificial > 0)) {
    if ((WorkingSet->Wid.data[idx - 1] == 4) &&
        (WorkingSet->Wlocalidx.data[idx - 1] > i - 320)) {
      idx_max = WorkingSet->nActiveConstr - 1;
      smax = TrialState->lambda.data[idx_max];
      TrialState->lambda.data[idx_max] = 0.0;
      TrialState->lambda.data[idx - 1] = smax;
      removeConstr(WorkingSet, idx);
      nActiveLBArtificial--;
    }
    idx--;
  }
  QPObjective->nvar = nVarOrig;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 3;
  setProblemType(WorkingSet, 3);
  sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
               WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid.data,
               WorkingSet->Wlocalidx.data, memspace->workspace_double.data);
}

/*
 * File trailer for relaxed.c
 *
 * [EOF]
 */
