/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: iterate.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "iterate.h"
#include "addBoundToActiveSetMatrix_.h"
#include "checkStoppingAndUpdateFval.h"
#include "computeFval_ReuseHx.h"
#include "computeGrad_StoreHx.h"
#include "compute_deltax.h"
#include "deleteColMoveEnd.h"
#include "factorQR.h"
#include "feasibleratiotest.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "strcmp.h"
#include "xgemv.h"
#include "xnrm2.h"
#include "xorgqr.h"
#include "xrotg.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double H[32761]
 *                const double f_data[]
 *                c_struct_T *solution
 *                e_struct_T *memspace
 *                f_struct_T *workingset
 *                g_struct_T *qrmanager
 *                h_struct_T *cholmanager
 *                d_struct_T *objective
 *                const char options_SolverName[7]
 *                double options_StepTolerance
 *                double options_ObjectiveLimit
 *                int runTimeOptions_MaxIterations
 * Return Type  : void
 */
void iterate(const double H[32761], const double f_data[], c_struct_T *solution,
             e_struct_T *memspace, f_struct_T *workingset,
             g_struct_T *qrmanager, h_struct_T *cholmanager,
             d_struct_T *objective, const char options_SolverName[7],
             double options_StepTolerance, double options_ObjectiveLimit,
             int runTimeOptions_MaxIterations)
{
  double y_data[1803];
  double c;
  double d;
  double s;
  double temp;
  int TYPE;
  int activeSetChangeID;
  int globalActiveConstrIdx;
  int i;
  int iac;
  int idx;
  int iy;
  int n;
  int nActiveConstr;
  int nVar;
  bool subProblemChanged;
  bool updateFval;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  TYPE = objective->objtype;
  nVar = workingset->nVar;
  globalActiveConstrIdx = 0;
  computeGrad_StoreHx(objective, H, f_data, solution->xstar.data);
  solution->fstar = computeFval_ReuseHx(
      objective, memspace->workspace_double.data, f_data, solution->xstar.data);
  if (solution->iterations < runTimeOptions_MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }
  n = workingset->mConstrMax;
  memset(&solution->lambda.data[0], 0, (unsigned int)n * sizeof(double));
  int exitg1;
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      int iQR0;
      int iyend;
      bool guard1 = false;
      guard1 = false;
      if (subProblemChanged) {
        switch (activeSetChangeID) {
        case 1:
          nActiveConstr = workingset->ldA * (workingset->nActiveConstr - 1);
          iyend = qrmanager->mrows;
          iQR0 = qrmanager->ncols + 1;
          if (iyend <= iQR0) {
            iQR0 = iyend;
          }
          qrmanager->minRowCol = iQR0;
          iy = qrmanager->ldq * qrmanager->ncols;
          iQR0 = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            iyend = iy + qrmanager->mrows;
            if (iy + 1 <= iyend) {
              memset(&qrmanager->QR.data[iy], 0,
                     (unsigned int)(iyend - iy) * sizeof(double));
            }
            i = qrmanager->ldq * (qrmanager->mrows - 1) + 1;
            for (iac = 1; iQR0 < 0 ? iac >= i : iac <= i; iac += iQR0) {
              c = 0.0;
              iyend = (iac + qrmanager->mrows) - 1;
              for (n = iac; n <= iyend; n++) {
                c += qrmanager->Q.data[n - 1] *
                     workingset->ATwset.data[(nActiveConstr + n) - iac];
              }
              qrmanager->QR.data[iy] += c;
              iy++;
            }
          }
          qrmanager->ncols++;
          qrmanager->jpvt.data[qrmanager->ncols - 1] = qrmanager->ncols;
          for (idx = qrmanager->mrows - 2; idx + 2 > qrmanager->ncols; idx--) {
            iyend = qrmanager->ldq * (qrmanager->ncols - 1);
            i = (idx + iyend) + 1;
            d = qrmanager->QR.data[i];
            xrotg(&qrmanager->QR.data[idx + iyend], &d, &c, &s);
            qrmanager->QR.data[i] = d;
            iQR0 = qrmanager->ldq * idx;
            n = qrmanager->mrows;
            if (qrmanager->mrows >= 1) {
              iy = qrmanager->ldq + iQR0;
              for (iac = 0; iac < n; iac++) {
                iyend = iy + iac;
                nActiveConstr = iQR0 + iac;
                temp = c * qrmanager->Q.data[nActiveConstr] +
                       s * qrmanager->Q.data[iyend];
                qrmanager->Q.data[iyend] = c * qrmanager->Q.data[iyend] -
                                           s * qrmanager->Q.data[nActiveConstr];
                qrmanager->Q.data[nActiveConstr] = temp;
              }
            }
          }
          break;
        case -1:
          deleteColMoveEnd(qrmanager, globalActiveConstrIdx);
          break;
        default:
          factorQR(qrmanager, workingset->ATwset.data, nVar,
                   workingset->nActiveConstr, workingset->ldA);
          i = qrmanager->minRowCol;
          for (idx = 0; idx < i; idx++) {
            iQR0 = qrmanager->ldq * idx + idx;
            n = qrmanager->mrows - idx;
            if (n - 2 >= 0) {
              memcpy(&qrmanager->Q.data[iQR0 + 1],
                     &qrmanager->QR.data[iQR0 + 1],
                     (unsigned int)(n - 1) * sizeof(double));
            }
          }
          xorgqr(qrmanager->mrows, qrmanager->mrows, qrmanager->minRowCol,
                 qrmanager->Q.data, qrmanager->Q.size, qrmanager->ldq,
                 qrmanager->tau.data);
          break;
        }
        compute_deltax(H, solution, memspace, qrmanager, cholmanager, objective,
                       b_strcmp(options_SolverName));
        if (solution->state != -5) {
          exitg1 = 1;
        } else if ((b_xnrm2(nVar, solution->searchDir.data) <
                    options_StepTolerance) ||
                   (workingset->nActiveConstr >= nVar)) {
          guard1 = true;
        } else {
          feasibleratiotest(
              solution->xstar.data, solution->searchDir.data,
              memspace->workspace_double.data, memspace->workspace_double.size,
              workingset->nVar, workingset->ldA, workingset->Aineq.data,
              workingset->bineq.data, workingset->lb.data, workingset->ub.data,
              workingset->indexLB.data, workingset->indexUB.data,
              workingset->sizes, workingset->isActiveIdx,
              workingset->isActiveConstr.data, workingset->nWConstr, TYPE == 5,
              &temp, &updateFval, &i, &nActiveConstr);
          if (updateFval) {
            switch (i) {
            case 3:
              workingset->nWConstr[2]++;
              workingset->isActiveConstr
                  .data[(workingset->isActiveIdx[2] + nActiveConstr) - 2] =
                  true;
              workingset->nActiveConstr++;
              workingset->Wid.data[workingset->nActiveConstr - 1] = 3;
              workingset->Wlocalidx.data[workingset->nActiveConstr - 1] =
                  nActiveConstr;
              iQR0 = workingset->ldA * (nActiveConstr - 1);
              iyend = workingset->ldA * (workingset->nActiveConstr - 1);
              i = workingset->nVar - 1;
              for (idx = 0; idx <= i; idx++) {
                workingset->ATwset.data[iyend + idx] =
                    workingset->Aineq.data[iQR0 + idx];
              }
              workingset->bwset.data[workingset->nActiveConstr - 1] =
                  workingset->bineq.data[nActiveConstr - 1];
              break;
            case 4:
              addBoundToActiveSetMatrix_(workingset, 4, nActiveConstr);
              break;
            default:
              addBoundToActiveSetMatrix_(workingset, 5, nActiveConstr);
              break;
            }
            activeSetChangeID = 1;
          } else {
            if (objective->objtype == 5) {
              if (b_xnrm2(objective->nvar, solution->searchDir.data) >
                  100.0 * (double)objective->nvar * 1.4901161193847656E-8) {
                solution->state = 3;
              } else {
                solution->state = 4;
              }
            }
            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }
          if ((nVar >= 1) && (!(temp == 0.0))) {
            iQR0 = nVar - 1;
            for (iac = 0; iac <= iQR0; iac++) {
              solution->xstar.data[iac] += temp * solution->searchDir.data[iac];
            }
          }
          computeGrad_StoreHx(objective, H, f_data, solution->xstar.data);
          updateFval = true;
          checkStoppingAndUpdateFval(&activeSetChangeID, f_data, solution,
                                     memspace, objective, workingset, qrmanager,
                                     options_ObjectiveLimit,
                                     runTimeOptions_MaxIterations, updateFval);
        }
      } else {
        iQR0 = solution->searchDir.size[0];
        iyend = solution->searchDir.size[0];
        if (iyend - 1 >= 0) {
          memcpy(&y_data[0], &solution->searchDir.data[0],
                 (unsigned int)iyend * sizeof(double));
        }
        memset(&y_data[0], 0, (unsigned int)nVar * sizeof(double));
        solution->searchDir.size[0] = iQR0;
        if (iQR0 - 1 >= 0) {
          memcpy(&solution->searchDir.data[0], &y_data[0],
                 (unsigned int)iQR0 * sizeof(double));
        }
        guard1 = true;
      }
      if (guard1) {
        nActiveConstr = qrmanager->ncols;
        if (qrmanager->ncols > 0) {
          bool b_guard1 = false;
          b_guard1 = false;
          if (objective->objtype != 4) {
            temp = 100.0 * (double)qrmanager->mrows * 2.2204460492503131E-16;
            if ((qrmanager->mrows > 0) && (qrmanager->ncols > 0)) {
              updateFval = true;
            } else {
              updateFval = false;
            }
            if (updateFval) {
              bool guard2 = false;
              idx = qrmanager->ncols;
              guard2 = false;
              if (qrmanager->mrows < qrmanager->ncols) {
                iQR0 =
                    qrmanager->mrows + qrmanager->ldq * (qrmanager->ncols - 1);
                while ((idx > qrmanager->mrows) &&
                       (fabs(qrmanager->QR.data[iQR0 - 1]) >= temp)) {
                  idx--;
                  iQR0 -= qrmanager->ldq;
                }
                updateFval = (idx == qrmanager->mrows);
                if (updateFval) {
                  guard2 = true;
                }
              } else {
                guard2 = true;
              }
              if (guard2) {
                iQR0 = idx + qrmanager->ldq * (idx - 1);
                while ((idx >= 1) &&
                       (fabs(qrmanager->QR.data[iQR0 - 1]) >= temp)) {
                  idx--;
                  iQR0 = (iQR0 - qrmanager->ldq) - 1;
                }
                updateFval = (idx == 0);
              }
            }
            if (!updateFval) {
              solution->state = -7;
            } else {
              b_guard1 = true;
            }
          } else {
            b_guard1 = true;
          }
          if (b_guard1) {
            n = qrmanager->ncols;
            xgemv(qrmanager->mrows, qrmanager->ncols, qrmanager->Q.data,
                  qrmanager->ldq, objective->grad.data,
                  memspace->workspace_double.data);
            if (qrmanager->ncols != 0) {
              for (iy = n; iy >= 1; iy--) {
                iQR0 = (iy + (iy - 1) * qrmanager->ldq) - 1;
                memspace->workspace_double.data[iy - 1] /=
                    qrmanager->QR.data[iQR0];
                for (iac = 0; iac <= iy - 2; iac++) {
                  iyend = (iy - iac) - 2;
                  memspace->workspace_double.data[iyend] -=
                      memspace->workspace_double.data[iy - 1] *
                      qrmanager->QR.data[(iQR0 - iac) - 1];
                }
              }
            }
            for (idx = 0; idx < nActiveConstr; idx++) {
              solution->lambda.data[idx] =
                  -memspace->workspace_double.data[idx];
            }
          }
        }
        if ((solution->state != -7) || (workingset->nActiveConstr > nVar)) {
          iQR0 = 0;
          temp = 0.0;
          i = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
          iyend = workingset->nActiveConstr;
          for (idx = i; idx <= iyend; idx++) {
            d = solution->lambda.data[idx - 1];
            if (d < temp) {
              temp = d;
              iQR0 = idx;
            }
          }
          if (iQR0 == 0) {
            solution->state = 1;
          } else {
            activeSetChangeID = -1;
            globalActiveConstrIdx = iQR0;
            subProblemChanged = true;
            removeConstr(workingset, iQR0);
            solution->lambda.data[iQR0 - 1] = 0.0;
          }
        } else {
          iQR0 = workingset->nActiveConstr;
          activeSetChangeID = 0;
          globalActiveConstrIdx = workingset->nActiveConstr;
          subProblemChanged = true;
          removeConstr(workingset, workingset->nActiveConstr);
          solution->lambda.data[iQR0 - 1] = 0.0;
        }
        updateFval = false;
        checkStoppingAndUpdateFval(&activeSetChangeID, f_data, solution,
                                   memspace, objective, workingset, qrmanager,
                                   options_ObjectiveLimit,
                                   runTimeOptions_MaxIterations, updateFval);
      }
    } else {
      if (!updateFval) {
        solution->fstar =
            computeFval_ReuseHx(objective, memspace->workspace_double.data,
                                f_data, solution->xstar.data);
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/*
 * File trailer for iterate.c
 *
 * [EOF]
 */
