/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: linesearch.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "linesearch.h"
#include "computeLinearResiduals.h"
#include "evalObjAndConstr.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : bool *evalWellDefined
 *                const double bineq_data[]
 *                int WorkingSet_nVar
 *                int WorkingSet_ldA
 *                const double WorkingSet_Aineq_data[]
 *                c_struct_T *TrialState
 *                double MeritFunction_penaltyParam
 *                double MeritFunction_phi
 *                double MeritFunction_phiPrimePlus
 *                double MeritFunction_phiFullStep
 *                int c_FcnEvaluator_next_next_next_n
 *                const i_struct_T *d_FcnEvaluator_next_next_next_n
 *                const k_struct_T *e_FcnEvaluator_next_next_next_n
 *                bool socTaken
 *                double *alpha
 *                int *exitflag
 * Return Type  : void
 */
void linesearch(bool *evalWellDefined, const double bineq_data[],
                int WorkingSet_nVar, int WorkingSet_ldA,
                const double WorkingSet_Aineq_data[], c_struct_T *TrialState,
                double MeritFunction_penaltyParam, double MeritFunction_phi,
                double MeritFunction_phiPrimePlus,
                double MeritFunction_phiFullStep,
                int c_FcnEvaluator_next_next_next_n,
                const i_struct_T *d_FcnEvaluator_next_next_next_n,
                const k_struct_T *e_FcnEvaluator_next_next_next_n,
                bool socTaken, double *alpha, int *exitflag)
{
  double y_data[1803];
  double phi_alpha;
  int i;
  int ixlast;
  int mLinIneq;
  int y_size;
  mLinIneq = TrialState->mIneq - TrialState->mNonlinIneq;
  *alpha = 1.0;
  *exitflag = 1;
  phi_alpha = MeritFunction_phiFullStep;
  y_size = TrialState->searchDir.size[0];
  ixlast = TrialState->searchDir.size[0];
  if (ixlast - 1 >= 0) {
    memcpy(&y_data[0], &TrialState->searchDir.data[0],
           (unsigned int)ixlast * sizeof(double));
  }
  i = (unsigned short)WorkingSet_nVar;
  if (i - 1 >= 0) {
    memcpy(&y_data[0], &TrialState->delta_x.data[0],
           (unsigned int)i * sizeof(double));
  }
  TrialState->searchDir.size[0] = y_size;
  if (y_size - 1 >= 0) {
    memcpy(&TrialState->searchDir.data[0], &y_data[0],
           (unsigned int)y_size * sizeof(double));
  }
  int exitg1;
  do {
    exitg1 = 0;
    if (TrialState->FunctionEvaluations < 18100) {
      if ((*evalWellDefined) &&
          (phi_alpha <=
           MeritFunction_phi + *alpha * 0.0001 * MeritFunction_phiPrimePlus)) {
        exitg1 = 1;
      } else {
        bool exitg2;
        bool tooSmallX;
        *alpha *= 0.7;
        for (ixlast = 0; ixlast < i; ixlast++) {
          TrialState->delta_x.data[ixlast] =
              *alpha * TrialState->xstar.data[ixlast];
        }
        if (socTaken) {
          phi_alpha = *alpha * *alpha;
          if ((WorkingSet_nVar >= 1) && (!(phi_alpha == 0.0))) {
            ixlast = WorkingSet_nVar - 1;
            for (y_size = 0; y_size <= ixlast; y_size++) {
              TrialState->delta_x.data[y_size] +=
                  phi_alpha * TrialState->socDirection.data[y_size];
            }
          }
        }
        tooSmallX = true;
        ixlast = 0;
        exitg2 = false;
        while ((!exitg2) && (ixlast <= (unsigned short)WorkingSet_nVar - 1)) {
          if (1.0E-6 * fmax(1.0, fabs(TrialState->xstarsqp[ixlast])) <=
              fabs(TrialState->delta_x.data[ixlast])) {
            tooSmallX = false;
            exitg2 = true;
          } else {
            ixlast++;
          }
        }
        if (tooSmallX) {
          *exitflag = -2;
          exitg1 = 1;
        } else {
          for (ixlast = 0; ixlast < i; ixlast++) {
            TrialState->xstarsqp[ixlast] = TrialState->xstarsqp_old[ixlast] +
                                           TrialState->delta_x.data[ixlast];
          }
          evalObjAndConstr(
              c_FcnEvaluator_next_next_next_n, d_FcnEvaluator_next_next_next_n,
              e_FcnEvaluator_next_next_next_n, TrialState->xstarsqp,
              TrialState->cIneq.data, TrialState->iNonIneq0, TrialState->cEq,
              &TrialState->sqpFval, &ixlast);
          computeLinearResiduals(
              TrialState->xstarsqp, WorkingSet_nVar, TrialState->cIneq.data,
              &TrialState->cIneq.size[0], mLinIneq, WorkingSet_Aineq_data,
              bineq_data, WorkingSet_ldA);
          TrialState->FunctionEvaluations++;
          *evalWellDefined = (ixlast == 1);
          if (*evalWellDefined) {
            double constrViolationIneq;
            phi_alpha = 0.0;
            for (y_size = 0; y_size < 160; y_size++) {
              phi_alpha += fabs(TrialState->cEq[y_size]);
            }
            constrViolationIneq = 0.0;
            y_size = (unsigned short)TrialState->mIneq;
            for (ixlast = 0; ixlast < y_size; ixlast++) {
              double d;
              d = TrialState->cIneq.data[ixlast];
              if (d > 0.0) {
                constrViolationIneq += d;
              }
            }
            phi_alpha =
                TrialState->sqpFval +
                MeritFunction_penaltyParam * (phi_alpha + constrViolationIneq);
          } else {
            phi_alpha = rtInf;
          }
        }
      }
    } else {
      *exitflag = 0;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/*
 * File trailer for linesearch.c
 *
 * [EOF]
 */
