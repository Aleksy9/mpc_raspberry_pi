/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: removeConstr.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "removeConstr.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : f_struct_T *obj
 *                int idx_global
 * Return Type  : void
 */
void removeConstr(f_struct_T *obj, int idx_global)
{
  int TYPE_tmp;
  int i;
  int idx;
  TYPE_tmp = obj->Wid.data[idx_global - 1] - 1;
  obj->isActiveConstr
      .data[(obj->isActiveIdx[TYPE_tmp] + obj->Wlocalidx.data[idx_global - 1]) -
            2] = false;
  obj->Wid.data[idx_global - 1] = obj->Wid.data[obj->nActiveConstr - 1];
  obj->Wlocalidx.data[idx_global - 1] =
      obj->Wlocalidx.data[obj->nActiveConstr - 1];
  i = (unsigned short)obj->nVar;
  for (idx = 0; idx < i; idx++) {
    obj->ATwset.data[idx + obj->ldA * (idx_global - 1)] =
        obj->ATwset.data[idx + obj->ldA * (obj->nActiveConstr - 1)];
  }
  obj->bwset.data[idx_global - 1] = obj->bwset.data[obj->nActiveConstr - 1];
  obj->nActiveConstr--;
  obj->nWConstr[TYPE_tmp]--;
}

/*
 * File trailer for removeConstr.c
 *
 * [EOF]
 */
