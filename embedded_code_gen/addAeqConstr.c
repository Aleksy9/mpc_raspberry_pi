/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: addAeqConstr.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "addAeqConstr.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : f_struct_T *obj
 *                int idx_local
 * Return Type  : void
 */
void addAeqConstr(f_struct_T *obj, int idx_local)
{
  int idx;
  int totalEq;
  totalEq = obj->nWConstr[0] + obj->nWConstr[1];
  if ((obj->nActiveConstr == totalEq) && (idx_local > obj->nWConstr[1])) {
    int i;
    int iAeq0;
    int iAw0;
    obj->nWConstr[1]++;
    obj->isActiveConstr.data[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->nActiveConstr++;
    obj->Wid.data[obj->nActiveConstr - 1] = 2;
    obj->Wlocalidx.data[obj->nActiveConstr - 1] = idx_local;
    iAeq0 = obj->ldA * (idx_local - 1);
    iAw0 = obj->ldA * (obj->nActiveConstr - 1);
    i = (unsigned short)obj->nVar;
    for (idx = 0; idx < i; idx++) {
      obj->ATwset.data[iAw0 + idx] = obj->Aeq.data[iAeq0 + idx];
    }
    obj->bwset.data[obj->nActiveConstr - 1] = obj->beq[idx_local - 1];
  } else {
    int i;
    int iAeq0;
    int iAw0;
    obj->nActiveConstr++;
    obj->Wid.data[obj->nActiveConstr - 1] = obj->Wid.data[totalEq];
    obj->Wlocalidx.data[obj->nActiveConstr - 1] = obj->Wlocalidx.data[totalEq];
    i = (unsigned short)obj->nVar;
    for (idx = 0; idx < i; idx++) {
      obj->ATwset.data[idx + obj->ldA * (obj->nActiveConstr - 1)] =
          obj->ATwset.data[idx + obj->ldA * totalEq];
    }
    obj->bwset.data[obj->nActiveConstr - 1] = obj->bwset.data[totalEq];
    obj->nWConstr[1]++;
    obj->isActiveConstr.data[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->Wid.data[totalEq] = 2;
    obj->Wlocalidx.data[totalEq] = idx_local;
    iAeq0 = obj->ldA * (idx_local - 1);
    iAw0 = obj->ldA * totalEq;
    i = (unsigned short)obj->nVar;
    for (idx = 0; idx < i; idx++) {
      obj->ATwset.data[iAw0 + idx] = obj->Aeq.data[iAeq0 + idx];
    }
    obj->bwset.data[totalEq] = obj->beq[idx_local - 1];
  }
}

/*
 * File trailer for addAeqConstr.c
 *
 * [EOF]
 */
