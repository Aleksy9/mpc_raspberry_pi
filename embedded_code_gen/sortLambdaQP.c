/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sortLambdaQP.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "sortLambdaQP.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double lambda_data[]
 *                int WorkingSet_nActiveConstr
 *                const int WorkingSet_sizes[5]
 *                const int WorkingSet_isActiveIdx[6]
 *                const int WorkingSet_Wid_data[]
 *                const int WorkingSet_Wlocalidx_data[]
 *                double workspace_data[]
 * Return Type  : void
 */
void sortLambdaQP(double lambda_data[], int WorkingSet_nActiveConstr,
                  const int WorkingSet_sizes[5],
                  const int WorkingSet_isActiveIdx[6],
                  const int WorkingSet_Wid_data[],
                  const int WorkingSet_Wlocalidx_data[],
                  double workspace_data[])
{
  if (WorkingSet_nActiveConstr != 0) {
    int idx;
    int idxOffset;
    int mAll;
    mAll =
        (((WorkingSet_sizes[0] + WorkingSet_sizes[3]) + WorkingSet_sizes[4]) +
         WorkingSet_sizes[2]) +
        159;
    idx = (unsigned short)(mAll + 1);
    if (idx - 1 >= 0) {
      memcpy(&workspace_data[0], &lambda_data[0],
             (unsigned int)idx * sizeof(double));
    }
    memset(&lambda_data[0], 0, (unsigned int)(mAll + 1) * sizeof(double));
    mAll = 0;
    idx = 0;
    while ((idx + 1 <= WorkingSet_nActiveConstr) &&
           (WorkingSet_Wid_data[idx] <= 2)) {
      if (WorkingSet_Wid_data[idx] == 1) {
        idxOffset = 1;
      } else {
        idxOffset = WorkingSet_isActiveIdx[1];
      }
      lambda_data[(idxOffset + WorkingSet_Wlocalidx_data[idx]) - 2] =
          workspace_data[mAll];
      mAll++;
      idx++;
    }
    while (idx + 1 <= WorkingSet_nActiveConstr) {
      switch (WorkingSet_Wid_data[idx]) {
      case 3:
        idxOffset = WorkingSet_isActiveIdx[2];
        break;
      case 4:
        idxOffset = WorkingSet_isActiveIdx[3];
        break;
      default:
        idxOffset = WorkingSet_isActiveIdx[4];
        break;
      }
      lambda_data[(idxOffset + WorkingSet_Wlocalidx_data[idx]) - 2] =
          workspace_data[mAll];
      mAll++;
      idx++;
    }
  }
}

/*
 * File trailer for sortLambdaQP.c
 *
 * [EOF]
 */
