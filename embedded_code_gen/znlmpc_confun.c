/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: znlmpc_confun.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "znlmpc_confun.h"
#include "all.h"
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double runtimedata_OutputMin[160]
 *                const double runtimedata_OutputMax[160]
 *                const double X[176]
 *                double e
 *                double c_data[]
 *                int c_size[2]
 *                double Jc_data[]
 *                int Jc_size[2]
 * Return Type  : void
 */
void outputBounds(const double runtimedata_OutputMin[160],
                  const double runtimedata_OutputMax[160], const double X[176],
                  double e, double c_data[], int c_size[2], double Jc_data[],
                  int Jc_size[2])
{
  static double c_tmp_data[12800];
  static double d_tmp_data[6400];
  static signed char Jx[51200];
  static signed char Jx_data[51200];
  double b_c_data[320];
  int tmp_size[2];
  int b_i;
  int i;
  int i1;
  int k;
  short b_tmp_data[320];
  short tmp_data[320];
  signed char Je[320];
  signed char Ck[256];
  bool bv[160];
  bool x[16];
  bool exitg1;
  bool guard1 = false;
  bool y;
  for (i = 0; i < 160; i++) {
    bv[i] = rtIsInf(runtimedata_OutputMin[i]);
  }
  all(bv, x);
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 16)) {
    if (!x[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  guard1 = false;
  if (y) {
    for (i = 0; i < 160; i++) {
      bv[i] = rtIsInf(runtimedata_OutputMax[i]);
    }
    all(bv, x);
    y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 16)) {
      if (!x[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
    if (y) {
      c_size[0] = 0;
      c_size[1] = 0;
      Jc_size[0] = 0;
      Jc_size[1] = 0;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }
  if (guard1) {
    double c[320];
    int trueCount;
    short ic[16];
    bool icf[320];
    for (b_i = 0; b_i < 320; b_i++) {
      c[b_i] = 0.0;
      icf[b_i] = true;
    }
    memset(&Jx[0], 0, 51200U * sizeof(signed char));
    memset(&Je[0], 0, 320U * sizeof(signed char));
    for (i = 0; i < 16; i++) {
      ic[i] = (short)(i + 1);
    }
    for (b_i = 0; b_i < 10; b_i++) {
      bool bv1[16];
      for (i = 0; i < 16; i++) {
        double d;
        i1 = b_i + 10 * i;
        d = runtimedata_OutputMin[i1];
        icf[ic[i] - 1] = ((!rtIsInf(d)) && (!rtIsNaN(d)));
        d = runtimedata_OutputMax[i1];
        x[i] = rtIsInf(d);
        bv1[i] = rtIsNaN(d);
      }
      for (i = 0; i < 16; i++) {
        icf[ic[i] + 15] = ((!x[i]) && (!bv1[i]));
      }
      y = false;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k <= 31)) {
        int b_ic[32];
        for (i = 0; i < 16; i++) {
          short i2;
          i2 = ic[i];
          b_ic[i] = i2 - 1;
          b_ic[i + 16] = i2 + 15;
        }
        if (icf[b_ic[k]]) {
          y = true;
          exitg1 = true;
        } else {
          k++;
        }
      }
      if (y) {
        signed char val[256];
        memset(&Ck[0], 0, 256U * sizeof(signed char));
        for (k = 0; k < 16; k++) {
          Ck[k + (k << 4)] = 1;
          c[ic[k] - 1] =
              (runtimedata_OutputMin[b_i + 10 * k] - e) - X[(b_i + 11 * k) + 1];
        }
        for (i = 0; i < 16; i++) {
          c[ic[i] + 15] =
              (X[(b_i + 11 * i) + 1] - runtimedata_OutputMax[b_i + 10 * i]) - e;
        }
        for (i = 0; i < 256; i++) {
          val[i] = (signed char)-Ck[i];
        }
        for (k = 0; k < 16; k++) {
          for (i = 0; i < 16; i++) {
            Jx[((ic[i] + 320 * k) + 5120 * b_i) - 1] = val[i + (k << 4)];
          }
        }
        for (k = 0; k < 16; k++) {
          for (i = 0; i < 16; i++) {
            Jx[((ic[i] + 320 * k) + 5120 * b_i) + 15] = Ck[i + (k << 4)];
          }
          Je[ic[k] - 1] = -1;
        }
        for (i = 0; i < 16; i++) {
          Je[ic[i] + 15] = -1;
        }
      }
      for (i = 0; i < 16; i++) {
        ic[i] = (short)(ic[i] + 32);
      }
    }
    trueCount = 0;
    k = 0;
    for (b_i = 0; b_i < 320; b_i++) {
      if (icf[b_i]) {
        trueCount++;
        tmp_data[k] = (short)(b_i + 1);
        k++;
      }
    }
    for (i = 0; i < trueCount; i++) {
      b_c_data[i] = c[tmp_data[i] - 1];
    }
    c_size[0] = trueCount;
    c_size[1] = 1;
    if (trueCount - 1 >= 0) {
      memcpy(&c_data[0], &b_c_data[0],
             (unsigned int)trueCount * sizeof(double));
    }
    trueCount = 0;
    k = 0;
    for (b_i = 0; b_i < 320; b_i++) {
      if (icf[b_i]) {
        trueCount++;
        b_tmp_data[k] = (short)(b_i + 1);
        k++;
      }
    }
    if (trueCount == 0) {
      Jc_size[0] = 0;
      Jc_size[1] = 0;
    } else {
      double varargin_2_data[6400];
      int b_tmp_size[2];
      signed char Je_data[320];
      signed char input_sizes_idx_0;
      for (i = 0; i < 10; i++) {
        for (i1 = 0; i1 < 16; i1++) {
          for (k = 0; k < trueCount; k++) {
            Jx_data[(k + trueCount * i1) + trueCount * 16 * i] =
                Jx[((b_tmp_data[k] + 320 * i1) + 5120 * i) - 1];
          }
        }
      }
      for (i = 0; i < trueCount; i++) {
        for (i1 = 0; i1 < 160; i1++) {
          Jx[i1 + 160 * i] = Jx_data[i + trueCount * i1];
        }
      }
      tmp_size[0] = trueCount;
      tmp_size[1] = 40;
      k = trueCount * 40;
      memset(&c_tmp_data[0], 0, (unsigned int)k * sizeof(double));
      mtimes(c_tmp_data, tmp_size, d_tmp_data, b_tmp_size);
      k = b_tmp_size[0];
      for (i = 0; i < k; i++) {
        for (i1 = 0; i1 < 20; i1++) {
          varargin_2_data[i1 + 20 * i] = d_tmp_data[i + b_tmp_size[0] * i1];
        }
      }
      if ((trueCount == 0) || (b_tmp_size[0] != 0)) {
        input_sizes_idx_0 = 20;
      } else {
        input_sizes_idx_0 = 0;
      }
      k = input_sizes_idx_0;
      for (i = 0; i < trueCount; i++) {
        Je_data[i] = Je[b_tmp_data[i] - 1];
      }
      Jc_size[0] = input_sizes_idx_0 + 161;
      Jc_size[1] = trueCount;
      for (i = 0; i < trueCount; i++) {
        for (i1 = 0; i1 < 160; i1++) {
          Jc_data[i1 + (input_sizes_idx_0 + 161) * i] = Jx[i1 + 160 * i];
        }
      }
      for (i = 0; i < trueCount; i++) {
        for (i1 = 0; i1 < k; i1++) {
          Jc_data[(i1 + (input_sizes_idx_0 + 161) * i) + 160] =
              varargin_2_data[i1 + input_sizes_idx_0 * i];
        }
      }
      for (i = 0; i < trueCount; i++) {
        Jc_data[(input_sizes_idx_0 + (input_sizes_idx_0 + 161) * i) + 160] =
            Je_data[i];
      }
    }
  }
}

/*
 * File trailer for znlmpc_confun.c
 *
 * [EOF]
 */
