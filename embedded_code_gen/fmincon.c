/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fmincon.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "fmincon.h"
#include "driver.h"
#include "evalObjAndConstrAndDerivatives.h"
#include "factoryConstruct.h"
#include "factoryConstruct1.h"
#include "loadProblem.h"
#include "nlmpcmoveCodeGeneration.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const i_struct_T *fun_workspace_runtimedata
 *                const j_struct_T *fun_workspace_userdata
 *                const double x0[181]
 *                const double Aineq_data[]
 *                const double bineq_data[]
 *                int bineq_size
 *                const double lb[181]
 *                const double ub[181]
 *                const i_struct_T *nonlcon_workspace_runtimedata
 *                const j_struct_T *nonlcon_workspace_userdata
 *                double x[181]
 *                double *fval
 *                double *exitflag
 *                l_struct_T *output
 * Return Type  : void
 */
void fmincon(const i_struct_T *fun_workspace_runtimedata,
             const j_struct_T *fun_workspace_userdata, const double x0[181],
             const double Aineq_data[], const double bineq_data[],
             int bineq_size, const double lb[181], const double ub[181],
             const i_struct_T *nonlcon_workspace_runtimedata,
             const j_struct_T *nonlcon_workspace_userdata, double x[181],
             double *fval, double *exitflag, l_struct_T *output)
{
  static c_struct_T TrialState;
  static e_struct_T memspace;
  static f_struct_T WorkingSet;
  static g_struct_T obj;
  static h_struct_T b_obj;
  static i_coder_internal_stickyStruct FcnEvaluator;
  static double varargout_3_data[57920];
  static double unusedExpr[32761];
  static double varargout_4[28960];
  d_struct_T QPObjective;
  struct_T MeritFunction;
  double y_data[1803];
  double varargout_1_data[320];
  double varargout_2[160];
  double c;
  double scale;
  int varargout_1_size[2];
  int varargout_3_size[2];
  int i;
  int i1;
  int iATw0;
  int iEq0;
  int ia;
  int mConstrMax;
  int mFixed;
  int mIneq;
  int mLB;
  int mNonlinIneq;
  int mUB;
  int maxDims;
  c_nlmpcmoveCodeGeneration_anonF(nonlcon_workspace_runtimedata->x,
                                  nonlcon_workspace_runtimedata->OutputMin,
                                  nonlcon_workspace_runtimedata->OutputMax,
                                  nonlcon_workspace_runtimedata->Parameters[0],
                                  x0, varargout_1_data, varargout_1_size,
                                  varargout_2, varargout_3_data,
                                  varargout_3_size, varargout_4);
  mNonlinIneq = varargout_1_size[0] * varargout_1_size[1];
  mIneq = (bineq_size + mNonlinIneq) + 502;
  mConstrMax = (mIneq + mIneq) - 161;
  if (mIneq >= mConstrMax) {
    maxDims = mIneq;
  } else {
    maxDims = mConstrMax;
  }
  factoryConstruct(mIneq, mConstrMax, mIneq - 502, mNonlinIneq, &TrialState);
  FcnEvaluator.next.next.next.next.next.value = mNonlinIneq;
  FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace
      .runtimedata = *fun_workspace_runtimedata;
  FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace
      .userdata = *fun_workspace_userdata;
  FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata =
      *nonlcon_workspace_runtimedata;
  FcnEvaluator.next.next.next.next.next.next.next.value.workspace.userdata =
      *nonlcon_workspace_userdata;
  QPObjective.grad.size[0] = mIneq;
  QPObjective.Hx.size[0] = mIneq - 1;
  QPObjective.maxVar = mIneq;
  QPObjective.beta = 0.0;
  QPObjective.rho = 0.0;
  QPObjective.prev_objtype = 3;
  QPObjective.prev_nvar = 0;
  QPObjective.prev_hasLinear = false;
  QPObjective.gammaScalar = 0.0;
  QPObjective.hasLinear = true;
  QPObjective.nvar = 181;
  QPObjective.objtype = 3;
  memspace.workspace_double.size[0] = maxDims;
  memspace.workspace_double.size[1] = mIneq;
  memspace.workspace_int.size[0] = maxDims;
  memspace.workspace_sort.size[0] = maxDims;
  b_factoryConstruct(mIneq - 502, mIneq, mConstrMax, &WorkingSet);
  mLB = -1;
  mUB = -1;
  mFixed = 0;
  for (iEq0 = 0; iEq0 < 181; iEq0++) {
    bool guard1 = false;
    TrialState.xstarsqp[iEq0] = x0[iEq0];
    c = lb[iEq0];
    guard1 = false;
    if ((!rtIsInf(c)) && (!rtIsNaN(c))) {
      if (fabs(c - ub[iEq0]) < 1.0E-6) {
        mFixed++;
        WorkingSet.indexFixed.data[mFixed - 1] = iEq0 + 1;
      } else {
        mLB++;
        WorkingSet.indexLB.data[mLB] = iEq0 + 1;
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      c = ub[iEq0];
      if ((!rtIsInf(c)) && (!rtIsNaN(c))) {
        mUB++;
        WorkingSet.indexUB.data[mUB] = iEq0 + 1;
      }
    }
  }
  loadProblem(&WorkingSet, mIneq - 502, bineq_size, Aineq_data, mLB + 1,
              mUB + 1, mFixed, mConstrMax);
  for (iATw0 = 0; iATw0 <= mLB; iATw0++) {
    i = WorkingSet.indexLB.data[iATw0];
    TrialState.xstarsqp[i - 1] = fmax(TrialState.xstarsqp[i - 1], lb[i - 1]);
  }
  for (iATw0 = 0; iATw0 <= mUB; iATw0++) {
    i = WorkingSet.indexUB.data[iATw0];
    TrialState.xstarsqp[i - 1] = fmin(TrialState.xstarsqp[i - 1], ub[i - 1]);
  }
  for (iATw0 = 0; iATw0 < mFixed; iATw0++) {
    i = WorkingSet.indexFixed.data[iATw0];
    TrialState.xstarsqp[i - 1] = ub[i - 1];
  }
  evalObjAndConstrAndDerivatives(
      mNonlinIneq, nonlcon_workspace_runtimedata,
      &FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace,
      TrialState.xstarsqp, TrialState.grad.data, TrialState.cIneq.data,
      TrialState.iNonIneq0, TrialState.cEq, WorkingSet.Aineq.data,
      TrialState.iNonIneq0, WorkingSet.ldA, WorkingSet.Aeq.data, WorkingSet.ldA,
      &TrialState.sqpFval, &mConstrMax);
  TrialState.FunctionEvaluations = 1;
  iATw0 = WorkingSet.ldA;
  if (bineq_size > 0) {
    mConstrMax = TrialState.cIneq.size[0];
    iEq0 = TrialState.cIneq.size[0];
    if (iEq0 - 1 >= 0) {
      memcpy(&y_data[0], &TrialState.cIneq.data[0],
             (unsigned int)iEq0 * sizeof(double));
    }
    memcpy(&y_data[0], &bineq_data[0],
           (unsigned int)bineq_size * sizeof(double));
    if (mConstrMax - 1 >= 0) {
      memcpy(&TrialState.cIneq.data[0], &y_data[0],
             (unsigned int)mConstrMax * sizeof(double));
    }
    for (mConstrMax = 0; mConstrMax < bineq_size; mConstrMax++) {
      TrialState.cIneq.data[mConstrMax] = -TrialState.cIneq.data[mConstrMax];
    }
    mConstrMax = 0;
    i = WorkingSet.ldA * (bineq_size - 1) + 1;
    for (iEq0 = 1; iATw0 < 0 ? iEq0 >= i : iEq0 <= i; iEq0 += iATw0) {
      c = 0.0;
      i1 = iEq0 + 180;
      for (ia = iEq0; ia <= i1; ia++) {
        c += WorkingSet.Aineq.data[ia - 1] * TrialState.xstarsqp[ia - iEq0];
      }
      TrialState.cIneq.data[mConstrMax] += c;
      mConstrMax++;
    }
  }
  mConstrMax = WorkingSet.ldA * mFixed;
  iEq0 = 0;
  for (iATw0 = 0; iATw0 < 160; iATw0++) {
    c = -TrialState.cEq[iATw0];
    WorkingSet.beq[iATw0] = c;
    WorkingSet.bwset.data[mFixed + iATw0] = c;
    memcpy(&WorkingSet.ATwset.data[mConstrMax], &WorkingSet.Aeq.data[iEq0],
           181U * sizeof(double));
    mConstrMax += WorkingSet.ldA;
    iEq0 += WorkingSet.ldA;
  }
  for (iATw0 = 0; iATw0 <= mIneq - 503; iATw0++) {
    WorkingSet.bineq.data[iATw0] = -TrialState.cIneq.data[iATw0];
  }
  for (iATw0 = 0; iATw0 <= mLB; iATw0++) {
    WorkingSet.lb.data[WorkingSet.indexLB.data[iATw0] - 1] =
        -lb[WorkingSet.indexLB.data[iATw0] - 1] +
        x0[WorkingSet.indexLB.data[iATw0] - 1];
  }
  for (iATw0 = 0; iATw0 <= mUB; iATw0++) {
    WorkingSet.ub.data[WorkingSet.indexUB.data[iATw0] - 1] =
        ub[WorkingSet.indexUB.data[iATw0] - 1] -
        x0[WorkingSet.indexUB.data[iATw0] - 1];
  }
  for (iATw0 = 0; iATw0 < mFixed; iATw0++) {
    c = ub[WorkingSet.indexFixed.data[iATw0] - 1] -
        x0[WorkingSet.indexFixed.data[iATw0] - 1];
    WorkingSet.ub.data[WorkingSet.indexFixed.data[iATw0] - 1] = c;
    WorkingSet.bwset.data[iATw0] = c;
  }
  setProblemType(&WorkingSet, 3);
  mConstrMax = WorkingSet.isActiveIdx[2];
  i = WorkingSet.mConstrMax;
  if (mConstrMax <= i) {
    memset(&WorkingSet.isActiveConstr.data[mConstrMax + -1], 0,
           (unsigned int)((i - mConstrMax) + 1) * sizeof(bool));
  }
  WorkingSet.nWConstr[0] = WorkingSet.sizes[0];
  WorkingSet.nWConstr[1] = 160;
  WorkingSet.nWConstr[2] = 0;
  WorkingSet.nWConstr[3] = 0;
  WorkingSet.nWConstr[4] = 0;
  WorkingSet.nActiveConstr = WorkingSet.nWConstr[0] + 160;
  i = (unsigned short)WorkingSet.sizes[0];
  for (mLB = 0; mLB < i; mLB++) {
    WorkingSet.Wid.data[mLB] = 1;
    WorkingSet.Wlocalidx.data[mLB] = mLB + 1;
    WorkingSet.isActiveConstr.data[mLB] = true;
    mConstrMax = WorkingSet.ldA * mLB;
    i1 = (unsigned char)(WorkingSet.indexFixed.data[mLB] - 1);
    if (i1 - 1 >= 0) {
      memset(&WorkingSet.ATwset.data[mConstrMax], 0,
             (unsigned int)i1 * sizeof(double));
    }
    WorkingSet.ATwset.data[(WorkingSet.indexFixed.data[mLB] + mConstrMax) - 1] =
        1.0;
    i1 = WorkingSet.indexFixed.data[mLB] + 1;
    iEq0 = WorkingSet.nVar;
    if (i1 <= iEq0) {
      memset(&WorkingSet.ATwset.data[(i1 + mConstrMax) + -1], 0,
             (unsigned int)((((iEq0 + mConstrMax) - i1) - mConstrMax) + 1) *
                 sizeof(double));
    }
    WorkingSet.bwset.data[mLB] =
        WorkingSet.ub.data[WorkingSet.indexFixed.data[mLB] - 1];
  }
  MeritFunction.initFval = TrialState.sqpFval;
  MeritFunction.penaltyParam = 1.0;
  MeritFunction.threshold = 0.0001;
  MeritFunction.nPenaltyDecreases = 0;
  MeritFunction.linearizedConstrViol = 0.0;
  scale = 0.0;
  i = WorkingSet.nVar - 1;
  for (mLB = 0; mLB < 160; mLB++) {
    mConstrMax = WorkingSet.sizes[0] + mLB;
    WorkingSet.Wid.data[mConstrMax] = 2;
    WorkingSet.Wlocalidx.data[mConstrMax] = mLB + 1;
    WorkingSet.isActiveConstr.data[mConstrMax] = true;
    iEq0 = WorkingSet.ldA * mLB;
    iATw0 = WorkingSet.ldA * mConstrMax;
    for (ia = 0; ia <= i; ia++) {
      WorkingSet.ATwset.data[iATw0 + ia] = WorkingSet.Aeq.data[iEq0 + ia];
    }
    WorkingSet.bwset.data[mConstrMax] = WorkingSet.beq[mLB];
    scale += fabs(TrialState.cEq[mLB]);
  }
  MeritFunction.initConstrViolationEq = scale;
  scale = 0.0;
  for (iATw0 = 0; iATw0 <= mIneq - 503; iATw0++) {
    c = TrialState.cIneq.data[iATw0];
    if (c > 0.0) {
      scale += c;
    }
  }
  MeritFunction.initConstrViolationIneq = scale;
  MeritFunction.phi = 0.0;
  MeritFunction.phiPrimePlus = 0.0;
  MeritFunction.phiFullStep = 0.0;
  MeritFunction.feasRelativeFactor = 0.0;
  MeritFunction.nlpPrimalFeasError = 0.0;
  MeritFunction.nlpDualFeasError = 0.0;
  MeritFunction.nlpComplError = 0.0;
  MeritFunction.firstOrderOpt = 0.0;
  MeritFunction.hasObjective = true;
  obj.ldq = maxDims;
  obj.QR.size[0] = maxDims;
  obj.QR.size[1] = maxDims;
  obj.Q.size[0] = maxDims;
  obj.Q.size[1] = maxDims;
  iEq0 = maxDims * maxDims;
  memset(&obj.Q.data[0], 0, (unsigned int)iEq0 * sizeof(double));
  obj.jpvt.size[0] = maxDims;
  memset(&obj.jpvt.data[0], 0, (unsigned int)maxDims * sizeof(int));
  obj.mrows = 0;
  obj.ncols = 0;
  obj.tau.size[0] = maxDims;
  obj.minRowCol = 0;
  obj.usedPivoting = false;
  b_obj.FMat.size[0] = maxDims;
  b_obj.FMat.size[1] = maxDims;
  b_obj.ldm = maxDims;
  b_obj.ndims = 0;
  b_obj.info = 0;
  b_obj.scaleFactor = 0.0;
  b_obj.ConvexCheck = true;
  b_obj.regTol_ = rtInf;
  b_obj.workspace_ = rtInf;
  b_obj.workspace2_ = rtInf;
  driver(bineq_data, lb, ub, &TrialState, &MeritFunction, &FcnEvaluator,
         &memspace, &WorkingSet, &obj, &b_obj, &QPObjective, bineq_size,
         mNonlinIneq, unusedExpr);
  *fval = TrialState.sqpFval;
  *exitflag = TrialState.sqpExitFlag;
  output->iterations = TrialState.sqpIterations;
  output->constrviolation = MeritFunction.nlpPrimalFeasError;
  for (iEq0 = 0; iEq0 < 181; iEq0++) {
    x[iEq0] = TrialState.xstarsqp[iEq0];
  }
}

/*
 * File trailer for fmincon.c
 *
 * [EOF]
 */
