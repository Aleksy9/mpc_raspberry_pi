/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeGrad_StoreHx.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeGrad_StoreHx.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : d_struct_T *obj
 *                const double H[32761]
 *                const double f_data[]
 *                const double x_data[]
 * Return Type  : void
 */
void computeGrad_StoreHx(d_struct_T *obj, const double H[32761],
                         const double f_data[], const double x_data[])
{
  int iy;
  int k;
  switch (obj->objtype) {
  case 5: {
    int i;
    i = obj->nvar;
    if (i - 2 >= 0) {
      memset(&obj->grad.data[0], 0, (unsigned int)(i - 1) * sizeof(double));
    }
    obj->grad.data[obj->nvar - 1] = obj->gammaScalar;
  } break;
  case 3: {
    int i;
    d_xgemv(obj->nvar, obj->nvar, H, obj->nvar, x_data, obj->Hx.data);
    i = (unsigned short)obj->nvar;
    if (i - 1 >= 0) {
      memcpy(&obj->grad.data[0], &obj->Hx.data[0],
             (unsigned int)i * sizeof(double));
    }
    if (obj->hasLinear && (obj->nvar >= 1)) {
      int ixlast;
      ixlast = obj->nvar - 1;
      for (k = 0; k <= ixlast; k++) {
        obj->grad.data[k] += f_data[k];
      }
    }
  } break;
  default: {
    int i;
    int ixlast;
    ixlast = obj->maxVar - 1;
    d_xgemv(obj->nvar, obj->nvar, H, obj->nvar, x_data, obj->Hx.data);
    i = obj->nvar + 1;
    for (iy = i; iy <= ixlast; iy++) {
      obj->Hx.data[iy - 1] = obj->beta * x_data[iy - 1];
    }
    i = (unsigned short)(obj->maxVar - 1);
    memcpy(&obj->grad.data[0], &obj->Hx.data[0],
           (unsigned int)i * sizeof(double));
    if (obj->hasLinear && (obj->nvar >= 1)) {
      ixlast = obj->nvar - 1;
      for (k = 0; k <= ixlast; k++) {
        obj->grad.data[k] += f_data[k];
      }
    }
    ixlast = (obj->maxVar - obj->nvar) - 1;
    if (ixlast >= 1) {
      iy = obj->nvar;
      i = ixlast - 1;
      for (k = 0; k <= i; k++) {
        ixlast = iy + k;
        obj->grad.data[ixlast] += obj->rho;
      }
    }
  } break;
  }
}

/*
 * File trailer for computeGrad_StoreHx.c
 *
 * [EOF]
 */
