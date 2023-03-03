/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: soc.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "soc.h"
#include "addAeqConstr.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver1.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "xnrm2.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double Hessian[32761]
 *                const double grad_data[]
 *                c_struct_T *TrialState
 *                e_struct_T *memspace
 *                f_struct_T *WorkingSet
 *                g_struct_T *QRManager
 *                h_struct_T *CholManager
 *                d_struct_T *QPObjective
 *                const m_struct_T *qpoptions
 * Return Type  : bool
 */
bool soc(const double Hessian[32761], const double grad_data[],
         c_struct_T *TrialState, e_struct_T *memspace, f_struct_T *WorkingSet,
         g_struct_T *QRManager, h_struct_T *CholManager,
         d_struct_T *QPObjective, const m_struct_T *qpoptions)
{
  m_struct_T b_qpoptions;
  m_struct_T c_qpoptions;
  double c;
  int i;
  int idx;
  int idxIneqOffset;
  int idx_Aineq;
  int idx_Partition;
  int idx_upper;
  int iy;
  int mConstrMax;
  int nVar;
  int nWIneq_old;
  int nWLower_old;
  int nWUpper_old;
  bool success;
  nWIneq_old = WorkingSet->nWConstr[2];
  nWLower_old = WorkingSet->nWConstr[3];
  nWUpper_old = WorkingSet->nWConstr[4];
  nVar = WorkingSet->nVar;
  mConstrMax = WorkingSet->mConstrMax;
  i = (unsigned short)WorkingSet->nVar;
  for (idx_Aineq = 0; idx_Aineq < i; idx_Aineq++) {
    TrialState->xstarsqp[idx_Aineq] = TrialState->xstarsqp_old[idx_Aineq];
    TrialState->socDirection.data[idx_Aineq] =
        TrialState->xstar.data[idx_Aineq];
  }
  i = (unsigned short)WorkingSet->mConstrMax;
  if (i - 1 >= 0) {
    memcpy(&TrialState->lambdaStopTest.data[0], &TrialState->lambda.data[0],
           (unsigned int)i * sizeof(double));
  }
  idxIneqOffset = WorkingSet->isActiveIdx[2];
  for (idx = 0; idx < 160; idx++) {
    WorkingSet->beq[idx] = -TrialState->cEq[idx];
  }
  idx_Aineq = WorkingSet->ldA;
  iy = 0;
  i = WorkingSet->ldA * 159 + 1;
  for (idx_Partition = 1;
       idx_Aineq < 0 ? idx_Partition >= i : idx_Partition <= i;
       idx_Partition += idx_Aineq) {
    c = 0.0;
    idx_upper = (idx_Partition + WorkingSet->nVar) - 1;
    for (idx = idx_Partition; idx <= idx_upper; idx++) {
      c += WorkingSet->Aeq.data[idx - 1] *
           TrialState->searchDir.data[idx - idx_Partition];
    }
    WorkingSet->beq[iy] += c;
    iy++;
  }
  for (idx_Aineq = 0; idx_Aineq < 160; idx_Aineq++) {
    WorkingSet->bwset.data[WorkingSet->sizes[0] + idx_Aineq] =
        WorkingSet->beq[idx_Aineq];
  }
  if (WorkingSet->sizes[2] > 0) {
    i = (unsigned short)WorkingSet->sizes[2];
    for (idx = 0; idx < i; idx++) {
      WorkingSet->bineq.data[idx] = -TrialState->cIneq.data[idx];
    }
    idx_Aineq = WorkingSet->ldA;
    iy = 0;
    i = WorkingSet->ldA * (WorkingSet->sizes[2] - 1) + 1;
    for (idx_Partition = 1;
         idx_Aineq < 0 ? idx_Partition >= i : idx_Partition <= i;
         idx_Partition += idx_Aineq) {
      c = 0.0;
      idx_upper = (idx_Partition + WorkingSet->nVar) - 1;
      for (idx = idx_Partition; idx <= idx_upper; idx++) {
        c += WorkingSet->Aineq.data[idx - 1] *
             TrialState->searchDir.data[idx - idx_Partition];
      }
      WorkingSet->bineq.data[iy] += c;
      iy++;
    }
    idx_Aineq = 1;
    iy = WorkingSet->sizes[2] + 1;
    idx_upper = (WorkingSet->sizes[2] + WorkingSet->sizes[3]) + 1;
    i = WorkingSet->nActiveConstr;
    for (idx = idxIneqOffset; idx <= i; idx++) {
      switch (WorkingSet->Wid.data[idx - 1]) {
      case 3:
        idx_Partition = idx_Aineq;
        idx_Aineq++;
        WorkingSet->bwset.data[idx - 1] =
            WorkingSet->bineq.data[WorkingSet->Wlocalidx.data[idx - 1] - 1];
        break;
      case 4:
        idx_Partition = iy;
        iy++;
        break;
      default:
        idx_Partition = idx_upper;
        idx_upper++;
        break;
      }
      TrialState->workingset_old.data[idx_Partition - 1] =
          WorkingSet->Wlocalidx.data[idx - 1];
    }
  }
  i = (unsigned short)WorkingSet->nVar;
  memcpy(&TrialState->xstar.data[0], &TrialState->xstarsqp[0],
         (unsigned int)i * sizeof(double));
  b_qpoptions = *qpoptions;
  c_qpoptions = *qpoptions;
  b_driver(Hessian, grad_data, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, &b_qpoptions, &c_qpoptions);
  while ((WorkingSet->mEqRemoved > 0) &&
         (WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1] >= 1)) {
    addAeqConstr(WorkingSet,
                 WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1]);
    WorkingSet->mEqRemoved--;
  }
  i = (unsigned short)nVar;
  for (idx = 0; idx < i; idx++) {
    double oldDirIdx;
    c = TrialState->socDirection.data[idx];
    oldDirIdx = c;
    c = TrialState->xstar.data[idx] - c;
    TrialState->socDirection.data[idx] = c;
    TrialState->xstar.data[idx] = oldDirIdx;
  }
  success = (b_xnrm2(nVar, TrialState->socDirection.data) <=
             2.0 * b_xnrm2(nVar, TrialState->xstar.data));
  idx_Partition = WorkingSet->sizes[2];
  nVar = WorkingSet->sizes[3];
  for (idx = 0; idx < 160; idx++) {
    WorkingSet->beq[idx] = -TrialState->cEq[idx];
  }
  for (idx_Aineq = 0; idx_Aineq < 160; idx_Aineq++) {
    WorkingSet->bwset.data[WorkingSet->sizes[0] + idx_Aineq] =
        WorkingSet->beq[idx_Aineq];
  }
  if (WorkingSet->sizes[2] > 0) {
    i = (unsigned short)WorkingSet->sizes[2];
    for (idx = 0; idx < i; idx++) {
      WorkingSet->bineq.data[idx] = -TrialState->cIneq.data[idx];
    }
    if (!success) {
      idx_Aineq = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
      iy = WorkingSet->nActiveConstr;
      for (idx_upper = idx_Aineq; idx_upper <= iy; idx_upper++) {
        WorkingSet->isActiveConstr.data
            [(WorkingSet->isActiveIdx[WorkingSet->Wid.data[idx_upper - 1] - 1] +
              WorkingSet->Wlocalidx.data[idx_upper - 1]) -
             2] = false;
      }
      WorkingSet->nWConstr[2] = 0;
      WorkingSet->nWConstr[3] = 0;
      WorkingSet->nWConstr[4] = 0;
      WorkingSet->nActiveConstr =
          WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1];
      for (idx = 0; idx < nWIneq_old; idx++) {
        idx_Aineq = TrialState->workingset_old.data[idx];
        WorkingSet->nWConstr[2]++;
        WorkingSet->isActiveConstr
            .data[(WorkingSet->isActiveIdx[2] + idx_Aineq) - 2] = true;
        WorkingSet->nActiveConstr++;
        WorkingSet->Wid.data[WorkingSet->nActiveConstr - 1] = 3;
        WorkingSet->Wlocalidx.data[WorkingSet->nActiveConstr - 1] = idx_Aineq;
        iy = WorkingSet->ldA * (idx_Aineq - 1);
        idx_upper = WorkingSet->ldA * (WorkingSet->nActiveConstr - 1);
        i = WorkingSet->nVar - 1;
        for (idxIneqOffset = 0; idxIneqOffset <= i; idxIneqOffset++) {
          WorkingSet->ATwset.data[idx_upper + idxIneqOffset] =
              WorkingSet->Aineq.data[iy + idxIneqOffset];
        }
        WorkingSet->bwset.data[WorkingSet->nActiveConstr - 1] =
            WorkingSet->bineq.data[idx_Aineq - 1];
      }
      for (idx = 0; idx < nWLower_old; idx++) {
        addBoundToActiveSetMatrix_(
            WorkingSet, 4,
            TrialState->workingset_old.data[idx + idx_Partition]);
      }
      for (idx = 0; idx < nWUpper_old; idx++) {
        addBoundToActiveSetMatrix_(
            WorkingSet, 5,
            TrialState->workingset_old.data[(idx + idx_Partition) + nVar]);
      }
    }
  }
  if (!success) {
    i = (unsigned short)mConstrMax;
    if (i - 1 >= 0) {
      memcpy(&TrialState->lambda.data[0], &TrialState->lambdaStopTest.data[0],
             (unsigned int)i * sizeof(double));
    }
  } else {
    sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
                 WorkingSet->sizes, WorkingSet->isActiveIdx,
                 WorkingSet->Wid.data, WorkingSet->Wlocalidx.data,
                 memspace->workspace_double.data);
  }
  return success;
}

/*
 * File trailer for soc.c
 *
 * [EOF]
 */
