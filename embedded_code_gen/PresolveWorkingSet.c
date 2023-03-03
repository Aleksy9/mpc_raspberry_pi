/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: PresolveWorkingSet.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "PresolveWorkingSet.h"
#include "RemoveDependentEq_.h"
#include "countsort.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : c_struct_T *solution
 *                e_struct_T *memspace
 *                f_struct_T *workingset
 *                g_struct_T *qrmanager
 * Return Type  : void
 */
void PresolveWorkingSet(c_struct_T *solution, e_struct_T *memspace,
                        f_struct_T *workingset, g_struct_T *qrmanager)
{
  int i;
  int idx_col;
  int idx_global;
  int k;
  solution->state = 82;
  i = RemoveDependentEq_(memspace, workingset, qrmanager);
  if ((i != -1) && (workingset->nActiveConstr <= qrmanager->ldq)) {
    double tol;
    int i1;
    int idxEndIneq;
    int idxStartIneq;
    int nFixedConstr_tmp_tmp;
    int nVar_tmp;
    bool guard1 = false;
    bool okWorkingSet;
    idxStartIneq = workingset->nActiveConstr;
    nFixedConstr_tmp_tmp = workingset->nWConstr[0] + workingset->nWConstr[1];
    nVar_tmp = workingset->nVar;
    if ((workingset->nWConstr[2] + workingset->nWConstr[3]) +
            workingset->nWConstr[4] >
        0) {
      tol = 100.0 * (double)workingset->nVar * 2.2204460492503131E-16;
      for (idx_global = 0; idx_global < nFixedConstr_tmp_tmp; idx_global++) {
        qrmanager->jpvt.data[idx_global] = 1;
      }
      i = nFixedConstr_tmp_tmp + 1;
      if (i <= idxStartIneq) {
        memset(&qrmanager->jpvt.data[i + -1], 0,
               (unsigned int)((idxStartIneq - i) + 1) * sizeof(int));
      }
      i = workingset->nActiveConstr;
      for (idx_col = 0; idx_col < i; idx_col++) {
        idxEndIneq = qrmanager->ldq * idx_col;
        idx_global = workingset->ldA * idx_col;
        i1 = (unsigned short)nVar_tmp;
        for (k = 0; k < i1; k++) {
          qrmanager->QR.data[idxEndIneq + k] =
              workingset->ATwset.data[idx_global + k];
        }
      }
      if (workingset->nVar * workingset->nActiveConstr == 0) {
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = workingset->nActiveConstr;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = workingset->nActiveConstr;
        idxStartIneq = workingset->nVar;
        idxEndIneq = workingset->nActiveConstr;
        if (idxStartIneq <= idxEndIneq) {
          idxEndIneq = idxStartIneq;
        }
        qrmanager->minRowCol = idxEndIneq;
        xgeqp3(qrmanager->QR.data, qrmanager->QR.size, workingset->nVar,
               workingset->nActiveConstr, qrmanager->jpvt.data,
               qrmanager->tau.data, &qrmanager->tau.size[0]);
      }
      idxStartIneq = 0;
      for (idx_global = workingset->nActiveConstr - 1;
           idx_global + 1 > nVar_tmp; idx_global--) {
        idxStartIneq++;
        memspace->workspace_int.data[idxStartIneq - 1] =
            qrmanager->jpvt.data[idx_global];
      }
      if (idx_global + 1 <= workingset->nVar) {
        idxEndIneq = idx_global + qrmanager->ldq * idx_global;
        while ((idx_global + 1 > nFixedConstr_tmp_tmp) &&
               (fabs(qrmanager->QR.data[idxEndIneq]) < tol)) {
          idxStartIneq++;
          memspace->workspace_int.data[idxStartIneq - 1] =
              qrmanager->jpvt.data[idx_global];
          idx_global--;
          idxEndIneq = (idxEndIneq - qrmanager->ldq) - 1;
        }
      }
      countsort(memspace->workspace_int.data, idxStartIneq,
                memspace->workspace_sort.data, nFixedConstr_tmp_tmp + 1,
                workingset->nActiveConstr);
      for (idx_global = idxStartIneq; idx_global >= 1; idx_global--) {
        removeConstr(workingset, memspace->workspace_int.data[idx_global - 1]);
      }
    }
    okWorkingSet = feasibleX0ForWorkingSet(
        memspace->workspace_double.data, memspace->workspace_double.size,
        solution->xstar.data, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      idxStartIneq = workingset->nActiveConstr;
      i = workingset->nWConstr[0] + workingset->nWConstr[1];
      if ((workingset->nWConstr[2] + workingset->nWConstr[3]) +
              workingset->nWConstr[4] >
          0) {
        tol = 1000.0 * (double)workingset->nVar * 2.2204460492503131E-16;
        for (idx_global = 0; idx_global < i; idx_global++) {
          qrmanager->jpvt.data[idx_global] = 1;
        }
        i1 = i + 1;
        if (i1 <= idxStartIneq) {
          memset(&qrmanager->jpvt.data[i1 + -1], 0,
                 (unsigned int)((idxStartIneq - i1) + 1) * sizeof(int));
        }
        i1 = workingset->nActiveConstr;
        for (idx_col = 0; idx_col < i1; idx_col++) {
          idxEndIneq = qrmanager->ldq * idx_col;
          idx_global = workingset->ldA * idx_col;
          idxStartIneq = (unsigned short)nVar_tmp;
          for (k = 0; k < idxStartIneq; k++) {
            qrmanager->QR.data[idxEndIneq + k] =
                workingset->ATwset.data[idx_global + k];
          }
        }
        if (workingset->nVar * workingset->nActiveConstr == 0) {
          qrmanager->mrows = workingset->nVar;
          qrmanager->ncols = workingset->nActiveConstr;
          qrmanager->minRowCol = 0;
        } else {
          qrmanager->usedPivoting = true;
          qrmanager->mrows = workingset->nVar;
          qrmanager->ncols = workingset->nActiveConstr;
          idxStartIneq = workingset->nVar;
          idxEndIneq = workingset->nActiveConstr;
          if (idxStartIneq <= idxEndIneq) {
            idxEndIneq = idxStartIneq;
          }
          qrmanager->minRowCol = idxEndIneq;
          xgeqp3(qrmanager->QR.data, qrmanager->QR.size, workingset->nVar,
                 workingset->nActiveConstr, qrmanager->jpvt.data,
                 qrmanager->tau.data, &qrmanager->tau.size[0]);
        }
        idxStartIneq = 0;
        for (idx_global = workingset->nActiveConstr - 1;
             idx_global + 1 > nVar_tmp; idx_global--) {
          idxStartIneq++;
          memspace->workspace_int.data[idxStartIneq - 1] =
              qrmanager->jpvt.data[idx_global];
        }
        if (idx_global + 1 <= workingset->nVar) {
          idxEndIneq = idx_global + qrmanager->ldq * idx_global;
          while ((idx_global + 1 > i) &&
                 (fabs(qrmanager->QR.data[idxEndIneq]) < tol)) {
            idxStartIneq++;
            memspace->workspace_int.data[idxStartIneq - 1] =
                qrmanager->jpvt.data[idx_global];
            idx_global--;
            idxEndIneq = (idxEndIneq - qrmanager->ldq) - 1;
          }
        }
        countsort(memspace->workspace_int.data, idxStartIneq,
                  memspace->workspace_sort.data, i + 1,
                  workingset->nActiveConstr);
        for (idx_global = idxStartIneq; idx_global >= 1; idx_global--) {
          removeConstr(workingset,
                       memspace->workspace_int.data[idx_global - 1]);
        }
      }
      okWorkingSet = feasibleX0ForWorkingSet(
          memspace->workspace_double.data, memspace->workspace_double.size,
          solution->xstar.data, workingset, qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1 && (workingset->nWConstr[0] + workingset->nWConstr[1] ==
                   workingset->nVar)) {
      tol = maxConstraintViolation(workingset, solution->xstar.data);
      if (tol > 1.0E-6) {
        solution->state = -2;
      }
    }
  } else {
    int idxEndIneq;
    int idxStartIneq;
    solution->state = -3;
    idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
    idxEndIneq = workingset->nActiveConstr;
    for (idx_global = idxStartIneq; idx_global <= idxEndIneq; idx_global++) {
      workingset->isActiveConstr.data
          [(workingset->isActiveIdx[workingset->Wid.data[idx_global - 1] - 1] +
            workingset->Wlocalidx.data[idx_global - 1]) -
           2] = false;
    }
    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr =
        workingset->nWConstr[0] + workingset->nWConstr[1];
  }
}

/*
 * File trailer for PresolveWorkingSet.c
 *
 * [EOF]
 */
