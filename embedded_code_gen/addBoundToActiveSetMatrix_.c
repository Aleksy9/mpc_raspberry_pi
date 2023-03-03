/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: addBoundToActiveSetMatrix_.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "addBoundToActiveSetMatrix_.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : f_struct_T *obj
 *                int TYPE
 *                int idx_local
 * Return Type  : void
 */
void addBoundToActiveSetMatrix_(f_struct_T *obj, int TYPE, int idx_local)
{
  int colOffset;
  int i;
  int idx_bnd_local;
  obj->nWConstr[TYPE - 1]++;
  obj->isActiveConstr.data[(obj->isActiveIdx[TYPE - 1] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid.data[obj->nActiveConstr - 1] = TYPE;
  obj->Wlocalidx.data[obj->nActiveConstr - 1] = idx_local;
  colOffset = obj->ldA * (obj->nActiveConstr - 1) - 1;
  if (TYPE == 5) {
    idx_bnd_local = obj->indexUB.data[idx_local - 1];
    obj->bwset.data[obj->nActiveConstr - 1] = obj->ub.data[idx_bnd_local - 1];
  } else {
    idx_bnd_local = obj->indexLB.data[idx_local - 1];
    obj->bwset.data[obj->nActiveConstr - 1] = obj->lb.data[idx_bnd_local - 1];
  }
  i = (unsigned short)(idx_bnd_local - 1);
  if (i - 1 >= 0) {
    memset(&obj->ATwset.data[colOffset + 1], 0,
           (unsigned int)((i + colOffset) - colOffset) * sizeof(double));
  }
  obj->ATwset.data[idx_bnd_local + colOffset] = 2.0 * (double)(TYPE == 5) - 1.0;
  i = idx_bnd_local + 1;
  idx_bnd_local = obj->nVar;
  if (i <= idx_bnd_local) {
    memset(&obj->ATwset.data[i + colOffset], 0,
           (unsigned int)((((idx_bnd_local + colOffset) - i) - colOffset) + 1) *
               sizeof(double));
  }
  switch (obj->probType) {
  case 3:
  case 2:
    break;
  default:
    obj->ATwset.data[obj->nVar + colOffset] = -1.0;
    break;
  }
}

/*
 * File trailer for addBoundToActiveSetMatrix_.c
 *
 * [EOF]
 */
