/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: test_exit.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "test_exit.h"
#include "computeComplError.h"
#include "computeDualFeasError.h"
#include "computeGradLag.h"
#include "computePrimalFeasError.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include "xgeqp3.h"
#include "xorgqr.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : b_struct_T *Flags
 *                e_struct_T *memspace
 *                struct_T *MeritFunction
 *                int fscales_lineq_constraint_size
 *                int fscales_cineq_constraint_size
 *                f_struct_T *WorkingSet
 *                c_struct_T *TrialState
 *                g_struct_T *QRManager
 *                const double lb[181]
 *                const double ub[181]
 * Return Type  : void
 */
void b_test_exit(b_struct_T *Flags, e_struct_T *memspace,
                 struct_T *MeritFunction, int fscales_lineq_constraint_size,
                 int fscales_cineq_constraint_size, f_struct_T *WorkingSet,
                 c_struct_T *TrialState, g_struct_T *QRManager,
                 const double lb[181], const double ub[181])
{
  double optimRelativeFactor;
  double s;
  double smax;
  int i;
  int idx;
  int idx_max;
  int k;
  int mFixed;
  int mIneq;
  int mLB;
  int mUB;
  int nVar;
  bool isFeasible;
  nVar = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0] + 1;
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  i = (unsigned short)((((WorkingSet->sizes[0] + WorkingSet->sizes[2]) +
                         WorkingSet->sizes[3]) +
                        WorkingSet->sizes[4]) +
                       160);
  if (i - 1 >= 0) {
    memcpy(&TrialState->lambdaStopTest.data[0], &TrialState->lambdasqp.data[0],
           (unsigned int)i * sizeof(double));
  }
  computeGradLag(
      TrialState->gradLag.data, WorkingSet->ldA, WorkingSet->nVar,
      TrialState->grad.data, WorkingSet->sizes[2], WorkingSet->Aineq.data,
      WorkingSet->Aeq.data, WorkingSet->indexFixed.data, WorkingSet->sizes[0],
      WorkingSet->indexLB.data, WorkingSet->sizes[3], WorkingSet->indexUB.data,
      WorkingSet->sizes[4], TrialState->lambdaStopTest.data);
  if (WorkingSet->nVar < 1) {
    idx_max = 0;
  } else {
    idx_max = 1;
    if (WorkingSet->nVar > 1) {
      smax = fabs(TrialState->grad.data[0]);
      for (k = 2; k <= nVar; k++) {
        s = fabs(TrialState->grad.data[k - 1]);
        if (s > smax) {
          idx_max = k;
          smax = s;
        }
      }
    }
  }
  optimRelativeFactor = fmax(1.0, fabs(TrialState->grad.data[idx_max - 1]));
  if (rtIsInf(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }
  MeritFunction->nlpPrimalFeasError = computePrimalFeasError(
      TrialState->xstarsqp, WorkingSet->sizes[2] - TrialState->mNonlinIneq,
      TrialState->mNonlinIneq, TrialState->cIneq.data, TrialState->cEq,
      WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
      WorkingSet->indexUB.data, WorkingSet->sizes[4], ub);
  if (TrialState->sqpIterations == 0) {
    MeritFunction->feasRelativeFactor =
        fmax(1.0, MeritFunction->nlpPrimalFeasError);
  }
  isFeasible = (MeritFunction->nlpPrimalFeasError <=
                1.0E-6 * MeritFunction->feasRelativeFactor);
  computeDualFeasError(WorkingSet->nVar, TrialState->gradLag.data,
                       &Flags->gradOK, &MeritFunction->nlpDualFeasError);
  if (!Flags->gradOK) {
    Flags->done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    int rankR;
    MeritFunction->nlpComplError = computeComplError(
        fscales_lineq_constraint_size, fscales_cineq_constraint_size,
        TrialState->xstarsqp, WorkingSet->sizes[2], TrialState->cIneq.data,
        WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
        WorkingSet->indexUB.data, WorkingSet->sizes[4], ub,
        TrialState->lambdaStopTest.data, WorkingSet->sizes[0] + 161);
    MeritFunction->firstOrderOpt =
        fmax(MeritFunction->nlpDualFeasError, MeritFunction->nlpComplError);
    if (TrialState->sqpIterations > 1) {
      double d;
      computeGradLag(memspace->workspace_double.data, WorkingSet->ldA,
                     WorkingSet->nVar, TrialState->grad.data,
                     WorkingSet->sizes[2], WorkingSet->Aineq.data,
                     WorkingSet->Aeq.data, WorkingSet->indexFixed.data,
                     WorkingSet->sizes[0], WorkingSet->indexLB.data,
                     WorkingSet->sizes[3], WorkingSet->indexUB.data,
                     WorkingSet->sizes[4], TrialState->lambdaStopTestPrev.data);
      smax = 0.0;
      rankR = (unsigned short)WorkingSet->nVar;
      idx = 0;
      while ((idx <= rankR - 1) &&
             ((!rtIsInf(memspace->workspace_double.data[idx])) &&
              (!rtIsNaN(memspace->workspace_double.data[idx])))) {
        smax = fmax(smax, fabs(memspace->workspace_double.data[idx]));
        idx++;
      }
      s = computeComplError(
          fscales_lineq_constraint_size, fscales_cineq_constraint_size,
          TrialState->xstarsqp, WorkingSet->sizes[2], TrialState->cIneq.data,
          WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
          WorkingSet->indexUB.data, WorkingSet->sizes[4], ub,
          TrialState->lambdaStopTestPrev.data, WorkingSet->sizes[0] + 161);
      d = fmax(smax, s);
      if (d <
          fmax(MeritFunction->nlpDualFeasError, MeritFunction->nlpComplError)) {
        MeritFunction->nlpDualFeasError = smax;
        MeritFunction->nlpComplError = s;
        MeritFunction->firstOrderOpt = d;
        if (i - 1 >= 0) {
          memcpy(&TrialState->lambdaStopTest.data[0],
                 &TrialState->lambdaStopTestPrev.data[0],
                 (unsigned int)i * sizeof(double));
        }
      } else if (i - 1 >= 0) {
        memcpy(&TrialState->lambdaStopTestPrev.data[0],
               &TrialState->lambdaStopTest.data[0],
               (unsigned int)i * sizeof(double));
      }
    } else if (i - 1 >= 0) {
      memcpy(&TrialState->lambdaStopTestPrev.data[0],
             &TrialState->lambdaStopTest.data[0],
             (unsigned int)i * sizeof(double));
    }
    if (isFeasible &&
        (MeritFunction->nlpDualFeasError <= 1.0E-6 * optimRelativeFactor) &&
        (MeritFunction->nlpComplError <= 1.0E-6 * optimRelativeFactor)) {
      Flags->done = true;
      TrialState->sqpExitFlag = 1;
    } else {
      Flags->done = false;
      if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
        Flags->done = true;
        TrialState->sqpExitFlag = -3;
      } else {
        bool guard1 = false;
        guard1 = false;
        if (TrialState->sqpIterations > 0) {
          bool dxTooSmall;
          bool exitg1;
          dxTooSmall = true;
          rankR = (unsigned short)WorkingSet->nVar;
          idx = 0;
          exitg1 = false;
          while ((!exitg1) && (idx <= rankR - 1)) {
            if (1.0E-6 * fmax(1.0, fabs(TrialState->xstarsqp[idx])) <=
                fabs(TrialState->delta_x.data[idx])) {
              dxTooSmall = false;
              exitg1 = true;
            } else {
              idx++;
            }
          }
          if (dxTooSmall) {
            if (!isFeasible) {
              if (Flags->stepType != 2) {
                Flags->stepType = 2;
                Flags->failedLineSearch = false;
                Flags->stepAccepted = false;
                guard1 = true;
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = -2;
              }
            } else {
              int nActiveConstr;
              nActiveConstr = WorkingSet->nActiveConstr;
              if (WorkingSet->nActiveConstr > 0) {
                int ix;
                int u1;
                updateWorkingSetForNewQP(
                    TrialState->xstarsqp, WorkingSet, WorkingSet->sizes[2],
                    TrialState->mNonlinIneq, TrialState->cIneq.data,
                    TrialState->cEq, WorkingSet->sizes[3], lb,
                    WorkingSet->sizes[4], ub, WorkingSet->sizes[0]);
                rankR = (unsigned short)nVar;
                for (k = 0; k < nActiveConstr; k++) {
                  TrialState->lambda.data[k] = 0.0;
                  idx_max = WorkingSet->ldA * k;
                  ix = QRManager->ldq * k;
                  for (idx = 0; idx < rankR; idx++) {
                    QRManager->QR.data[ix + idx] =
                        WorkingSet->ATwset.data[idx_max + idx];
                  }
                }
                QRManager->usedPivoting = true;
                QRManager->mrows = nVar;
                QRManager->ncols = nActiveConstr;
                if (nVar <= nActiveConstr) {
                  u1 = nVar;
                } else {
                  u1 = nActiveConstr;
                }
                QRManager->minRowCol = u1;
                xgeqp3(QRManager->QR.data, QRManager->QR.size, nVar,
                       nActiveConstr, QRManager->jpvt.data, QRManager->tau.data,
                       &QRManager->tau.size[0]);
                rankR = QRManager->minRowCol;
                for (idx = 0; idx < rankR; idx++) {
                  idx_max = QRManager->ldq * idx + idx;
                  ix = nVar - idx;
                  if (ix - 2 >= 0) {
                    memcpy(&QRManager->Q.data[idx_max + 1],
                           &QRManager->QR.data[idx_max + 1],
                           (unsigned int)(ix - 1) * sizeof(double));
                  }
                }
                xorgqr(nVar, nVar, QRManager->minRowCol, QRManager->Q.data,
                       QRManager->Q.size, QRManager->ldq, QRManager->tau.data);
                if (nVar >= nActiveConstr) {
                  idx_max = nVar;
                } else {
                  idx_max = nActiveConstr;
                }
                smax = fabs(QRManager->QR.data[0]) *
                       fmin(1.4901161193847656E-8,
                            (double)idx_max * 2.2204460492503131E-16);
                rankR = 0;
                idx_max = 0;
                while ((rankR < u1) &&
                       (fabs(QRManager->QR.data[idx_max]) > smax)) {
                  rankR++;
                  idx_max = (idx_max + QRManager->ldq) + 1;
                }
                xgemv(nVar, nVar, QRManager->Q.data, QRManager->ldq,
                      TrialState->grad.data, memspace->workspace_double.data);
                if (rankR != 0) {
                  for (idx = rankR; idx >= 1; idx--) {
                    idx_max = (idx + (idx - 1) * QRManager->ldq) - 1;
                    memspace->workspace_double.data[idx - 1] /=
                        QRManager->QR.data[idx_max];
                    for (k = 0; k <= idx - 2; k++) {
                      ix = (idx - k) - 2;
                      memspace->workspace_double.data[ix] -=
                          memspace->workspace_double.data[idx - 1] *
                          QRManager->QR.data[(idx_max - k) - 1];
                    }
                  }
                }
                if (nActiveConstr <= u1) {
                  u1 = nActiveConstr;
                }
                rankR = (unsigned short)u1;
                for (idx = 0; idx < rankR; idx++) {
                  TrialState->lambda.data[QRManager->jpvt.data[idx] - 1] =
                      memspace->workspace_double.data[idx];
                }
                rankR = mFixed + 159;
                for (idx = mFixed; idx <= rankR; idx++) {
                  TrialState->lambda.data[idx - 1] =
                      -TrialState->lambda.data[idx - 1];
                }
                sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
                             WorkingSet->sizes, WorkingSet->isActiveIdx,
                             WorkingSet->Wid.data, WorkingSet->Wlocalidx.data,
                             memspace->workspace_double.data);
                computeGradLag(
                    memspace->workspace_double.data, WorkingSet->ldA, nVar,
                    TrialState->grad.data, mIneq, WorkingSet->Aineq.data,
                    WorkingSet->Aeq.data, WorkingSet->indexFixed.data,
                    mFixed - 1, WorkingSet->indexLB.data, mLB,
                    WorkingSet->indexUB.data, mUB, TrialState->lambda.data);
                smax = 0.0;
                idx = 0;
                while ((idx <= (unsigned short)nVar - 1) &&
                       ((!rtIsInf(memspace->workspace_double.data[idx])) &&
                        (!rtIsNaN(memspace->workspace_double.data[idx])))) {
                  smax = fmax(smax, fabs(memspace->workspace_double.data[idx]));
                  idx++;
                }
                s = computeComplError(
                    fscales_lineq_constraint_size,
                    fscales_cineq_constraint_size, TrialState->xstarsqp, mIneq,
                    TrialState->cIneq.data, WorkingSet->indexLB.data, mLB, lb,
                    WorkingSet->indexUB.data, mUB, ub, TrialState->lambda.data,
                    mFixed);
                if ((smax <= 1.0E-6 * optimRelativeFactor) &&
                    (s <= 1.0E-6 * optimRelativeFactor)) {
                  MeritFunction->nlpDualFeasError = smax;
                  MeritFunction->nlpComplError = s;
                  MeritFunction->firstOrderOpt = fmax(smax, s);
                  if (i - 1 >= 0) {
                    memcpy(&TrialState->lambdaStopTest.data[0],
                           &TrialState->lambda.data[0],
                           (unsigned int)i * sizeof(double));
                  }
                  Flags->done = true;
                  TrialState->sqpExitFlag = 1;
                } else {
                  Flags->done = true;
                  TrialState->sqpExitFlag = 2;
                }
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = 2;
              }
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1) {
          if (TrialState->sqpIterations >= 200) {
            Flags->done = true;
            TrialState->sqpExitFlag = 0;
          } else if (TrialState->FunctionEvaluations >= 18100) {
            Flags->done = true;
            TrialState->sqpExitFlag = 0;
          }
        }
      }
    }
  }
}

/*
 * Arguments    : struct_T *MeritFunction
 *                const f_struct_T *WorkingSet
 *                c_struct_T *TrialState
 *                const double lb[181]
 *                const double ub[181]
 *                bool *Flags_gradOK
 *                bool *Flags_fevalOK
 *                bool *Flags_done
 *                bool *Flags_stepAccepted
 *                bool *Flags_failedLineSearch
 *                int *Flags_stepType
 * Return Type  : void
 */
void test_exit(struct_T *MeritFunction, const f_struct_T *WorkingSet,
               c_struct_T *TrialState, const double lb[181],
               const double ub[181], bool *Flags_gradOK, bool *Flags_fevalOK,
               bool *Flags_done, bool *Flags_stepAccepted,
               bool *Flags_failedLineSearch, int *Flags_stepType)
{
  double smax;
  int i;
  int idx_max;
  int k;
  int nVar;
  bool isFeasible;
  *Flags_fevalOK = true;
  *Flags_done = false;
  *Flags_stepAccepted = false;
  *Flags_failedLineSearch = false;
  *Flags_stepType = 1;
  nVar = WorkingSet->nVar;
  i = (unsigned short)((((WorkingSet->sizes[0] + WorkingSet->sizes[2]) +
                         WorkingSet->sizes[3]) +
                        WorkingSet->sizes[4]) +
                       160);
  if (i - 1 >= 0) {
    memcpy(&TrialState->lambdaStopTest.data[0], &TrialState->lambdasqp.data[0],
           (unsigned int)i * sizeof(double));
  }
  computeGradLag(
      TrialState->gradLag.data, WorkingSet->ldA, WorkingSet->nVar,
      TrialState->grad.data, WorkingSet->sizes[2], WorkingSet->Aineq.data,
      WorkingSet->Aeq.data, WorkingSet->indexFixed.data, WorkingSet->sizes[0],
      WorkingSet->indexLB.data, WorkingSet->sizes[3], WorkingSet->indexUB.data,
      WorkingSet->sizes[4], TrialState->lambdaStopTest.data);
  if (WorkingSet->nVar < 1) {
    idx_max = 0;
  } else {
    idx_max = 1;
    if (WorkingSet->nVar > 1) {
      smax = fabs(TrialState->grad.data[0]);
      for (k = 2; k <= nVar; k++) {
        double s;
        s = fabs(TrialState->grad.data[k - 1]);
        if (s > smax) {
          idx_max = k;
          smax = s;
        }
      }
    }
  }
  smax = fmax(1.0, fabs(TrialState->grad.data[idx_max - 1]));
  if (rtIsInf(smax)) {
    smax = 1.0;
  }
  MeritFunction->nlpPrimalFeasError = computePrimalFeasError(
      TrialState->xstarsqp, WorkingSet->sizes[2] - TrialState->mNonlinIneq,
      TrialState->mNonlinIneq, TrialState->cIneq.data, TrialState->cEq,
      WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
      WorkingSet->indexUB.data, WorkingSet->sizes[4], ub);
  MeritFunction->feasRelativeFactor =
      fmax(1.0, MeritFunction->nlpPrimalFeasError);
  isFeasible = (MeritFunction->nlpPrimalFeasError <=
                1.0E-6 * MeritFunction->feasRelativeFactor);
  computeDualFeasError(WorkingSet->nVar, TrialState->gradLag.data, Flags_gradOK,
                       &MeritFunction->nlpDualFeasError);
  if (!*Flags_gradOK) {
    *Flags_done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = 0.0;
    MeritFunction->firstOrderOpt = fmax(MeritFunction->nlpDualFeasError, 0.0);
    if (i - 1 >= 0) {
      memcpy(&TrialState->lambdaStopTestPrev.data[0],
             &TrialState->lambdaStopTest.data[0],
             (unsigned int)i * sizeof(double));
    }
    if (isFeasible && (MeritFunction->nlpDualFeasError <= 1.0E-6 * smax)) {
      *Flags_done = true;
      TrialState->sqpExitFlag = 1;
    } else if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
      *Flags_done = true;
      TrialState->sqpExitFlag = -3;
    }
  }
}

/*
 * File trailer for test_exit.c
 *
 * [EOF]
 */
