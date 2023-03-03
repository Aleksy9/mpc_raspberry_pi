/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mtimes.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "mtimes.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double A_data[]
 *                const int A_size[2]
 *                double C_data[]
 *                int C_size[2]
 * Return Type  : void
 */
void mtimes(const double A_data[], const int A_size[2], double C_data[],
            int C_size[2])
{
  int i;
  int j;
  int k;
  int mc;
  mc = A_size[0];
  C_size[0] = A_size[0];
  C_size[1] = 20;
  for (j = 0; j < 20; j++) {
    int boffset;
    int coffset;
    coffset = j * mc;
    boffset = j * 40;
    if (mc - 1 >= 0) {
      memset(&C_data[coffset], 0,
             (unsigned int)((mc + coffset) - coffset) * sizeof(double));
    }
    for (k = 0; k < 40; k++) {
      int aoffset;
      int bkj;
      aoffset = k * A_size[0];
      bkj = iv[boffset + k];
      for (i = 0; i < mc; i++) {
        int b_i;
        b_i = coffset + i;
        C_data[b_i] += A_data[aoffset + i] * (double)bkj;
      }
    }
  }
}

/*
 * File trailer for mtimes.c
 *
 * [EOF]
 */
