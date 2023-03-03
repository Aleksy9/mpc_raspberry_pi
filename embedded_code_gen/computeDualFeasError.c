/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeDualFeasError.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "computeDualFeasError.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int nVar
 *                const double gradLag_data[]
 *                bool *gradOK
 *                double *val
 * Return Type  : void
 */
void computeDualFeasError(int nVar, const double gradLag_data[], bool *gradOK,
                          double *val)
{
  int idx;
  bool exitg1;
  *gradOK = true;
  *val = 0.0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= (unsigned short)nVar - 1)) {
    *gradOK = ((!rtIsInf(gradLag_data[idx])) && (!rtIsNaN(gradLag_data[idx])));
    if (!*gradOK) {
      exitg1 = true;
    } else {
      *val = fmax(*val, fabs(gradLag_data[idx]));
      idx++;
    }
  }
}

/*
 * File trailer for computeDualFeasError.c
 *
 * [EOF]
 */
