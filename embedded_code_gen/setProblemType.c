/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: setProblemType.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "setProblemType.h"
#include "modifyOverheadPhaseOne_.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : f_struct_T *obj
 *                int PROBLEM_TYPE
 * Return Type  : void
 */
void setProblemType(f_struct_T *obj, int PROBLEM_TYPE)
{
  int colOffsetAeq;
  int i;
  int idx_col;
  switch (PROBLEM_TYPE) {
  case 3:
    obj->nVar = 181;
    obj->mConstr = obj->mConstrOrig;
    if (obj->nWConstr[4] > 0) {
      i = (unsigned short)obj->sizesNormal[4];
      for (colOffsetAeq = 0; colOffsetAeq < i; colOffsetAeq++) {
        obj->isActiveConstr
            .data[(obj->isActiveIdxNormal[4] + colOffsetAeq) - 1] =
            obj->isActiveConstr.data[(obj->isActiveIdx[4] + colOffsetAeq) - 1];
      }
    }
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesNormal[i];
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxNormal[i];
    }
    break;
  case 1:
    obj->nVar = 182;
    obj->mConstr = obj->mConstrOrig + 1;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesPhaseOne[i];
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxPhaseOne[i];
    }
    modifyOverheadPhaseOne_(obj);
    break;
  case 2: {
    obj->nVar = obj->nVarMax - 1;
    obj->mConstr = obj->mConstrMax - 1;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesRegularized[i];
    }
    if (obj->probType != 4) {
      int colOffsetATw;
      int colOffsetAineq;
      int i1;
      int i2;
      int mIneq;
      int offsetEq1;
      int offsetEq2;
      mIneq = obj->sizes[2] + 180;
      offsetEq1 = obj->sizes[2] + 181;
      offsetEq2 = obj->sizes[2] + 341;
      i = (unsigned short)obj->sizes[0];
      for (idx_col = 0; idx_col < i; idx_col++) {
        colOffsetATw = obj->ldA * idx_col;
        i1 = obj->nVar;
        memset(&obj->ATwset.data[colOffsetATw + 181], 0,
               (unsigned int)(((i1 + colOffsetATw) - colOffsetATw) - 181) *
                   sizeof(double));
      }
      i = (unsigned short)obj->sizes[2];
      for (idx_col = 0; idx_col < i; idx_col++) {
        colOffsetAineq = obj->ldA * idx_col - 1;
        i1 = idx_col + 181;
        if (i1 >= 182) {
          memset(
              &obj->Aineq.data[colOffsetAineq + 182], 0,
              (unsigned int)(((i1 + colOffsetAineq) - colOffsetAineq) - 181) *
                  sizeof(double));
        }
        obj->Aineq.data[(idx_col + colOffsetAineq) + 182] = -1.0;
        i1 = idx_col + 183;
        i2 = obj->nVar;
        if (i1 <= i2) {
          memset(
              &obj->Aineq.data[i1 + colOffsetAineq], 0,
              (unsigned int)((((i2 + colOffsetAineq) - i1) - colOffsetAineq) +
                             1) *
                  sizeof(double));
        }
      }
      i = mIneq + 2;
      i1 = mIneq + 162;
      for (idx_col = 0; idx_col < 160; idx_col++) {
        int i3;
        int i4;
        colOffsetAeq = obj->ldA * idx_col - 1;
        colOffsetATw = colOffsetAeq + obj->ldA * (obj->isActiveIdx[1] - 1);
        if (offsetEq1 >= 182) {
          memset(&obj->Aeq.data[colOffsetAeq + 182], 0,
                 (unsigned int)(((offsetEq1 + colOffsetAeq) - colOffsetAeq) -
                                181) *
                     sizeof(double));
          memset(&obj->ATwset.data[colOffsetATw + 182], 0,
                 (unsigned int)(((offsetEq1 + colOffsetATw) - colOffsetATw) -
                                181) *
                     sizeof(double));
        }
        i2 = mIneq + idx_col;
        colOffsetAineq = i2 + 1;
        if (i <= colOffsetAineq) {
          memset(&obj->Aeq.data[i + colOffsetAeq], 0,
                 (unsigned int)((((colOffsetAineq + colOffsetAeq) - i) -
                                 colOffsetAeq) +
                                1) *
                     sizeof(double));
          memset(&obj->ATwset.data[i + colOffsetATw], 0,
                 (unsigned int)((((colOffsetAineq + colOffsetATw) - i) -
                                 colOffsetATw) +
                                1) *
                     sizeof(double));
        }
        colOffsetAineq = i2 + colOffsetAeq;
        obj->Aeq.data[colOffsetAineq + 2] = -1.0;
        i3 = i2 + colOffsetATw;
        obj->ATwset.data[i3 + 2] = -1.0;
        i4 = i2 + 3;
        if (i4 <= offsetEq2) {
          memset(&obj->Aeq.data[i4 + colOffsetAeq], 0,
                 (unsigned int)((((offsetEq2 + colOffsetAeq) - i4) -
                                 colOffsetAeq) +
                                1) *
                     sizeof(double));
          memset(&obj->ATwset.data[i4 + colOffsetATw], 0,
                 (unsigned int)((((offsetEq2 + colOffsetATw) - i4) -
                                 colOffsetATw) +
                                1) *
                     sizeof(double));
        }
        i4 = i2 + 161;
        if (i1 <= i4) {
          memset(
              &obj->Aeq.data[i1 + colOffsetAeq], 0,
              (unsigned int)((((i4 + colOffsetAeq) - i1) - colOffsetAeq) + 1) *
                  sizeof(double));
          memset(
              &obj->ATwset.data[i1 + colOffsetATw], 0,
              (unsigned int)((((i4 + colOffsetATw) - i1) - colOffsetATw) + 1) *
                  sizeof(double));
        }
        obj->Aeq.data[colOffsetAineq + 162] = 1.0;
        obj->ATwset.data[i3 + 162] = 1.0;
        i2 += 163;
        colOffsetAineq = obj->nVar;
        if (i2 <= colOffsetAineq) {
          memset(&obj->Aeq.data[i2 + colOffsetAeq], 0,
                 (unsigned int)((((colOffsetAineq + colOffsetAeq) - i2) -
                                 colOffsetAeq) +
                                1) *
                     sizeof(double));
          memset(&obj->ATwset.data[i2 + colOffsetATw], 0,
                 (unsigned int)((((colOffsetAineq + colOffsetATw) - i2) -
                                 colOffsetATw) +
                                1) *
                     sizeof(double));
        }
      }
      colOffsetAineq = 181;
      i = obj->sizesNormal[3] + 1;
      i1 = obj->sizesRegularized[3];
      for (colOffsetAeq = i; colOffsetAeq <= i1; colOffsetAeq++) {
        colOffsetAineq++;
        obj->indexLB.data[colOffsetAeq - 1] = colOffsetAineq;
      }
      if (obj->nWConstr[4] > 0) {
        i = (unsigned short)obj->sizesRegularized[4];
        for (colOffsetAeq = 0; colOffsetAeq < i; colOffsetAeq++) {
          obj->isActiveConstr
              .data[obj->isActiveIdxRegularized[4] + colOffsetAeq] =
              obj->isActiveConstr
                  .data[(obj->isActiveIdx[4] + colOffsetAeq) - 1];
        }
      }
      i = obj->isActiveIdx[4];
      i1 = obj->isActiveIdxRegularized[4] - 1;
      if (i <= i1) {
        memset(&obj->isActiveConstr.data[i + -1], 0,
               (unsigned int)((i1 - i) + 1) * sizeof(bool));
      }
      i = obj->sizes[2] + 501;
      memset(&obj->lb.data[181], 0, (unsigned int)(i - 181) * sizeof(double));
      colOffsetAineq = obj->isActiveIdx[2];
      i = obj->nActiveConstr;
      for (idx_col = colOffsetAineq; idx_col <= i; idx_col++) {
        colOffsetATw = obj->ldA * (idx_col - 1) - 1;
        if (obj->Wid.data[idx_col - 1] == 3) {
          i1 = obj->Wlocalidx.data[idx_col - 1] + 180;
          if (i1 >= 182) {
            memset(&obj->ATwset.data[colOffsetATw + 182], 0,
                   (unsigned int)(((i1 + colOffsetATw) - colOffsetATw) - 181) *
                       sizeof(double));
          }
          obj->ATwset
              .data[(obj->Wlocalidx.data[idx_col - 1] + colOffsetATw) + 181] =
              -1.0;
          i1 = obj->Wlocalidx.data[idx_col - 1] + 182;
          i2 = obj->nVar;
          if (i1 <= i2) {
            memset(&obj->ATwset.data[i1 + colOffsetATw], 0,
                   (unsigned int)((((i2 + colOffsetATw) - i1) - colOffsetATw) +
                                  1) *
                       sizeof(double));
          }
        } else {
          i1 = obj->nVar;
          memset(&obj->ATwset.data[colOffsetATw + 182], 0,
                 (unsigned int)(((i1 + colOffsetATw) - colOffsetATw) - 181) *
                     sizeof(double));
        }
      }
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxRegularized[i];
    }
  } break;
  default:
    obj->nVar = obj->nVarMax;
    obj->mConstr = obj->mConstrMax;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesRegPhaseOne[i];
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxRegPhaseOne[i];
    }
    modifyOverheadPhaseOne_(obj);
    break;
  }
  obj->probType = PROBLEM_TYPE;
}

/*
 * File trailer for setProblemType.c
 *
 * [EOF]
 */
