/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: nlmpcmoveCodeGeneration.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "nlmpcmoveCodeGeneration.h"
#include "cost_fct_3D_model.h"
#include "fmincon.h"
#include "mtimes.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "state_update_3D_model.h"
#include "znlmpc_confun.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double runtimedata_x[16]
 *                const double runtimedata_OutputMin[160]
 *                const double runtimedata_OutputMax[160]
 *                double runtimedata_Parameters
 *                const double z[181]
 *                double varargout_1_data[]
 *                int varargout_1_size[2]
 *                double varargout_2[160]
 *                double varargout_3_data[]
 *                int varargout_3_size[2]
 *                double varargout_4[28960]
 * Return Type  : void
 */
void c_nlmpcmoveCodeGeneration_anonF(
    const double runtimedata_x[16], const double runtimedata_OutputMin[160],
    const double runtimedata_OutputMax[160], double runtimedata_Parameters,
    const double z[181], double varargout_1_data[], int varargout_1_size[2],
    double varargout_2[160], double varargout_3_data[], int varargout_3_size[2],
    double varargout_4[28960])
{
  static double Jc_data[57920];
  static double Jx[25600];
  static double Jmv[6400];
  double b_Jmv[3200];
  double c_data[320];
  double X[176];
  double b_X[176];
  double b_z[160];
  double U[44];
  double Umv[44];
  double a[40];
  double a_tmp;
  double b_a_tmp;
  double du;
  int Jc_size[2];
  int c_size[2];
  int U_tmp;
  int b_i;
  int i;
  int k;
  short input_sizes_idx_0;
  unsigned char ic[16];
  unsigned char sizes_idx_1;
  memset(&X[0], 0, 176U * sizeof(double));
  memset(&Umv[0], 0, 44U * sizeof(double));
  for (i = 0; i < 40; i++) {
    du = 0.0;
    for (b_i = 0; b_i < 20; b_i++) {
      du += (double)iv[i + 40 * b_i] * z[b_i + 160];
    }
    a[i] = du;
  }
  for (i = 0; i < 4; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      Umv[b_i + 11 * i] = a[i + (b_i << 2)];
    }
  }
  memcpy(&b_z[0], &z[0], 160U * sizeof(double));
  for (i = 0; i < 16; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      X[(b_i + 11 * i) + 1] = b_z[i + (b_i << 4)];
    }
    X[11 * i] = runtimedata_x[i];
  }
  for (b_i = 0; b_i < 4; b_i++) {
    Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
    memcpy(&U[b_i * 11], &Umv[b_i * 11], 11U * sizeof(double));
  }
  memset(&Jx[0], 0, 25600U * sizeof(double));
  memset(&Jmv[0], 0, 6400U * sizeof(double));
  memset(&varargout_2[0], 0, 160U * sizeof(double));
  for (i = 0; i < 16; i++) {
    ic[i] = (unsigned char)((unsigned int)i + 1U);
  }
  for (i = 0; i < 11; i++) {
    U_tmp = i << 2;
    Umv[U_tmp] = U[i];
    Umv[U_tmp + 1] = U[i + 11];
    Umv[U_tmp + 2] = U[i + 22];
    Umv[U_tmp + 3] = U[i + 33];
  }
  for (i = 0; i < 11; i++) {
    for (b_i = 0; b_i < 16; b_i++) {
      b_X[b_i + (i << 4)] = X[i + 11 * b_i];
    }
  }
  a_tmp = runtimedata_Parameters / 2.0;
  b_a_tmp = runtimedata_Parameters / 6.0;
  for (b_i = 0; b_i < 10; b_i++) {
    double val[256];
    double b_val[64];
    double b_k1[16];
    double b_xk[16];
    double k1[16];
    double k2[16];
    double k3[16];
    double k4[16];
    double xa[16];
    double xk[16];
    double uk[4];
    int uk_tmp;
    uk_tmp = b_i << 2;
    uk[0] = Umv[uk_tmp];
    uk[1] = Umv[uk_tmp + 1];
    uk[2] = Umv[uk_tmp + 2];
    uk[3] = Umv[uk_tmp + 3];
    /*  States = {x,y,Vx,Vy,theta, omega} */
    /*  Inputs = {T, alpha_t} */
    /*  RK4 */
    U_tmp = b_i << 4;
    state_deriv(&b_X[U_tmp], &Umv[uk_tmp], k1);
    for (i = 0; i < 16; i++) {
      du = b_X[i + U_tmp];
      xk[i] = du;
      xa[i] = du + a_tmp * k1[i];
    }
    state_deriv(xa, &Umv[uk_tmp], k2);
    for (i = 0; i < 16; i++) {
      xa[i] = b_X[i + U_tmp] + a_tmp * k2[i];
    }
    state_deriv(xa, &Umv[uk_tmp], k3);
    for (i = 0; i < 16; i++) {
      xa[i] = b_X[i + U_tmp] + runtimedata_Parameters * k3[i];
    }
    state_deriv(xa, &Umv[uk_tmp], k4);
    /*  disp("state") */
    /*  disp(state) */
    /*  disp("new_state") */
    /*  disp(new_state) */
    /* aero_force_x = - 1/(2)*rho*S*V* ( Cd*(vx*cos(theta) + vy*sin(theta))); */
    /* aero_force_y = - 1/(2)*rho*S*V* ( (CLa + Cd) * (-vx*sin(theta) +
     * vy*cos(theta)) ); */
    for (k = 0; k < 16; k++) {
      du = b_X[k + U_tmp];
      k1[k] = du + b_a_tmp * (((k1[k] + 2.0 * k2[k]) + 2.0 * k3[k]) + k4[k]);
      du = fabs(du);
      xa[k] = du;
      if (du < 1.0) {
        xa[k] = 1.0;
      }
    }
    for (U_tmp = 0; U_tmp < 16; U_tmp++) {
      double dx;
      dx = 1.0E-6 * xa[U_tmp];
      xk[U_tmp] += dx;
      /*  States = {x,y,Vx,Vy,theta, omega} */
      /*  Inputs = {T, alpha_t} */
      /*  RK4 */
      state_deriv(xk, &Umv[uk_tmp], b_k1);
      for (i = 0; i < 16; i++) {
        b_xk[i] = xk[i] + a_tmp * b_k1[i];
      }
      state_deriv(b_xk, &Umv[uk_tmp], k2);
      for (i = 0; i < 16; i++) {
        b_xk[i] = xk[i] + a_tmp * k2[i];
      }
      state_deriv(b_xk, &Umv[uk_tmp], k3);
      for (i = 0; i < 16; i++) {
        b_xk[i] = xk[i] + runtimedata_Parameters * k3[i];
      }
      state_deriv(b_xk, &Umv[uk_tmp], k4);
      /*  disp("state") */
      /*  disp(state) */
      /*  disp("new_state") */
      /*  disp(new_state) */
      /* aero_force_x = - 1/(2)*rho*S*V* ( Cd*(vx*cos(theta) + vy*sin(theta)));
       */
      /* aero_force_y = - 1/(2)*rho*S*V* ( (CLa + Cd) * (-vx*sin(theta) +
       * vy*cos(theta)) ); */
      for (i = 0; i < 16; i++) {
        du =
            xk[i] + b_a_tmp * (((b_k1[i] + 2.0 * k2[i]) + 2.0 * k3[i]) + k4[i]);
        b_k1[i] = du;
        val[i + (U_tmp << 4)] = (du - k1[i]) / dx;
      }
      xk[U_tmp] -= dx;
    }
    for (k = 0; k < 4; k++) {
      du = fabs(Umv[k + uk_tmp]);
      if (du < 1.0) {
        du = 1.0;
      }
      du *= 1.0E-6;
      uk[k] += du;
      /*  States = {x,y,Vx,Vy,theta, omega} */
      /*  Inputs = {T, alpha_t} */
      /*  RK4 */
      state_deriv(xk, uk, b_k1);
      for (i = 0; i < 16; i++) {
        b_xk[i] = xk[i] + a_tmp * b_k1[i];
      }
      state_deriv(b_xk, uk, k2);
      for (i = 0; i < 16; i++) {
        b_xk[i] = xk[i] + a_tmp * k2[i];
      }
      state_deriv(b_xk, uk, k3);
      for (i = 0; i < 16; i++) {
        b_xk[i] = xk[i] + runtimedata_Parameters * k3[i];
      }
      state_deriv(b_xk, uk, k4);
      /*  disp("state") */
      /*  disp(state) */
      /*  disp("new_state") */
      /*  disp(new_state) */
      /* aero_force_x = - 1/(2)*rho*S*V* ( Cd*(vx*cos(theta) + vy*sin(theta)));
       */
      /* aero_force_y = - 1/(2)*rho*S*V* ( (CLa + Cd) * (-vx*sin(theta) +
       * vy*cos(theta)) ); */
      uk[k] -= du;
      for (i = 0; i < 16; i++) {
        b_val[i + (k << 4)] =
            ((xk[i] +
              b_a_tmp * (((b_k1[i] + 2.0 * k2[i]) + 2.0 * k3[i]) + k4[i])) -
             k1[i]) /
            du;
      }
    }
    for (k = 0; k < 16; k++) {
      sizes_idx_1 = ic[k];
      varargout_2[sizes_idx_1 - 1] = b_X[k + ((b_i + 1) << 4)] - k1[k];
      Jx[((sizes_idx_1 + 160 * k) + 2560 * b_i) - 1] = 1.0;
    }
    if (b_i + 1 > 1) {
      for (i = 0; i < 256; i++) {
        val[i] = -val[i];
      }
      for (k = 0; k < 16; k++) {
        for (i = 0; i < 16; i++) {
          Jx[((ic[i] + 160 * k) + 2560 * (b_i - 1)) - 1] = val[i + (k << 4)];
        }
      }
    }
    for (i = 0; i < 64; i++) {
      b_val[i] = -b_val[i];
    }
    for (k = 0; k < 4; k++) {
      for (i = 0; i < 16; i++) {
        Jmv[((ic[i] + 160 * k) + 640 * b_i) - 1] = b_val[i + (k << 4)];
      }
    }
    for (i = 0; i < 16; i++) {
      ic[i] = (unsigned char)(ic[i] + 16U);
    }
  }
  outputBounds(runtimedata_OutputMin, runtimedata_OutputMax, X, z[180], c_data,
               c_size, Jc_data, Jc_size);
  sizes_idx_1 = (unsigned char)((c_size[0] != 0) && (c_size[1] != 0));
  if ((sizes_idx_1 == 0) || ((c_size[0] != 0) && (c_size[1] != 0))) {
    input_sizes_idx_0 = (short)c_size[0];
  } else {
    input_sizes_idx_0 = 0;
  }
  varargout_1_size[0] = input_sizes_idx_0;
  varargout_1_size[1] = sizes_idx_1;
  U_tmp = sizes_idx_1;
  for (i = 0; i < U_tmp; i++) {
    k = input_sizes_idx_0;
    if (k - 1 >= 0) {
      memcpy(&varargout_1_data[0], &c_data[0],
             (unsigned int)k * sizeof(double));
    }
  }
  if ((Jc_size[0] != 0) && (Jc_size[1] != 0)) {
    sizes_idx_1 = (unsigned char)Jc_size[0];
  } else {
    sizes_idx_1 = 0U;
  }
  if ((sizes_idx_1 == 0) || ((Jc_size[0] != 0) && (Jc_size[1] != 0))) {
    input_sizes_idx_0 = (short)Jc_size[1];
  } else {
    input_sizes_idx_0 = 0;
  }
  varargout_3_size[0] = sizes_idx_1;
  varargout_3_size[1] = input_sizes_idx_0;
  U_tmp = input_sizes_idx_0;
  for (i = 0; i < U_tmp; i++) {
    k = sizes_idx_1;
    for (b_i = 0; b_i < k; b_i++) {
      varargout_3_data[b_i + sizes_idx_1 * i] = Jc_data[b_i + sizes_idx_1 * i];
    }
  }
  for (i = 0; i < 20; i++) {
    for (b_i = 0; b_i < 160; b_i++) {
      du = 0.0;
      for (U_tmp = 0; U_tmp < 40; U_tmp++) {
        du += Jmv[b_i + 160 * U_tmp] * (double)iv[U_tmp + 40 * i];
      }
      b_Jmv[i + 20 * b_i] = du;
    }
  }
  for (i = 0; i < 160; i++) {
    for (b_i = 0; b_i < 160; b_i++) {
      varargout_4[b_i + 181 * i] = Jx[i + 160 * b_i];
    }
    memcpy(&varargout_4[i * 181 + 160], &b_Jmv[i * 20], 20U * sizeof(double));
    varargout_4[181 * i + 180] = 0.0;
  }
}

/*
 * Arguments    : const double x[16]
 *                const double lastMV[4]
 *                struct1_T *onlinedata
 *                double mv[4]
 *                struct2_T *info
 * Return Type  : void
 */
void nlmpcmoveCodeGeneration(const double x[16], const double lastMV[4],
                             struct1_T *onlinedata, double mv[4],
                             struct2_T *info)
{
  static const double varargin_26[40] = {100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         100.0,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571,
                                         -0.78534031413612571};
  static const double varargin_28[40] = {1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         1400.0,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571,
                                         0.78534031413612571};
  static const double varargin_30[40] = {-500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -500.0,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792,
                                         -0.17452006980802792};
  static const double varargin_32[40] = {500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         500.0,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792,
                                         0.17452006980802792};
  static double A_data[32160];
  static double Au[6400];
  static double Auf_data[6400];
  static const signed char b_a[800] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0};
  static const signed char varargin_10[160] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const signed char b_iv[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10};
  i_struct_T b_expl_temp;
  i_struct_T c_expl_temp;
  j_struct_T d_expl_temp;
  j_struct_T expl_temp;
  l_struct_T Out;
  double dv[181];
  double z[181];
  double z0[181];
  double zUB[181];
  double Bu[160];
  double ref[160];
  double Umv[44];
  double b_onlinedata[40];
  double a[20];
  double ic[4];
  double ExitFlag;
  double d;
  int Au_tmp;
  int b_i;
  int i;
  int idx;
  int ii_size;
  unsigned char ii_data[160];
  signed char As[16];
  bool icf[160];
  bool exitg1;
  for (i = 0; i < 16; i++) {
    ref[10 * i] = onlinedata->ref[i];
    for (idx = 0; idx < 9; idx++) {
      ref[(idx + 10 * i) + 1] = onlinedata->ref[i];
    }
  }
  for (i = 0; i < 10; i++) {
    for (idx = 0; idx < 16; idx++) {
      Bu[idx + (i << 4)] = onlinedata->X0[i + 10 * idx];
    }
    idx = i << 2;
    b_onlinedata[idx] = onlinedata->MV0[i];
    b_onlinedata[idx + 1] = onlinedata->MV0[i + 10];
    b_onlinedata[idx + 2] = onlinedata->MV0[i + 20];
    b_onlinedata[idx + 3] = onlinedata->MV0[i + 30];
  }
  for (i = 0; i < 20; i++) {
    d = 0.0;
    for (idx = 0; idx < 40; idx++) {
      d += (double)b_a[i + 20 * idx] * b_onlinedata[idx];
    }
    a[i] = d;
  }
  memcpy(&z0[0], &Bu[0], 160U * sizeof(double));
  memcpy(&z0[160], &a[0], 20U * sizeof(double));
  z0[180] = onlinedata->Slack0;
  memcpy(&expl_temp.References[0], &ref[0], 160U * sizeof(double));
  memcpy(&b_expl_temp.ref[0], &ref[0], 160U * sizeof(double));
  for (i = 0; i < 40; i++) {
    b_expl_temp.MVRateWeights[i] = 0.1;
  }
  for (i = 0; i < 160; i++) {
    b_expl_temp.OutputMin[i] = rtMinusInf;
    b_expl_temp.OutputMax[i] = rtInf;
    b_expl_temp.StateMin[i] = rtMinusInf;
    b_expl_temp.StateMax[i] = rtInf;
    zUB[i] = rtInf;
  }
  for (i = 0; i < 20; i++) {
    zUB[i + 160] = rtInf;
  }
  zUB[180] = rtInf;
  memset(&info->Xopt[0], 0, 176U * sizeof(double));
  memset(&Umv[0], 0, 44U * sizeof(double));
  for (i = 0; i < 40; i++) {
    d = 0.0;
    for (idx = 0; idx < 20; idx++) {
      d += (double)iv[i + 40 * idx] * z0[idx + 160];
    }
    b_onlinedata[i] = d;
  }
  for (i = 0; i < 4; i++) {
    for (idx = 0; idx < 10; idx++) {
      Umv[idx + 11 * i] = b_onlinedata[i + (idx << 2)];
    }
  }
  memcpy(&Bu[0], &z0[0], 160U * sizeof(double));
  for (i = 0; i < 16; i++) {
    for (idx = 0; idx < 10; idx++) {
      info->Xopt[(idx + 11 * i) + 1] = Bu[i + (idx << 4)];
    }
    info->Xopt[11 * i] = x[i];
  }
  for (b_i = 0; b_i < 4; b_i++) {
    Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
    memcpy(&info->MVopt[b_i * 11], &Umv[b_i * 11], 11U * sizeof(double));
  }
  ExitFlag = cost_fct_3D_model(info->Xopt, ref);
  if (ExitFlag <= ExitFlag) {
    zUB[180] = 0.0;
  }
  memset(&Au[0], 0, 6400U * sizeof(double));
  memset(&Bu[0], 0, 160U * sizeof(double));
  memset(&icf[0], 0, 160U * sizeof(bool));
  ic[0] = 1.0;
  ic[1] = 2.0;
  ic[2] = 3.0;
  ic[3] = 4.0;
  for (i = 0; i < 16; i++) {
    As[i] = 0;
  }
  As[0] = 1;
  As[5] = 1;
  As[10] = 1;
  As[15] = 1;
  for (b_i = 0; b_i < 10; b_i++) {
    double Bu_idx_2;
    double Bu_idx_3;
    icf[(int)ic[0] - 1] = true;
    icf[(int)ic[1] - 1] = true;
    icf[(int)ic[2] - 1] = true;
    icf[(int)ic[3] - 1] = true;
    icf[(int)(ic[0] + 4.0) - 1] = true;
    icf[(int)(ic[1] + 4.0) - 1] = true;
    icf[(int)(ic[2] + 4.0) - 1] = true;
    icf[(int)(ic[3] + 4.0) - 1] = true;
    icf[(int)(ic[0] + 8.0) - 1] = true;
    icf[(int)(ic[1] + 8.0) - 1] = true;
    icf[(int)(ic[2] + 8.0) - 1] = true;
    icf[(int)(ic[3] + 8.0) - 1] = true;
    for (i = 0; i < 4; i++) {
      icf[(int)(ic[i] + 12.0) - 1] = true;
      idx = i << 2;
      Au[(((int)ic[0] + 160 * i) + 640 * b_i) - 1] = -(double)As[idx];
      Au[(((int)ic[1] + 160 * i) + 640 * b_i) - 1] = -(double)As[idx + 1];
      Au[(((int)ic[2] + 160 * i) + 640 * b_i) - 1] = -(double)As[idx + 2];
      Au[(((int)ic[3] + 160 * i) + 640 * b_i) - 1] = -(double)As[idx + 3];
    }
    d = ic[0];
    ExitFlag = ic[1];
    Bu_idx_2 = ic[2];
    Bu_idx_3 = ic[3];
    for (i = 0; i < 4; i++) {
      idx = i << 2;
      Au[(((int)(d + 4.0) + 160 * i) + 640 * b_i) - 1] = As[idx];
      Au[(((int)(ExitFlag + 4.0) + 160 * i) + 640 * b_i) - 1] = As[idx + 1];
      Au[(((int)(Bu_idx_2 + 4.0) + 160 * i) + 640 * b_i) - 1] = As[idx + 2];
      Au[(((int)(Bu_idx_3 + 4.0) + 160 * i) + 640 * b_i) - 1] = As[idx + 3];
    }
    for (i = 0; i < 4; i++) {
      idx = i << 2;
      Au[(((int)(d + 8.0) + 160 * i) + 640 * b_i) - 1] = -(double)As[idx];
      Au[(((int)(ExitFlag + 8.0) + 160 * i) + 640 * b_i) - 1] =
          -(double)As[idx + 1];
      Au[(((int)(Bu_idx_2 + 8.0) + 160 * i) + 640 * b_i) - 1] =
          -(double)As[idx + 2];
      Au[(((int)(Bu_idx_3 + 8.0) + 160 * i) + 640 * b_i) - 1] =
          -(double)As[idx + 3];
    }
    for (i = 0; i < 4; i++) {
      idx = i << 2;
      Au[(((int)(d + 12.0) + 160 * i) + 640 * b_i) - 1] = As[idx];
      Au[(((int)(ExitFlag + 12.0) + 160 * i) + 640 * b_i) - 1] = As[idx + 1];
      Au[(((int)(Bu_idx_2 + 12.0) + 160 * i) + 640 * b_i) - 1] = As[idx + 2];
      Au[(((int)(Bu_idx_3 + 12.0) + 160 * i) + 640 * b_i) - 1] = As[idx + 3];
    }
    Bu[(int)ic[0] - 1] = -varargin_30[b_i];
    Bu[(int)ic[1] - 1] = -varargin_30[b_i + 10];
    Bu[(int)ic[2] - 1] = -varargin_30[b_i + 20];
    Bu[(int)ic[3] - 1] = -varargin_30[b_i + 30];
    Bu[(int)(ic[0] + 4.0) - 1] = varargin_32[b_i];
    Bu[(int)(ic[1] + 4.0) - 1] = varargin_32[b_i + 10];
    Bu[(int)(ic[2] + 4.0) - 1] = varargin_32[b_i + 20];
    Bu[(int)(ic[3] + 4.0) - 1] = varargin_32[b_i + 30];
    Bu[(int)(ic[0] + 8.0) - 1] = -varargin_26[b_i];
    Bu[(int)(ic[1] + 8.0) - 1] = -varargin_26[b_i + 10];
    Bu[(int)(ic[2] + 8.0) - 1] = -varargin_26[b_i + 20];
    Bu[(int)(ic[3] + 8.0) - 1] = -varargin_26[b_i + 30];
    Bu[(int)(ic[0] + 12.0) - 1] = varargin_28[b_i];
    Bu[(int)(ic[1] + 12.0) - 1] = varargin_28[b_i + 10];
    Bu[(int)(ic[2] + 12.0) - 1] = varargin_28[b_i + 20];
    Bu[(int)(ic[3] + 12.0) - 1] = varargin_28[b_i + 30];
    if (b_i + 1 == 1) {
      ExitFlag = Bu[(int)ic[1] - 1] - lastMV[1];
      Bu_idx_2 = Bu[(int)ic[2] - 1] - lastMV[2];
      Bu_idx_3 = Bu[(int)ic[3] - 1] - lastMV[3];
      Bu[(int)ic[0] - 1] -= lastMV[0];
      Bu[(int)ic[1] - 1] = ExitFlag;
      Bu[(int)ic[2] - 1] = Bu_idx_2;
      Bu[(int)ic[3] - 1] = Bu_idx_3;
      ExitFlag = Bu[(int)(ic[1] + 4.0) - 1] + lastMV[1];
      Bu_idx_2 = Bu[(int)(ic[2] + 4.0) - 1] + lastMV[2];
      Bu_idx_3 = Bu[(int)(ic[3] + 4.0) - 1] + lastMV[3];
      Bu[(int)(ic[0] + 4.0) - 1] += lastMV[0];
      Bu[(int)(ic[1] + 4.0) - 1] = ExitFlag;
      Bu[(int)(ic[2] + 4.0) - 1] = Bu_idx_2;
      Bu[(int)(ic[3] + 4.0) - 1] = Bu_idx_3;
    } else {
      idx = 640 * (b_i - 1);
      for (i = 0; i < 4; i++) {
        Au_tmp = i << 2;
        Au[(((int)d + 160 * i) + idx) - 1] = As[Au_tmp];
        Au[(((int)ExitFlag + 160 * i) + idx) - 1] = As[Au_tmp + 1];
        Au[(((int)Bu_idx_2 + 160 * i) + idx) - 1] = As[Au_tmp + 2];
        Au[(((int)Bu_idx_3 + 160 * i) + idx) - 1] = As[Au_tmp + 3];
      }
      idx = 640 * (b_i - 1);
      for (i = 0; i < 4; i++) {
        Au_tmp = i << 2;
        Au[(((int)(d + 4.0) + 160 * i) + idx) - 1] = -(double)As[Au_tmp];
        Au[(((int)(ExitFlag + 4.0) + 160 * i) + idx) - 1] =
            -(double)As[Au_tmp + 1];
        Au[(((int)(Bu_idx_2 + 4.0) + 160 * i) + idx) - 1] =
            -(double)As[Au_tmp + 2];
        Au[(((int)(Bu_idx_3 + 4.0) + 160 * i) + idx) - 1] =
            -(double)As[Au_tmp + 3];
      }
    }
    ic[0] += 16.0;
    ic[1] += 16.0;
    ic[2] += 16.0;
    ic[3] += 16.0;
  }
  idx = 0;
  Au_tmp = 0;
  exitg1 = false;
  while ((!exitg1) && (Au_tmp < 160)) {
    if (icf[Au_tmp]) {
      idx++;
      ii_data[idx - 1] = (unsigned char)(Au_tmp + 1);
      if (idx >= 160) {
        exitg1 = true;
      } else {
        Au_tmp++;
      }
    } else {
      Au_tmp++;
    }
  }
  if (idx < 1) {
    ii_size = 0;
  } else {
    ii_size = idx;
  }
  if (ii_size > 0) {
    for (i = 0; i < ii_size; i++) {
      ref[i] = Bu[ii_data[i] - 1];
    }
    for (idx = 0; idx < 4; idx++) {
      for (Au_tmp = 0; Au_tmp < 10; Au_tmp++) {
        for (b_i = 0; b_i < ii_size; b_i++) {
          Auf_data[(b_i + ii_size * idx) + ii_size * 4 * Au_tmp] =
              Au[((ii_data[b_i] + 160 * idx) + 640 * Au_tmp) - 1];
        }
      }
    }
    int ii[2];
    int tmp_size[2];
    ii[0] = ii_size;
    ii[1] = 40;
    mtimes(Auf_data, ii, Au, tmp_size);
    for (i = 0; i < 160; i++) {
      for (idx = 0; idx < ii_size; idx++) {
        A_data[idx + ii_size * i] = 0.0;
      }
    }
    for (i = 0; i < 20; i++) {
      for (idx = 0; idx < ii_size; idx++) {
        A_data[idx + ii_size * (i + 160)] = Au[idx + ii_size * i];
      }
    }
    memset(&A_data[ii_size * 180], 0,
           (unsigned int)((ii_size + ii_size * 180) - ii_size * 180) *
               sizeof(double));
  } else {
    ii_size = 0;
  }
  b_expl_temp.Parameters[0] = onlinedata->Parameters[0];
  b_expl_temp.ECRWeight = 100000.0;
  for (i = 0; i < 40; i++) {
    b_expl_temp.MVScaledTarget[i] = 0.0;
    b_expl_temp.MVRateMax[i] = varargin_32[i];
    b_expl_temp.MVRateMin[i] = varargin_30[i];
    b_expl_temp.MVMax[i] = varargin_28[i];
    b_expl_temp.MVMin[i] = varargin_26[i];
    b_expl_temp.MVWeights[i] = 0.0;
  }
  for (i = 0; i < 160; i++) {
    b_expl_temp.OutputWeights[i] = varargin_10[i];
  }
  b_expl_temp.lastMV[0] = lastMV[0];
  b_expl_temp.lastMV[1] = lastMV[1];
  b_expl_temp.lastMV[2] = lastMV[2];
  b_expl_temp.lastMV[3] = lastMV[3];
  memcpy(&b_expl_temp.x[0], &x[0], 16U * sizeof(double));
  expl_temp.PassivityUsePredictedX = true;
  expl_temp.OutputPassivityIndex = 0.1;
  expl_temp.InputPassivityIndex = 0.0;
  expl_temp.MVIndex[0] = 1.0;
  expl_temp.MVIndex[1] = 2.0;
  expl_temp.MVIndex[2] = 3.0;
  expl_temp.MVIndex[3] = 4.0;
  expl_temp.NumOfInputs = 4.0;
  expl_temp.NumOfOutputs = 16.0;
  expl_temp.NumOfStates = 16.0;
  expl_temp.PredictionHorizon = 10.0;
  memset(&expl_temp.MVTarget[0], 0, 40U * sizeof(double));
  expl_temp.LastMV[0] = lastMV[0];
  expl_temp.LastMV[1] = lastMV[1];
  expl_temp.LastMV[2] = lastMV[2];
  expl_temp.LastMV[3] = lastMV[3];
  memcpy(&expl_temp.CurrentStates[0], &x[0], 16U * sizeof(double));
  expl_temp.Ts = 0.1;
  c_expl_temp.Parameters[0] = onlinedata->Parameters[0];
  for (i = 0; i < 40; i++) {
    c_expl_temp.MVScaledTarget[i] = 0.0;
    c_expl_temp.MVRateMax[i] = varargin_32[i];
    c_expl_temp.MVRateMin[i] = varargin_30[i];
    c_expl_temp.MVMax[i] = varargin_28[i];
    c_expl_temp.MVMin[i] = varargin_26[i];
  }
  for (i = 0; i < 160; i++) {
    c_expl_temp.StateMax[i] = rtInf;
    c_expl_temp.StateMin[i] = rtMinusInf;
    c_expl_temp.OutputMax[i] = rtInf;
    c_expl_temp.OutputMin[i] = rtMinusInf;
  }
  c_expl_temp.ECRWeight = 100000.0;
  for (i = 0; i < 40; i++) {
    c_expl_temp.MVRateWeights[i] = 0.1;
    c_expl_temp.MVWeights[i] = 0.0;
  }
  for (i = 0; i < 160; i++) {
    c_expl_temp.OutputWeights[i] = varargin_10[i];
    c_expl_temp.ref[i] = b_expl_temp.ref[i];
  }
  c_expl_temp.lastMV[0] = lastMV[0];
  c_expl_temp.lastMV[1] = lastMV[1];
  c_expl_temp.lastMV[2] = lastMV[2];
  c_expl_temp.lastMV[3] = lastMV[3];
  memcpy(&c_expl_temp.x[0], &x[0], 16U * sizeof(double));
  d_expl_temp.PassivityUsePredictedX = true;
  d_expl_temp.OutputPassivityIndex = 0.1;
  d_expl_temp.InputPassivityIndex = 0.0;
  d_expl_temp.MVIndex[0] = 1.0;
  d_expl_temp.MVIndex[1] = 2.0;
  d_expl_temp.MVIndex[2] = 3.0;
  d_expl_temp.MVIndex[3] = 4.0;
  d_expl_temp.NumOfInputs = 4.0;
  d_expl_temp.NumOfOutputs = 16.0;
  d_expl_temp.NumOfStates = 16.0;
  d_expl_temp.PredictionHorizon = 10.0;
  memset(&d_expl_temp.MVTarget[0], 0, 40U * sizeof(double));
  memcpy(&d_expl_temp.References[0], &expl_temp.References[0],
         160U * sizeof(double));
  d_expl_temp.LastMV[0] = lastMV[0];
  d_expl_temp.LastMV[1] = lastMV[1];
  d_expl_temp.LastMV[2] = lastMV[2];
  d_expl_temp.LastMV[3] = lastMV[3];
  memcpy(&d_expl_temp.CurrentStates[0], &x[0], 16U * sizeof(double));
  d_expl_temp.Ts = 0.1;
  for (i = 0; i < 160; i++) {
    dv[i] = rtMinusInf;
  }
  for (i = 0; i < 20; i++) {
    dv[i + 160] = rtMinusInf;
  }
  dv[180] = 0.0;
  fmincon(&b_expl_temp, &expl_temp, z0, A_data, ref, ii_size, dv, zUB,
          &c_expl_temp, &d_expl_temp, z, &info->Cost, &ExitFlag, &Out);
  if ((ExitFlag == 0.0) && (Out.constrviolation > 1.0E-6)) {
    ExitFlag = -2.0;
  }
  memset(&info->Xopt[0], 0, 176U * sizeof(double));
  memset(&Umv[0], 0, 44U * sizeof(double));
  for (i = 0; i < 40; i++) {
    d = 0.0;
    for (idx = 0; idx < 20; idx++) {
      d += (double)iv[i + 40 * idx] * z[idx + 160];
    }
    b_onlinedata[i] = d;
  }
  for (i = 0; i < 4; i++) {
    for (idx = 0; idx < 10; idx++) {
      Umv[idx + 11 * i] = b_onlinedata[i + (idx << 2)];
    }
  }
  memcpy(&Bu[0], &z[0], 160U * sizeof(double));
  for (i = 0; i < 16; i++) {
    for (idx = 0; idx < 10; idx++) {
      info->Xopt[(idx + 11 * i) + 1] = Bu[i + (idx << 4)];
    }
    info->Xopt[11 * i] = x[i];
  }
  for (b_i = 0; b_i < 4; b_i++) {
    Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
    memcpy(&info->MVopt[b_i * 11], &Umv[b_i * 11], 11U * sizeof(double));
  }
  if ((ExitFlag > 0.0) || (ExitFlag == 0.0)) {
    mv[0] = info->MVopt[0];
    mv[1] = info->MVopt[11];
    mv[2] = info->MVopt[22];
    mv[3] = info->MVopt[33];
  } else {
    mv[0] = lastMV[0];
    mv[1] = lastMV[1];
    mv[2] = lastMV[2];
    mv[3] = lastMV[3];
  }
  info->ExitFlag = ExitFlag;
  info->Iterations = Out.iterations;
  for (i = 0; i < 4; i++) {
    memcpy(&onlinedata->MV0[i * 10], &info->MVopt[i * 11 + 1],
           10U * sizeof(double));
  }
  for (i = 0; i < 16; i++) {
    for (idx = 0; idx < 10; idx++) {
      onlinedata->X0[idx + 10 * i] = info->Xopt[b_iv[idx] + 11 * i];
    }
  }
  onlinedata->Slack0 = fmax(0.0, z[180]);
  memcpy(&info->Yopt[0], &info->Xopt[0], 176U * sizeof(double));
  for (i = 0; i < 11; i++) {
    info->Topt[i] = 0.1 * (double)i;
  }
  info->Slack = z[180];
}

/*
 * File trailer for nlmpcmoveCodeGeneration.c
 *
 * [EOF]
 */
