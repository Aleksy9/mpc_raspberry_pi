/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: feasibleX0ForWorkingSet.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "feasibleX0ForWorkingSet.h"
#include "factorQR.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xorgqr.h"
#include "xzgeqp3.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double workspace_data[]
 *                const int workspace_size[2]
 *                double xCurrent_data[]
 *                f_struct_T *workingset
 *                g_struct_T *qrmanager
 * Return Type  : bool
 */
bool feasibleX0ForWorkingSet(double workspace_data[],
                             const int workspace_size[2],
                             double xCurrent_data[], f_struct_T *workingset,
                             g_struct_T *qrmanager)
{
  static double B_data[1770546];
  double tau_data[1803];
  int ar;
  int b_i;
  int iQR0;
  int jBcol;
  int k;
  int mWConstr;
  int nVar;
  bool nonDegenerateWset;
  mWConstr = workingset->nActiveConstr;
  nVar = workingset->nVar;
  nonDegenerateWset = true;
  if (mWConstr != 0) {
    double c;
    int i;
    int i1;
    int iy;
    for (ar = 0; ar < mWConstr; ar++) {
      c = workingset->bwset.data[ar];
      workspace_data[ar] = c;
      workspace_data[ar + workspace_size[0]] = c;
    }
    iQR0 = workingset->ldA;
    if (mWConstr != 0) {
      iy = 0;
      i = workingset->ldA * (mWConstr - 1) + 1;
      for (ar = 1; iQR0 < 0 ? ar >= i : ar <= i; ar += iQR0) {
        c = 0.0;
        i1 = (ar + nVar) - 1;
        for (jBcol = ar; jBcol <= i1; jBcol++) {
          c += workingset->ATwset.data[jBcol - 1] * xCurrent_data[jBcol - ar];
        }
        workspace_data[iy] -= c;
        iy++;
      }
    }
    if (mWConstr >= nVar) {
      int ldq;
      int ldw;
      i = (unsigned short)nVar;
      qrmanager->usedPivoting = false;
      qrmanager->mrows = mWConstr;
      qrmanager->ncols = nVar;
      for (iQR0 = 0; iQR0 < i; iQR0++) {
        iy = qrmanager->ldq * iQR0;
        for (ar = 0; ar < mWConstr; ar++) {
          qrmanager->QR.data[ar + iy] =
              workingset->ATwset.data[iQR0 + workingset->ldA * ar];
        }
        qrmanager->jpvt.data[iQR0] = iQR0 + 1;
      }
      if (mWConstr <= nVar) {
        i = mWConstr;
      } else {
        i = nVar;
      }
      qrmanager->minRowCol = i;
      iQR0 = qrmanager->QR.size[0];
      iy = qrmanager->QR.size[1];
      if (iQR0 <= iy) {
        iy = iQR0;
      }
      if (iy - 1 >= 0) {
        memset(&tau_data[0], 0, (unsigned int)iy * sizeof(double));
      }
      if (i >= 1) {
        qrf(qrmanager->QR.data, qrmanager->QR.size, mWConstr, nVar, i,
            tau_data);
      }
      qrmanager->tau.size[0] = iy;
      if (iy - 1 >= 0) {
        memcpy(&qrmanager->tau.data[0], &tau_data[0],
               (unsigned int)iy * sizeof(double));
      }
      i = qrmanager->minRowCol;
      for (ar = 0; ar < i; ar++) {
        iQR0 = qrmanager->ldq * ar + ar;
        iy = mWConstr - ar;
        if (iy - 2 >= 0) {
          memcpy(&qrmanager->Q.data[iQR0 + 1], &qrmanager->QR.data[iQR0 + 1],
                 (unsigned int)(iy - 1) * sizeof(double));
        }
      }
      xorgqr(mWConstr, mWConstr, qrmanager->minRowCol, qrmanager->Q.data,
             qrmanager->Q.size, qrmanager->ldq, tau_data);
      ldq = qrmanager->ldq;
      ldw = workspace_size[0];
      iQR0 = workspace_size[0] * workspace_size[1];
      if (iQR0 - 1 >= 0) {
        memcpy(&B_data[0], &workspace_data[0],
               (unsigned int)iQR0 * sizeof(double));
      }
      for (b_i = 0; ldw < 0 ? b_i >= ldw : b_i <= ldw; b_i += ldw) {
        i = b_i + 1;
        i1 = b_i + nVar;
        if (i <= i1) {
          memset(&workspace_data[i + -1], 0,
                 (unsigned int)((i1 - i) + 1) * sizeof(double));
        }
      }
      iy = -1;
      for (b_i = 0; ldw < 0 ? b_i >= ldw : b_i <= ldw; b_i += ldw) {
        ar = -1;
        i = b_i + 1;
        i1 = b_i + nVar;
        for (k = i; k <= i1; k++) {
          c = 0.0;
          for (iQR0 = 0; iQR0 < mWConstr; iQR0++) {
            c += qrmanager->Q.data[(iQR0 + ar) + 1] * B_data[(iQR0 + iy) + 1];
          }
          workspace_data[k - 1] += c;
          ar += ldq;
        }
        iy += ldw;
      }
      for (ar = 0; ar < 2; ar++) {
        jBcol = ldw * ar - 1;
        for (k = nVar; k >= 1; k--) {
          iQR0 = ldq * (k - 1) - 1;
          i = k + jBcol;
          if (workspace_data[i] != 0.0) {
            workspace_data[i] /= qrmanager->QR.data[k + iQR0];
            i1 = (unsigned short)(k - 1);
            for (b_i = 0; b_i < i1; b_i++) {
              int i2;
              i2 = (b_i + jBcol) + 1;
              workspace_data[i2] -=
                  workspace_data[i] * qrmanager->QR.data[(b_i + iQR0) + 1];
            }
          }
        }
      }
    } else {
      int ldq;
      int ldw;
      factorQR(qrmanager, workingset->ATwset.data, nVar, mWConstr,
               workingset->ldA);
      i = qrmanager->minRowCol;
      for (ar = 0; ar < i; ar++) {
        iQR0 = qrmanager->ldq * ar + ar;
        iy = qrmanager->mrows - ar;
        if (iy - 2 >= 0) {
          memcpy(&qrmanager->Q.data[iQR0 + 1], &qrmanager->QR.data[iQR0 + 1],
                 (unsigned int)(iy - 1) * sizeof(double));
        }
      }
      xorgqr(qrmanager->mrows, qrmanager->minRowCol, qrmanager->minRowCol,
             qrmanager->Q.data, qrmanager->Q.size, qrmanager->ldq,
             qrmanager->tau.data);
      ldq = qrmanager->ldq;
      ldw = workspace_size[0];
      for (ar = 0; ar < 2; ar++) {
        jBcol = ldw * ar;
        for (b_i = 0; b_i < mWConstr; b_i++) {
          iQR0 = ldq * b_i;
          iy = b_i + jBcol;
          c = workspace_data[iy];
          i = (unsigned short)b_i;
          for (k = 0; k < i; k++) {
            c -= qrmanager->QR.data[k + iQR0] * workspace_data[k + jBcol];
          }
          workspace_data[iy] = c / qrmanager->QR.data[b_i + iQR0];
        }
      }
      iQR0 = workspace_size[0] * workspace_size[1];
      if (iQR0 - 1 >= 0) {
        memcpy(&B_data[0], &workspace_data[0],
               (unsigned int)iQR0 * sizeof(double));
      }
      for (b_i = 0; ldw < 0 ? b_i >= ldw : b_i <= ldw; b_i += ldw) {
        i = b_i + 1;
        i1 = b_i + nVar;
        if (i <= i1) {
          memset(&workspace_data[i + -1], 0,
                 (unsigned int)((i1 - i) + 1) * sizeof(double));
        }
      }
      iy = 0;
      for (b_i = 0; ldw < 0 ? b_i >= ldw : b_i <= ldw; b_i += ldw) {
        ar = -1;
        i = iy + 1;
        i1 = iy + mWConstr;
        for (jBcol = i; jBcol <= i1; jBcol++) {
          int i2;
          i2 = b_i + 1;
          iQR0 = b_i + nVar;
          for (k = i2; k <= iQR0; k++) {
            workspace_data[k - 1] +=
                B_data[jBcol - 1] * qrmanager->Q.data[(ar + k) - b_i];
          }
          ar += ldq;
        }
        iy += ldw;
      }
    }
    ar = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (ar <= (unsigned short)nVar - 1) {
        c = workspace_data[ar];
        if (rtIsInf(c) || rtIsNaN(c)) {
          nonDegenerateWset = false;
          exitg1 = 1;
        } else {
          c = workspace_data[ar + workspace_size[0]];
          if (rtIsInf(c) || rtIsNaN(c)) {
            nonDegenerateWset = false;
            exitg1 = 1;
          } else {
            ar++;
          }
        }
      } else {
        double b_v;
        double v;
        iQR0 = nVar - 1;
        for (k = 0; k <= iQR0; k++) {
          workspace_data[k] += xCurrent_data[k];
        }
        if (workingset->probType == 2) {
          v = 0.0;
          if (workingset->Aineq.size[0] != 0) {
            i = (unsigned short)workingset->sizes[2];
            if (i - 1 >= 0) {
              memcpy(&workingset->maxConstrWorkspace.data[0],
                     &workingset->bineq.data[0],
                     (unsigned int)i * sizeof(double));
            }
            e_xgemv(workingset->sizes[2], workingset->Aineq.data,
                    workingset->ldA, workspace_data,
                    workingset->maxConstrWorkspace.data);
            i = (unsigned short)workingset->sizes[2];
            for (ar = 0; ar < i; ar++) {
              c = workingset->maxConstrWorkspace.data[ar] -
                  workspace_data[ar + 181];
              workingset->maxConstrWorkspace.data[ar] = c;
              v = fmax(v, c);
            }
          }
          memcpy(&workingset->maxConstrWorkspace.data[0], &workingset->beq[0],
                 160U * sizeof(double));
          e_xgemv(160, workingset->Aeq.data, workingset->ldA, workspace_data,
                  workingset->maxConstrWorkspace.data);
          for (ar = 0; ar < 160; ar++) {
            i = workingset->sizes[2] + ar;
            c = (workingset->maxConstrWorkspace.data[ar] -
                 workspace_data[i + 181]) +
                workspace_data[i + 341];
            workingset->maxConstrWorkspace.data[ar] = c;
            v = fmax(v, fabs(c));
          }
        } else {
          v = 0.0;
          if (workingset->Aineq.size[0] != 0) {
            i = (unsigned short)workingset->sizes[2];
            if (i - 1 >= 0) {
              memcpy(&workingset->maxConstrWorkspace.data[0],
                     &workingset->bineq.data[0],
                     (unsigned int)i * sizeof(double));
            }
            b_xgemv(workingset->nVar, workingset->sizes[2],
                    workingset->Aineq.data, workingset->ldA, workspace_data,
                    workingset->maxConstrWorkspace.data);
            i = (unsigned short)workingset->sizes[2];
            for (ar = 0; ar < i; ar++) {
              v = fmax(v, workingset->maxConstrWorkspace.data[ar]);
            }
          }
          memcpy(&workingset->maxConstrWorkspace.data[0], &workingset->beq[0],
                 160U * sizeof(double));
          b_xgemv(workingset->nVar, 160, workingset->Aeq.data, workingset->ldA,
                  workspace_data, workingset->maxConstrWorkspace.data);
          for (ar = 0; ar < 160; ar++) {
            v = fmax(v, fabs(workingset->maxConstrWorkspace.data[ar]));
          }
        }
        if (workingset->sizes[3] > 0) {
          i = (unsigned short)workingset->sizes[3];
          for (ar = 0; ar < i; ar++) {
            iQR0 = workingset->indexLB.data[ar] - 1;
            v = fmax(v, -workspace_data[iQR0] - workingset->lb.data[iQR0]);
          }
        }
        if (workingset->sizes[4] > 0) {
          i = (unsigned short)workingset->sizes[4];
          for (ar = 0; ar < i; ar++) {
            iQR0 = workingset->indexUB.data[ar] - 1;
            v = fmax(v, workspace_data[iQR0] - workingset->ub.data[iQR0]);
          }
        }
        if (workingset->sizes[0] > 0) {
          i = (unsigned short)workingset->sizes[0];
          for (ar = 0; ar < i; ar++) {
            v = fmax(
                v,
                fabs(workspace_data[workingset->indexFixed.data[ar] - 1] -
                     workingset->ub.data[workingset->indexFixed.data[ar] - 1]));
          }
        }
        iy = workspace_size[0] - 1;
        if (workingset->probType == 2) {
          b_v = 0.0;
          if (workingset->Aineq.size[0] != 0) {
            i = (unsigned short)workingset->sizes[2];
            if (i - 1 >= 0) {
              memcpy(&workingset->maxConstrWorkspace.data[0],
                     &workingset->bineq.data[0],
                     (unsigned int)i * sizeof(double));
            }
            c_xgemv(181, workingset->sizes[2], workingset->Aineq.data,
                    workingset->ldA, workspace_data, workspace_size[0] + 1,
                    workingset->maxConstrWorkspace.data);
            i = (unsigned short)workingset->sizes[2];
            for (ar = 0; ar < i; ar++) {
              c = workingset->maxConstrWorkspace.data[ar] -
                  workspace_data[(iy + ar) + 182];
              workingset->maxConstrWorkspace.data[ar] = c;
              b_v = fmax(b_v, c);
            }
          }
          memcpy(&workingset->maxConstrWorkspace.data[0], &workingset->beq[0],
                 160U * sizeof(double));
          c_xgemv(181, 160, workingset->Aeq.data, workingset->ldA,
                  workspace_data, workspace_size[0] + 1,
                  workingset->maxConstrWorkspace.data);
          for (ar = 0; ar < 160; ar++) {
            i = (iy + workingset->sizes[2]) + ar;
            c = (workingset->maxConstrWorkspace.data[ar] -
                 workspace_data[i + 182]) +
                workspace_data[i + 342];
            workingset->maxConstrWorkspace.data[ar] = c;
            b_v = fmax(b_v, fabs(c));
          }
        } else {
          b_v = 0.0;
          if (workingset->Aineq.size[0] != 0) {
            i = (unsigned short)workingset->sizes[2];
            if (i - 1 >= 0) {
              memcpy(&workingset->maxConstrWorkspace.data[0],
                     &workingset->bineq.data[0],
                     (unsigned int)i * sizeof(double));
            }
            c_xgemv(workingset->nVar, workingset->sizes[2],
                    workingset->Aineq.data, workingset->ldA, workspace_data,
                    workspace_size[0] + 1, workingset->maxConstrWorkspace.data);
            i = (unsigned short)workingset->sizes[2];
            for (ar = 0; ar < i; ar++) {
              b_v = fmax(b_v, workingset->maxConstrWorkspace.data[ar]);
            }
          }
          memcpy(&workingset->maxConstrWorkspace.data[0], &workingset->beq[0],
                 160U * sizeof(double));
          c_xgemv(workingset->nVar, 160, workingset->Aeq.data, workingset->ldA,
                  workspace_data, workspace_size[0] + 1,
                  workingset->maxConstrWorkspace.data);
          for (ar = 0; ar < 160; ar++) {
            b_v = fmax(b_v, fabs(workingset->maxConstrWorkspace.data[ar]));
          }
        }
        if (workingset->sizes[3] > 0) {
          i = (unsigned short)workingset->sizes[3];
          for (ar = 0; ar < i; ar++) {
            iQR0 = workingset->indexLB.data[ar];
            b_v = fmax(b_v, -workspace_data[iy + iQR0] -
                                workingset->lb.data[iQR0 - 1]);
          }
        }
        if (workingset->sizes[4] > 0) {
          i = (unsigned short)workingset->sizes[4];
          for (ar = 0; ar < i; ar++) {
            iQR0 = workingset->indexUB.data[ar];
            b_v = fmax(b_v, workspace_data[iy + iQR0] -
                                workingset->ub.data[iQR0 - 1]);
          }
        }
        if (workingset->sizes[0] > 0) {
          i = (unsigned short)workingset->sizes[0];
          for (ar = 0; ar < i; ar++) {
            b_v = fmax(
                b_v,
                fabs(workspace_data[iy + workingset->indexFixed.data[ar]] -
                     workingset->ub.data[workingset->indexFixed.data[ar] - 1]));
          }
        }
        if ((v <= 2.2204460492503131E-16) || (v < b_v)) {
          i = (unsigned short)nVar;
          memcpy(&xCurrent_data[0], &workspace_data[0],
                 (unsigned int)i * sizeof(double));
        } else {
          i = (unsigned short)nVar;
          for (k = 0; k < i; k++) {
            xCurrent_data[k] = workspace_data[workspace_size[0] + k];
          }
        }
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return nonDegenerateWset;
}

/*
 * File trailer for feasibleX0ForWorkingSet.c
 *
 * [EOF]
 */
