/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: factoryConstruct.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "factoryConstruct.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int nVarMax
 *                int mConstrMax
 *                int mIneq
 *                int mNonlinIneq
 *                c_struct_T *obj
 * Return Type  : void
 */
void factoryConstruct(int nVarMax, int mConstrMax, int mIneq, int mNonlinIneq,
                      c_struct_T *obj)
{
  obj->nVarMax = nVarMax;
  obj->mNonlinIneq = mNonlinIneq;
  obj->mNonlinEq = 160;
  obj->mIneq = mIneq;
  obj->mEq = 160;
  obj->iNonIneq0 = (mIneq - mNonlinIneq) + 1;
  obj->iNonEq0 = 1;
  obj->sqpFval = 0.0;
  obj->sqpFval_old = 0.0;
  obj->cIneq.size[0] = mIneq;
  obj->cIneq_old.size[0] = mIneq;
  obj->grad.size[0] = nVarMax;
  obj->grad_old.size[0] = nVarMax;
  obj->FunctionEvaluations = 0;
  obj->sqpIterations = 0;
  obj->sqpExitFlag = 0;
  obj->lambdasqp.size[0] = mConstrMax;
  if (mConstrMax - 1 >= 0) {
    memset(&obj->lambdasqp.data[0], 0,
           (unsigned int)mConstrMax * sizeof(double));
  }
  obj->lambdaStopTest.size[0] = mConstrMax;
  obj->lambdaStopTestPrev.size[0] = mConstrMax;
  obj->steplength = 1.0;
  obj->delta_x.size[0] = nVarMax;
  if (nVarMax - 1 >= 0) {
    memset(&obj->delta_x.data[0], 0, (unsigned int)nVarMax * sizeof(double));
  }
  obj->socDirection.size[0] = nVarMax;
  obj->workingset_old.size[0] = mConstrMax;
  if (mNonlinIneq > 0) {
    obj->JacCineqTrans_old.size[0] = nVarMax;
    obj->JacCineqTrans_old.size[1] = mNonlinIneq;
  } else {
    obj->JacCineqTrans_old.size[0] = 0;
    obj->JacCineqTrans_old.size[1] = 0;
  }
  obj->JacCeqTrans_old.size[0] = nVarMax;
  obj->JacCeqTrans_old.size[1] = 160;
  obj->gradLag.size[0] = nVarMax;
  obj->delta_gradLag.size[0] = nVarMax;
  obj->xstar.size[0] = nVarMax;
  obj->fstar = 0.0;
  obj->firstorderopt = 0.0;
  obj->lambda.size[0] = mConstrMax;
  if (mConstrMax - 1 >= 0) {
    memset(&obj->lambda.data[0], 0, (unsigned int)mConstrMax * sizeof(double));
  }
  obj->state = 0;
  obj->maxConstr = 0.0;
  obj->iterations = 0;
  obj->searchDir.size[0] = nVarMax;
}

/*
 * File trailer for factoryConstruct.c
 *
 * [EOF]
 */
