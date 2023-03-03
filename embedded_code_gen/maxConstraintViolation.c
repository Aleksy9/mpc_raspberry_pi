/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: maxConstraintViolation.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : f_struct_T *obj
 *                const double x_data[]
 * Return Type  : double
 */
double maxConstraintViolation(f_struct_T *obj, const double x_data[])
{
  double v;
  int i;
  int idx;
  int idxLB;
  if (obj->probType == 2) {
    double d;
    v = 0.0;
    if (obj->Aineq.size[0] != 0) {
      i = (unsigned short)obj->sizes[2];
      if (i - 1 >= 0) {
        memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
               (unsigned int)i * sizeof(double));
      }
      e_xgemv(obj->sizes[2], obj->Aineq.data, obj->ldA, x_data,
              obj->maxConstrWorkspace.data);
      i = (unsigned short)obj->sizes[2];
      for (idx = 0; idx < i; idx++) {
        d = obj->maxConstrWorkspace.data[idx] - x_data[idx + 181];
        obj->maxConstrWorkspace.data[idx] = d;
        v = fmax(v, d);
      }
    }
    memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0],
           160U * sizeof(double));
    e_xgemv(160, obj->Aeq.data, obj->ldA, x_data, obj->maxConstrWorkspace.data);
    for (idx = 0; idx < 160; idx++) {
      i = obj->sizes[2] + idx;
      d = (obj->maxConstrWorkspace.data[idx] - x_data[i + 181]) +
          x_data[i + 341];
      obj->maxConstrWorkspace.data[idx] = d;
      v = fmax(v, fabs(d));
    }
  } else {
    v = 0.0;
    if (obj->Aineq.size[0] != 0) {
      i = (unsigned short)obj->sizes[2];
      if (i - 1 >= 0) {
        memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
               (unsigned int)i * sizeof(double));
      }
      b_xgemv(obj->nVar, obj->sizes[2], obj->Aineq.data, obj->ldA, x_data,
              obj->maxConstrWorkspace.data);
      i = (unsigned short)obj->sizes[2];
      for (idx = 0; idx < i; idx++) {
        v = fmax(v, obj->maxConstrWorkspace.data[idx]);
      }
    }
    memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0],
           160U * sizeof(double));
    b_xgemv(obj->nVar, 160, obj->Aeq.data, obj->ldA, x_data,
            obj->maxConstrWorkspace.data);
    for (idx = 0; idx < 160; idx++) {
      v = fmax(v, fabs(obj->maxConstrWorkspace.data[idx]));
    }
  }
  if (obj->sizes[3] > 0) {
    i = (unsigned short)obj->sizes[3];
    for (idx = 0; idx < i; idx++) {
      idxLB = obj->indexLB.data[idx] - 1;
      v = fmax(v, -x_data[idxLB] - obj->lb.data[idxLB]);
    }
  }
  if (obj->sizes[4] > 0) {
    i = (unsigned short)obj->sizes[4];
    for (idx = 0; idx < i; idx++) {
      idxLB = obj->indexUB.data[idx] - 1;
      v = fmax(v, x_data[idxLB] - obj->ub.data[idxLB]);
    }
  }
  if (obj->sizes[0] > 0) {
    i = (unsigned short)obj->sizes[0];
    for (idx = 0; idx < i; idx++) {
      v = fmax(v, fabs(x_data[obj->indexFixed.data[idx] - 1] -
                       obj->ub.data[obj->indexFixed.data[idx] - 1]));
    }
  }
  return v;
}

/*
 * File trailer for maxConstraintViolation.c
 *
 * [EOF]
 */
