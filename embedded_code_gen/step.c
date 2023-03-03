/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: step.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "step.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "normal.h"
#include "relaxed.h"
#include "rt_nonfinite.h"
#include "soc.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int *STEP_TYPE
 *                double Hessian[32761]
 *                const double lb[181]
 *                const double ub[181]
 *                c_struct_T *TrialState
 *                struct_T *MeritFunction
 *                e_struct_T *memspace
 *                f_struct_T *WorkingSet
 *                g_struct_T *QRManager
 *                h_struct_T *CholManager
 *                d_struct_T *QPObjective
 *                m_struct_T *qpoptions
 * Return Type  : bool
 */
bool step(int *STEP_TYPE, double Hessian[32761], const double lb[181],
          const double ub[181], c_struct_T *TrialState, struct_T *MeritFunction,
          e_struct_T *memspace, f_struct_T *WorkingSet, g_struct_T *QRManager,
          h_struct_T *CholManager, d_struct_T *QPObjective,
          m_struct_T *qpoptions)
{
  double y_data[1803];
  double tmp_data[982];
  double nrmDirInf;
  double nrmGradInf;
  int idx;
  int idxEndIneq;
  int idxStartIneq;
  int nVar;
  bool checkBoundViolation;
  bool stepSuccess;
  stepSuccess = true;
  checkBoundViolation = true;
  nVar = WorkingSet->nVar;
  if (*STEP_TYPE != 3) {
    idxEndIneq = (unsigned short)WorkingSet->nVar;
    memcpy(&TrialState->xstar.data[0], &TrialState->xstarsqp[0],
           (unsigned int)idxEndIneq * sizeof(double));
  } else {
    idxStartIneq = TrialState->searchDir.size[0];
    idxEndIneq = TrialState->searchDir.size[0];
    if (idxEndIneq - 1 >= 0) {
      memcpy(&y_data[0], &TrialState->searchDir.data[0],
             (unsigned int)idxEndIneq * sizeof(double));
    }
    idxEndIneq = (unsigned short)WorkingSet->nVar;
    if (idxEndIneq - 1 >= 0) {
      memcpy(&y_data[0], &TrialState->xstar.data[0],
             (unsigned int)idxEndIneq * sizeof(double));
    }
    TrialState->searchDir.size[0] = idxStartIneq;
    if (idxStartIneq - 1 >= 0) {
      memcpy(&TrialState->searchDir.data[0], &y_data[0],
             (unsigned int)idxStartIneq * sizeof(double));
    }
  }
  int exitg1;
  bool guard1 = false;
  do {
    exitg1 = 0;
    guard1 = false;
    switch (*STEP_TYPE) {
    case 1:
      normal(Hessian, TrialState->grad.data, TrialState, MeritFunction,
             memspace, WorkingSet, QRManager, CholManager, QPObjective,
             qpoptions);
      if ((TrialState->state <= 0) && (TrialState->state != -6)) {
        *STEP_TYPE = 2;
      } else {
        idxStartIneq = TrialState->delta_x.size[0];
        idxEndIneq = TrialState->delta_x.size[0];
        if (idxEndIneq - 1 >= 0) {
          memcpy(&y_data[0], &TrialState->delta_x.data[0],
                 (unsigned int)idxEndIneq * sizeof(double));
        }
        idxEndIneq = (unsigned short)nVar;
        if (idxEndIneq - 1 >= 0) {
          memcpy(&y_data[0], &TrialState->xstar.data[0],
                 (unsigned int)idxEndIneq * sizeof(double));
        }
        TrialState->delta_x.size[0] = idxStartIneq;
        if (idxStartIneq - 1 >= 0) {
          memcpy(&TrialState->delta_x.data[0], &y_data[0],
                 (unsigned int)idxStartIneq * sizeof(double));
        }
        guard1 = true;
      }
      break;
    case 2:
      idxStartIneq = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
      idxEndIneq = WorkingSet->nActiveConstr;
      for (idx = idxStartIneq; idx <= idxEndIneq; idx++) {
        WorkingSet->isActiveConstr
            .data[(WorkingSet->isActiveIdx[WorkingSet->Wid.data[idx - 1] - 1] +
                   WorkingSet->Wlocalidx.data[idx - 1]) -
                  2] = false;
      }
      WorkingSet->nWConstr[2] = 0;
      WorkingSet->nWConstr[3] = 0;
      WorkingSet->nWConstr[4] = 0;
      WorkingSet->nActiveConstr =
          WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1];
      idxStartIneq = TrialState->xstar.size[0];
      idxEndIneq = TrialState->xstar.size[0];
      if (idxEndIneq - 1 >= 0) {
        memcpy(&tmp_data[0], &TrialState->xstar.data[0],
               (unsigned int)idxEndIneq * sizeof(double));
      }
      idxEndIneq = (unsigned short)WorkingSet->sizes[3];
      for (idx = 0; idx < idxEndIneq; idx++) {
        nrmGradInf = WorkingSet->lb.data[WorkingSet->indexLB.data[idx] - 1];
        if (-tmp_data[WorkingSet->indexLB.data[idx] - 1] > nrmGradInf) {
          if (rtIsInf(ub[WorkingSet->indexLB.data[idx] - 1])) {
            tmp_data[WorkingSet->indexLB.data[idx] - 1] =
                -nrmGradInf + fabs(nrmGradInf);
          } else {
            tmp_data[WorkingSet->indexLB.data[idx] - 1] =
                (WorkingSet->ub.data[WorkingSet->indexLB.data[idx] - 1] -
                 nrmGradInf) /
                2.0;
          }
        }
      }
      idxEndIneq = (unsigned short)WorkingSet->sizes[4];
      for (idx = 0; idx < idxEndIneq; idx++) {
        nrmGradInf = WorkingSet->ub.data[WorkingSet->indexUB.data[idx] - 1];
        if (tmp_data[WorkingSet->indexUB.data[idx] - 1] > nrmGradInf) {
          if (rtIsInf(lb[WorkingSet->indexUB.data[idx] - 1])) {
            tmp_data[WorkingSet->indexUB.data[idx] - 1] =
                nrmGradInf - fabs(nrmGradInf);
          } else {
            tmp_data[WorkingSet->indexUB.data[idx] - 1] =
                (nrmGradInf -
                 WorkingSet->lb.data[WorkingSet->indexUB.data[idx] - 1]) /
                2.0;
          }
        }
      }
      TrialState->xstar.size[0] = idxStartIneq;
      if (idxStartIneq - 1 >= 0) {
        memcpy(&TrialState->xstar.data[0], &tmp_data[0],
               (unsigned int)idxStartIneq * sizeof(double));
      }
      relaxed(Hessian, TrialState->grad.data, TrialState, MeritFunction,
              memspace, WorkingSet, QRManager, CholManager, QPObjective,
              qpoptions);
      idxStartIneq = TrialState->delta_x.size[0];
      idxEndIneq = TrialState->delta_x.size[0];
      if (idxEndIneq - 1 >= 0) {
        memcpy(&y_data[0], &TrialState->delta_x.data[0],
               (unsigned int)idxEndIneq * sizeof(double));
      }
      idxEndIneq = (unsigned short)nVar;
      if (idxEndIneq - 1 >= 0) {
        memcpy(&y_data[0], &TrialState->xstar.data[0],
               (unsigned int)idxEndIneq * sizeof(double));
      }
      TrialState->delta_x.size[0] = idxStartIneq;
      if (idxStartIneq - 1 >= 0) {
        memcpy(&TrialState->delta_x.data[0], &y_data[0],
               (unsigned int)idxStartIneq * sizeof(double));
      }
      guard1 = true;
      break;
    default:
      idxEndIneq = TrialState->grad.size[0];
      if (idxEndIneq - 1 >= 0) {
        memcpy(&tmp_data[0], &TrialState->grad.data[0],
               (unsigned int)idxEndIneq * sizeof(double));
      }
      stepSuccess = soc(Hessian, tmp_data, TrialState, memspace, WorkingSet,
                        QRManager, CholManager, QPObjective, qpoptions);
      checkBoundViolation = stepSuccess;
      if (stepSuccess && (TrialState->state != -6)) {
        idxEndIneq = (unsigned short)nVar;
        for (idx = 0; idx < idxEndIneq; idx++) {
          TrialState->delta_x.data[idx] =
              TrialState->xstar.data[idx] + TrialState->socDirection.data[idx];
        }
      }
      guard1 = true;
      break;
    }
    if (guard1) {
      if (TrialState->state != -6) {
        exitg1 = 1;
      } else {
        nrmGradInf = 0.0;
        nrmDirInf = 1.0;
        for (idx = 0; idx < 181; idx++) {
          nrmGradInf = fmax(nrmGradInf, fabs(TrialState->grad.data[idx]));
          nrmDirInf = fmax(nrmDirInf, fabs(TrialState->xstar.data[idx]));
        }
        nrmGradInf = fmax(2.2204460492503131E-16, nrmGradInf / nrmDirInf);
        for (idx = 0; idx < 181; idx++) {
          idxStartIneq = 181 * idx;
          for (idxEndIneq = 0; idxEndIneq < idx; idxEndIneq++) {
            Hessian[idxStartIneq + idxEndIneq] = 0.0;
          }
          Hessian[idx + 181 * idx] = nrmGradInf;
          idxStartIneq += idx;
          idxEndIneq = 179 - idx;
          if (idxEndIneq >= 0) {
            memset(&Hessian[idxStartIneq + 1], 0,
                   (unsigned int)(((idxEndIneq + idxStartIneq) - idxStartIneq) +
                                  1) *
                       sizeof(double));
          }
        }
      }
    }
  } while (exitg1 == 0);
  if (checkBoundViolation) {
    idxStartIneq = TrialState->delta_x.size[0];
    idxEndIneq = TrialState->delta_x.size[0];
    if (idxEndIneq - 1 >= 0) {
      memcpy(&tmp_data[0], &TrialState->delta_x.data[0],
             (unsigned int)idxEndIneq * sizeof(double));
    }
    idxEndIneq = (unsigned short)WorkingSet->sizes[3];
    for (idx = 0; idx < idxEndIneq; idx++) {
      nrmGradInf = tmp_data[WorkingSet->indexLB.data[idx] - 1];
      nrmDirInf = (TrialState->xstarsqp[WorkingSet->indexLB.data[idx] - 1] +
                   nrmGradInf) -
                  lb[WorkingSet->indexLB.data[idx] - 1];
      if (nrmDirInf < 0.0) {
        tmp_data[WorkingSet->indexLB.data[idx] - 1] = nrmGradInf - nrmDirInf;
        TrialState->xstar.data[WorkingSet->indexLB.data[idx] - 1] -= nrmDirInf;
      }
    }
    idxEndIneq = (unsigned short)WorkingSet->sizes[4];
    for (idx = 0; idx < idxEndIneq; idx++) {
      nrmGradInf = tmp_data[WorkingSet->indexUB.data[idx] - 1];
      nrmDirInf = (ub[WorkingSet->indexUB.data[idx] - 1] -
                   TrialState->xstarsqp[WorkingSet->indexUB.data[idx] - 1]) -
                  nrmGradInf;
      if (nrmDirInf < 0.0) {
        tmp_data[WorkingSet->indexUB.data[idx] - 1] = nrmGradInf + nrmDirInf;
        TrialState->xstar.data[WorkingSet->indexUB.data[idx] - 1] += nrmDirInf;
      }
    }
    TrialState->delta_x.size[0] = idxStartIneq;
    if (idxStartIneq - 1 >= 0) {
      memcpy(&TrialState->delta_x.data[0], &tmp_data[0],
             (unsigned int)idxStartIneq * sizeof(double));
    }
  }
  return stepSuccess;
}

/*
 * File trailer for step.c
 *
 * [EOF]
 */
