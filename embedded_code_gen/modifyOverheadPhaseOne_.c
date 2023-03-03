/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: modifyOverheadPhaseOne_.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "modifyOverheadPhaseOne_.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : f_struct_T *obj
 * Return Type  : void
 */
void modifyOverheadPhaseOne_(f_struct_T *obj)
{
  int idx;
  int idxEq;
  int idxStartIneq;
  idxEq = (unsigned short)obj->sizes[0];
  for (idx = 0; idx < idxEq; idx++) {
    obj->ATwset.data[(obj->nVar + obj->ldA * idx) - 1] = 0.0;
  }
  for (idx = 0; idx < 160; idx++) {
    idxEq = (obj->nVar + obj->ldA * idx) - 1;
    obj->Aeq.data[idxEq] = 0.0;
    obj->ATwset.data[idxEq + obj->ldA * (obj->isActiveIdx[1] - 1)] = 0.0;
  }
  idxEq = (unsigned short)obj->sizes[2];
  for (idx = 0; idx < idxEq; idx++) {
    obj->Aineq.data[(obj->nVar + obj->ldA * idx) - 1] = -1.0;
  }
  obj->indexLB.data[obj->sizes[3] - 1] = obj->nVar;
  obj->lb.data[obj->nVar - 1] = 1.0E-5;
  idxStartIneq = obj->isActiveIdx[2];
  idxEq = obj->nActiveConstr;
  for (idx = idxStartIneq; idx <= idxEq; idx++) {
    obj->ATwset.data[(obj->nVar + obj->ldA * (idx - 1)) - 1] = -1.0;
  }
  if (obj->nWConstr[4] > 0) {
    idxEq = (unsigned short)(obj->sizesNormal[4] + 1);
    for (idx = 0; idx < idxEq; idx++) {
      obj->isActiveConstr.data[(obj->isActiveIdx[4] + idx) - 1] = false;
    }
  }
  obj->isActiveConstr.data[obj->isActiveIdx[4] - 2] = false;
}

/*
 * File trailer for modifyOverheadPhaseOne_.c
 *
 * [EOF]
 */
