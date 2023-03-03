/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_deltax.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "compute_deltax.h"
#include "fullColLDL2_.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "partialColLDL3_.h"
#include "rt_nonfinite.h"
#include "solve.h"
#include "xgemm.h"
#include "xpotrf.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double H[32761]
 *                c_struct_T *solution
 *                e_struct_T *memspace
 *                const g_struct_T *qrmanager
 *                h_struct_T *cholmanager
 *                const d_struct_T *objective
 *                bool alwaysPositiveDef
 * Return Type  : void
 */
void compute_deltax(const double H[32761], c_struct_T *solution,
                    e_struct_T *memspace, const g_struct_T *qrmanager,
                    h_struct_T *cholmanager, const d_struct_T *objective,
                    bool alwaysPositiveDef)
{
  int LDimSizeP1;
  int idx;
  int idx_col;
  int k;
  int mNull_tmp;
  int nVar_tmp;
  nVar_tmp = qrmanager->mrows - 1;
  mNull_tmp = qrmanager->mrows - qrmanager->ncols;
  if (mNull_tmp <= 0) {
    if (nVar_tmp >= 0) {
      memset(&solution->searchDir.data[0], 0,
             (unsigned int)(nVar_tmp + 1) * sizeof(double));
    }
  } else {
    for (idx = 0; idx <= nVar_tmp; idx++) {
      solution->searchDir.data[idx] = -objective->grad.data[idx];
    }
    if (qrmanager->ncols <= 0) {
      switch (objective->objtype) {
      case 5:
        break;
      case 3: {
        double smax;
        int ldw;
        int nVars;
        if (alwaysPositiveDef) {
          cholmanager->ndims = qrmanager->mrows;
          for (idx = 0; idx <= nVar_tmp; idx++) {
            ldw = qrmanager->mrows * idx;
            nVars = cholmanager->ldm * idx;
            for (k = 0; k <= nVar_tmp; k++) {
              cholmanager->FMat.data[nVars + k] = H[ldw + k];
            }
          }
          cholmanager->info = xpotrf(qrmanager->mrows, cholmanager->FMat.data,
                                     cholmanager->ldm);
        } else {
          idx_col = qrmanager->mrows;
          LDimSizeP1 = cholmanager->ldm + 1;
          cholmanager->ndims = qrmanager->mrows;
          for (idx = 0; idx < idx_col; idx++) {
            ldw = qrmanager->mrows * idx;
            nVars = cholmanager->ldm * idx;
            for (k = 0; k < idx_col; k++) {
              cholmanager->FMat.data[nVars + k] = H[ldw + k];
            }
          }
          if (qrmanager->mrows < 1) {
            nVars = -1;
          } else {
            nVars = 0;
            if (qrmanager->mrows > 1) {
              smax = fabs(cholmanager->FMat.data[0]);
              for (k = 2; k <= idx_col; k++) {
                double s;
                s = fabs(cholmanager->FMat.data[(k - 1) * LDimSizeP1]);
                if (s > smax) {
                  nVars = k - 1;
                  smax = s;
                }
              }
            }
          }
          cholmanager->regTol_ = fmax(
              fabs(cholmanager->FMat.data[nVars + cholmanager->ldm * nVars]) *
                  2.2204460492503131E-16,
              0.0);
          if (qrmanager->mrows > 128) {
            bool exitg1;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < idx_col)) {
              nVars = LDimSizeP1 * k + 1;
              ldw = idx_col - k;
              if (k + 48 <= idx_col) {
                partialColLDL3_(cholmanager, nVars, ldw);
                k += 48;
              } else {
                fullColLDL2_(cholmanager, nVars, ldw);
                exitg1 = true;
              }
            }
          } else {
            fullColLDL2_(cholmanager, 1, qrmanager->mrows);
          }
          if (cholmanager->ConvexCheck) {
            idx = 0;
            int exitg2;
            do {
              exitg2 = 0;
              if (idx <= idx_col - 1) {
                if (cholmanager->FMat.data[idx + cholmanager->ldm * idx] <=
                    0.0) {
                  cholmanager->info = -idx - 1;
                  exitg2 = 1;
                } else {
                  idx++;
                }
              } else {
                cholmanager->ConvexCheck = false;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }
        }
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else if (alwaysPositiveDef) {
          solve(cholmanager, solution->searchDir.data);
        } else {
          int i;
          ldw = cholmanager->ndims - 2;
          if (cholmanager->ndims != 0) {
            for (idx_col = 0; idx_col <= ldw + 1; idx_col++) {
              nVars = idx_col + idx_col * cholmanager->ldm;
              i = ldw - idx_col;
              for (idx = 0; idx <= i; idx++) {
                LDimSizeP1 = (idx_col + idx) + 1;
                solution->searchDir.data[LDimSizeP1] -=
                    solution->searchDir.data[idx_col] *
                    cholmanager->FMat.data[(nVars + idx) + 1];
              }
            }
          }
          i = cholmanager->ndims;
          for (idx = 0; idx < i; idx++) {
            solution->searchDir.data[idx] /=
                cholmanager->FMat.data[idx + cholmanager->ldm * idx];
          }
          ldw = cholmanager->ndims;
          if (cholmanager->ndims != 0) {
            for (idx_col = ldw; idx_col >= 1; idx_col--) {
              nVars = (idx_col - 1) * cholmanager->ldm;
              smax = solution->searchDir.data[idx_col - 1];
              i = idx_col + 1;
              for (idx = ldw; idx >= i; idx--) {
                smax -= cholmanager->FMat.data[(nVars + idx) - 1] *
                        solution->searchDir.data[idx - 1];
              }
              solution->searchDir.data[idx_col - 1] = smax;
            }
          }
        }
      } break;
      default: {
        if (alwaysPositiveDef) {
          int ldw;
          idx_col = objective->nvar - 1;
          cholmanager->ndims = objective->nvar;
          for (idx = 0; idx <= idx_col; idx++) {
            int nVars;
            ldw = objective->nvar * idx;
            nVars = cholmanager->ldm * idx;
            for (k = 0; k <= idx_col; k++) {
              cholmanager->FMat.data[nVars + k] = H[ldw + k];
            }
          }
          cholmanager->info =
              xpotrf(objective->nvar, cholmanager->FMat.data, cholmanager->ldm);
          if (cholmanager->info != 0) {
            solution->state = -6;
          } else {
            double smax;
            int i;
            solve(cholmanager, solution->searchDir.data);
            smax = 1.0 / objective->beta;
            ldw = objective->nvar + 1;
            i = qrmanager->mrows;
            for (k = ldw; k <= i; k++) {
              solution->searchDir.data[k - 1] *= smax;
            }
          }
        }
      } break;
      }
    } else {
      int nullStartIdx_tmp;
      nullStartIdx_tmp = qrmanager->ldq * qrmanager->ncols + 1;
      if (objective->objtype == 5) {
        int ldw;
        for (idx = 0; idx < mNull_tmp; idx++) {
          memspace->workspace_double.data[idx] =
              -qrmanager->Q
                   .data[nVar_tmp + qrmanager->ldq * (qrmanager->ncols + idx)];
        }
        ldw = qrmanager->ldq;
        if (qrmanager->mrows != 0) {
          int i;
          memset(&solution->searchDir.data[0], 0,
                 (unsigned int)(nVar_tmp + 1) * sizeof(double));
          LDimSizeP1 = 0;
          i = nullStartIdx_tmp + qrmanager->ldq * (mNull_tmp - 1);
          for (idx = nullStartIdx_tmp; ldw < 0 ? idx >= i : idx <= i;
               idx += ldw) {
            idx_col = idx + nVar_tmp;
            for (k = idx; k <= idx_col; k++) {
              int nVars;
              nVars = k - idx;
              solution->searchDir.data[nVars] +=
                  qrmanager->Q.data[k - 1] *
                  memspace->workspace_double.data[LDimSizeP1];
            }
            LDimSizeP1++;
          }
        }
      } else {
        double smax;
        int i;
        int ldw;
        int nVars;
        if (objective->objtype == 3) {
          xgemm(qrmanager->mrows, mNull_tmp, qrmanager->mrows, H,
                qrmanager->mrows, qrmanager->Q.data, nullStartIdx_tmp,
                qrmanager->ldq, memspace->workspace_double.data,
                memspace->workspace_double.size[0]);
          b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q.data,
                  nullStartIdx_tmp, qrmanager->ldq,
                  memspace->workspace_double.data,
                  memspace->workspace_double.size[0], cholmanager->FMat.data,
                  cholmanager->ldm);
        } else if (alwaysPositiveDef) {
          nVars = qrmanager->mrows;
          ldw = memspace->workspace_double.size[0];
          xgemm(objective->nvar, mNull_tmp, objective->nvar, H, objective->nvar,
                qrmanager->Q.data, nullStartIdx_tmp, qrmanager->ldq,
                memspace->workspace_double.data,
                memspace->workspace_double.size[0]);
          i = objective->nvar + 1;
          for (idx_col = 0; idx_col < mNull_tmp; idx_col++) {
            for (LDimSizeP1 = i; LDimSizeP1 <= nVars; LDimSizeP1++) {
              memspace->workspace_double
                  .data[(LDimSizeP1 +
                         memspace->workspace_double.size[0] * idx_col) -
                        1] =
                  objective->beta *
                  qrmanager->Q
                      .data[(LDimSizeP1 + qrmanager->Q.size[0] *
                                              (idx_col + qrmanager->ncols)) -
                            1];
            }
          }
          b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q.data,
                  nullStartIdx_tmp, qrmanager->ldq,
                  memspace->workspace_double.data, ldw, cholmanager->FMat.data,
                  cholmanager->ldm);
        }
        if (alwaysPositiveDef) {
          cholmanager->ndims = mNull_tmp;
          cholmanager->info =
              xpotrf(mNull_tmp, cholmanager->FMat.data, cholmanager->ldm);
        } else {
          LDimSizeP1 = cholmanager->ldm + 1;
          cholmanager->ndims = mNull_tmp;
          nVars = 0;
          if (mNull_tmp > 1) {
            smax = fabs(cholmanager->FMat.data[0]);
            for (k = 2; k <= mNull_tmp; k++) {
              double s;
              s = fabs(cholmanager->FMat.data[(k - 1) * LDimSizeP1]);
              if (s > smax) {
                nVars = k - 1;
                smax = s;
              }
            }
          }
          cholmanager->regTol_ = fmax(
              fabs(cholmanager->FMat.data[nVars + cholmanager->ldm * nVars]) *
                  2.2204460492503131E-16,
              0.0);
          if (mNull_tmp > 128) {
            bool exitg1;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < mNull_tmp)) {
              nVars = LDimSizeP1 * k + 1;
              ldw = mNull_tmp - k;
              if (k + 48 <= mNull_tmp) {
                partialColLDL3_(cholmanager, nVars, ldw);
                k += 48;
              } else {
                fullColLDL2_(cholmanager, nVars, ldw);
                exitg1 = true;
              }
            }
          } else {
            fullColLDL2_(cholmanager, 1, mNull_tmp);
          }
          if (cholmanager->ConvexCheck) {
            idx = 0;
            int exitg2;
            do {
              exitg2 = 0;
              if (idx <= mNull_tmp - 1) {
                if (cholmanager->FMat.data[idx + cholmanager->ldm * idx] <=
                    0.0) {
                  cholmanager->info = -idx - 1;
                  exitg2 = 1;
                } else {
                  idx++;
                }
              } else {
                cholmanager->ConvexCheck = false;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }
        }
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          ldw = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            memset(&memspace->workspace_double.data[0], 0,
                   (unsigned int)mNull_tmp * sizeof(double));
            nVars = 0;
            i = nullStartIdx_tmp + qrmanager->ldq * (mNull_tmp - 1);
            for (idx = nullStartIdx_tmp; ldw < 0 ? idx >= i : idx <= i;
                 idx += ldw) {
              smax = 0.0;
              idx_col = idx + nVar_tmp;
              for (k = idx; k <= idx_col; k++) {
                smax +=
                    qrmanager->Q.data[k - 1] * objective->grad.data[k - idx];
              }
              memspace->workspace_double.data[nVars] -= smax;
              nVars++;
            }
          }
          if (alwaysPositiveDef) {
            ldw = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (idx_col = 0; idx_col < ldw; idx_col++) {
                nVars = idx_col * cholmanager->ldm;
                smax = memspace->workspace_double.data[idx_col];
                for (idx = 0; idx < idx_col; idx++) {
                  smax -= cholmanager->FMat.data[nVars + idx] *
                          memspace->workspace_double.data[idx];
                }
                memspace->workspace_double.data[idx_col] =
                    smax / cholmanager->FMat.data[nVars + idx_col];
              }
            }
            ldw = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (idx_col = ldw; idx_col >= 1; idx_col--) {
                nVars = (idx_col + (idx_col - 1) * cholmanager->ldm) - 1;
                memspace->workspace_double.data[idx_col - 1] /=
                    cholmanager->FMat.data[nVars];
                for (idx = 0; idx <= idx_col - 2; idx++) {
                  LDimSizeP1 = (idx_col - idx) - 2;
                  memspace->workspace_double.data[LDimSizeP1] -=
                      memspace->workspace_double.data[idx_col - 1] *
                      cholmanager->FMat.data[(nVars - idx) - 1];
                }
              }
            }
          } else {
            ldw = cholmanager->ndims - 2;
            if (cholmanager->ndims != 0) {
              for (idx_col = 0; idx_col <= ldw + 1; idx_col++) {
                nVars = idx_col + idx_col * cholmanager->ldm;
                i = ldw - idx_col;
                for (idx = 0; idx <= i; idx++) {
                  LDimSizeP1 = (idx_col + idx) + 1;
                  memspace->workspace_double.data[LDimSizeP1] -=
                      memspace->workspace_double.data[idx_col] *
                      cholmanager->FMat.data[(nVars + idx) + 1];
                }
              }
            }
            i = cholmanager->ndims;
            for (idx = 0; idx < i; idx++) {
              memspace->workspace_double.data[idx] /=
                  cholmanager->FMat.data[idx + cholmanager->ldm * idx];
            }
            ldw = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (idx_col = ldw; idx_col >= 1; idx_col--) {
                nVars = (idx_col - 1) * cholmanager->ldm;
                smax = memspace->workspace_double.data[idx_col - 1];
                i = idx_col + 1;
                for (idx = ldw; idx >= i; idx--) {
                  smax -= cholmanager->FMat.data[(nVars + idx) - 1] *
                          memspace->workspace_double.data[idx - 1];
                }
                memspace->workspace_double.data[idx_col - 1] = smax;
              }
            }
          }
          ldw = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            memset(&solution->searchDir.data[0], 0,
                   (unsigned int)(nVar_tmp + 1) * sizeof(double));
            LDimSizeP1 = 0;
            i = nullStartIdx_tmp + qrmanager->ldq * (mNull_tmp - 1);
            for (idx = nullStartIdx_tmp; ldw < 0 ? idx >= i : idx <= i;
                 idx += ldw) {
              idx_col = idx + nVar_tmp;
              for (k = idx; k <= idx_col; k++) {
                nVars = k - idx;
                solution->searchDir.data[nVars] +=
                    qrmanager->Q.data[k - 1] *
                    memspace->workspace_double.data[LDimSizeP1];
              }
              LDimSizeP1++;
            }
          }
        }
      }
    }
  }
}

/*
 * File trailer for compute_deltax.c
 *
 * [EOF]
 */
