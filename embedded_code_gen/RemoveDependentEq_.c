/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: RemoveDependentEq_.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "RemoveDependentEq_.h"
#include "countsort.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "xorgqr.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : e_struct_T *memspace
 *                f_struct_T *workingset
 *                g_struct_T *qrmanager
 * Return Type  : int
 */
int RemoveDependentEq_(e_struct_T *memspace, f_struct_T *workingset,
                       g_struct_T *qrmanager)
{
  int idx;
  int idxDiag;
  int idx_col;
  int k;
  int mTotalWorkingEq_tmp_tmp;
  int mWorkingFixed;
  int n;
  int nDepInd;
  mWorkingFixed = workingset->nWConstr[0];
  mTotalWorkingEq_tmp_tmp = workingset->nWConstr[0] + workingset->nWConstr[1];
  nDepInd = 0;
  if (mTotalWorkingEq_tmp_tmp > 0) {
    double tol;
    int i;
    int i1;
    int u0;
    i = (unsigned short)workingset->nVar;
    for (idxDiag = 0; idxDiag < mTotalWorkingEq_tmp_tmp; idxDiag++) {
      for (idx_col = 0; idx_col < i; idx_col++) {
        qrmanager->QR.data[idxDiag + qrmanager->ldq * idx_col] =
            workingset->ATwset.data[idx_col + workingset->ldA * idxDiag];
      }
    }
    nDepInd = mTotalWorkingEq_tmp_tmp - workingset->nVar;
    if (nDepInd <= 0) {
      nDepInd = 0;
    }
    memset(&qrmanager->jpvt.data[0], 0, (unsigned int)i * sizeof(int));
    i1 = mTotalWorkingEq_tmp_tmp * workingset->nVar;
    if (i1 == 0) {
      qrmanager->mrows = mTotalWorkingEq_tmp_tmp;
      qrmanager->ncols = workingset->nVar;
      qrmanager->minRowCol = 0;
    } else {
      qrmanager->usedPivoting = true;
      qrmanager->mrows = mTotalWorkingEq_tmp_tmp;
      qrmanager->ncols = workingset->nVar;
      idxDiag = workingset->nVar;
      if (mTotalWorkingEq_tmp_tmp <= idxDiag) {
        idxDiag = mTotalWorkingEq_tmp_tmp;
      }
      qrmanager->minRowCol = idxDiag;
      xgeqp3(qrmanager->QR.data, qrmanager->QR.size, mTotalWorkingEq_tmp_tmp,
             workingset->nVar, qrmanager->jpvt.data, qrmanager->tau.data,
             &qrmanager->tau.size[0]);
    }
    tol = 100.0 * (double)workingset->nVar * 2.2204460492503131E-16;
    u0 = workingset->nVar;
    if (u0 > mTotalWorkingEq_tmp_tmp) {
      u0 = mTotalWorkingEq_tmp_tmp;
    }
    idxDiag = u0 + qrmanager->ldq * (u0 - 1);
    while ((idxDiag > 0) && (fabs(qrmanager->QR.data[idxDiag - 1]) < tol)) {
      idxDiag = (idxDiag - qrmanager->ldq) - 1;
      nDepInd++;
    }
    if (nDepInd > 0) {
      bool exitg1;
      idx_col = qrmanager->minRowCol;
      for (idx = 0; idx < idx_col; idx++) {
        idxDiag = qrmanager->ldq * idx + idx;
        n = qrmanager->mrows - idx;
        if (n - 2 >= 0) {
          memcpy(&qrmanager->Q.data[idxDiag + 1],
                 &qrmanager->QR.data[idxDiag + 1],
                 (unsigned int)(n - 1) * sizeof(double));
        }
      }
      xorgqr(qrmanager->mrows, qrmanager->mrows, qrmanager->minRowCol,
             qrmanager->Q.data, qrmanager->Q.size, qrmanager->ldq,
             qrmanager->tau.data);
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= nDepInd - 1)) {
        double qtb;
        idxDiag = qrmanager->ldq * ((mTotalWorkingEq_tmp_tmp - idx) - 1);
        qtb = 0.0;
        for (k = 0; k < mTotalWorkingEq_tmp_tmp; k++) {
          qtb += qrmanager->Q.data[idxDiag + k] * workingset->bwset.data[k];
        }
        if (fabs(qtb) >= tol) {
          nDepInd = -1;
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }
    if (nDepInd > 0) {
      for (idx_col = 0; idx_col < mTotalWorkingEq_tmp_tmp; idx_col++) {
        idxDiag = qrmanager->ldq * idx_col;
        n = workingset->ldA * idx_col;
        for (k = 0; k < i; k++) {
          qrmanager->QR.data[idxDiag + k] = workingset->ATwset.data[n + k];
        }
      }
      for (idx = 0; idx < mWorkingFixed; idx++) {
        qrmanager->jpvt.data[idx] = 1;
      }
      i = workingset->nWConstr[0] + 1;
      if (i <= mTotalWorkingEq_tmp_tmp) {
        memset(&qrmanager->jpvt.data[i + -1], 0,
               (unsigned int)((mTotalWorkingEq_tmp_tmp - i) + 1) * sizeof(int));
      }
      if (i1 == 0) {
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = mTotalWorkingEq_tmp_tmp;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = mTotalWorkingEq_tmp_tmp;
        qrmanager->minRowCol = u0;
        xgeqp3(qrmanager->QR.data, qrmanager->QR.size, workingset->nVar,
               mTotalWorkingEq_tmp_tmp, qrmanager->jpvt.data,
               qrmanager->tau.data, &qrmanager->tau.size[0]);
      }
      for (idx = 0; idx < nDepInd; idx++) {
        memspace->workspace_int.data[idx] =
            qrmanager->jpvt.data[(mTotalWorkingEq_tmp_tmp - nDepInd) + idx];
      }
      countsort(memspace->workspace_int.data, nDepInd,
                memspace->workspace_sort.data, 1, mTotalWorkingEq_tmp_tmp);
      for (idx = nDepInd; idx >= 1; idx--) {
        i = workingset->nWConstr[0] + workingset->nWConstr[1];
        if (i != 0) {
          i1 = memspace->workspace_int.data[idx - 1];
          if (i1 <= i) {
            if ((workingset->nActiveConstr == i) || (i1 == i)) {
              workingset->mEqRemoved++;
              workingset->indexEqRemoved[workingset->mEqRemoved - 1] =
                  workingset->Wlocalidx
                      .data[memspace->workspace_int.data[idx - 1] - 1];
              removeConstr(workingset, memspace->workspace_int.data[idx - 1]);
            } else {
              workingset->mEqRemoved++;
              idxDiag = workingset->Wid.data[i1 - 1] - 1;
              workingset->indexEqRemoved[workingset->mEqRemoved - 1] =
                  workingset->Wlocalidx.data[i1 - 1];
              workingset->isActiveConstr.data
                  [(workingset->isActiveIdx[workingset->Wid.data[i1 - 1] - 1] +
                    workingset->Wlocalidx.data[i1 - 1]) -
                   2] = false;
              workingset->Wid.data[i1 - 1] = workingset->Wid.data[i - 1];
              workingset->Wlocalidx.data[i1 - 1] =
                  workingset->Wlocalidx.data[i - 1];
              idx_col = (unsigned short)workingset->nVar;
              for (n = 0; n < idx_col; n++) {
                workingset->ATwset.data[n + workingset->ldA * (i1 - 1)] =
                    workingset->ATwset.data[n + workingset->ldA * (i - 1)];
              }
              workingset->bwset.data[i1 - 1] = workingset->bwset.data[i - 1];
              workingset->Wid.data[i - 1] =
                  workingset->Wid.data[workingset->nActiveConstr - 1];
              workingset->Wlocalidx.data[i - 1] =
                  workingset->Wlocalidx.data[workingset->nActiveConstr - 1];
              i1 = (unsigned short)workingset->nVar;
              for (n = 0; n < i1; n++) {
                workingset->ATwset.data[n + workingset->ldA * (i - 1)] =
                    workingset->ATwset
                        .data[n + workingset->ldA *
                                      (workingset->nActiveConstr - 1)];
              }
              workingset->bwset.data[i - 1] =
                  workingset->bwset.data[workingset->nActiveConstr - 1];
              workingset->nActiveConstr--;
              workingset->nWConstr[idxDiag]--;
            }
          }
        }
      }
    }
  }
  return nDepInd;
}

/*
 * File trailer for RemoveDependentEq_.c
 *
 * [EOF]
 */
