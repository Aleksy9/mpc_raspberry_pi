/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evalObjAndConstr.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "evalObjAndConstr.h"
#include "all.h"
#include "checkVectorNonFinite.h"
#include "cost_fct_3D_model.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include "state_update_3D_model.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int c_obj_next_next_next_next_next_
 *                const i_struct_T *d_obj_next_next_next_next_next_
 *                const k_struct_T *e_obj_next_next_next_next_next_
 *                const double x[181]
 *                double Cineq_workspace_data[]
 *                int ineq0
 *                double Ceq_workspace[160]
 *                double *fval
 *                int *status
 * Return Type  : void
 */
void evalObjAndConstr(int c_obj_next_next_next_next_next_,
                      const i_struct_T *d_obj_next_next_next_next_next_,
                      const k_struct_T *e_obj_next_next_next_next_next_,
                      const double x[181], double Cineq_workspace_data[],
                      int ineq0, double Ceq_workspace[160], double *fval,
                      int *status)
{
  static double c_data[102400];
  double b_c_data[320];
  double c[320];
  double X[176];
  double b_x[160];
  double U[44];
  double Umv[44];
  int b_i;
  int i;
  int k;
  int yk;
  short tmp_data[320];
  memset(&X[0], 0, 176U * sizeof(double));
  memcpy(&b_x[0], &x[0], 160U * sizeof(double));
  for (i = 0; i < 16; i++) {
    for (yk = 0; yk < 10; yk++) {
      X[(yk + 11 * i) + 1] = b_x[i + (yk << 4)];
    }
    X[11 * i] = e_obj_next_next_next_next_next_->runtimedata.x[i];
  }
  *fval = cost_fct_3D_model(
      X, e_obj_next_next_next_next_next_->userdata.References);
  *status = 1;
  if (rtIsInf(*fval) || rtIsNaN(*fval)) {
    if (rtIsNaN(*fval)) {
      *status = -3;
    } else if (*fval < 0.0) {
      *status = -1;
    } else {
      *status = -2;
    }
  }
  if (*status == 1) {
    double b_X[176];
    double a[40];
    double a_tmp;
    double b_a;
    double e;
    int ineqRange_data[320];
    int n;
    short ic[16];
    short input_sizes_idx_0;
    signed char sizes_idx_1;
    bool bv[160];
    bool c_x[16];
    bool exitg1;
    bool guard1 = false;
    bool y;
    if (c_obj_next_next_next_next_next_ - 1 < 0) {
      n = 0;
    } else {
      n = (unsigned short)(c_obj_next_next_next_next_next_ - 1) + 1;
    }
    if (n > 0) {
      ineqRange_data[0] = 0;
      yk = 0;
      for (k = 2; k <= n; k++) {
        yk++;
        ineqRange_data[k - 1] = yk;
      }
    }
    yk = n - 1;
    for (i = 0; i <= yk; i++) {
      ineqRange_data[i] += ineq0;
    }
    memset(&X[0], 0, 176U * sizeof(double));
    memset(&Umv[0], 0, 44U * sizeof(double));
    for (i = 0; i < 40; i++) {
      a_tmp = 0.0;
      for (yk = 0; yk < 20; yk++) {
        a_tmp += (double)iv[i + 40 * yk] * x[yk + 160];
      }
      a[i] = a_tmp;
    }
    for (i = 0; i < 4; i++) {
      for (yk = 0; yk < 10; yk++) {
        Umv[yk + 11 * i] = a[i + (yk << 2)];
      }
    }
    e = x[180];
    memcpy(&b_x[0], &x[0], 160U * sizeof(double));
    for (i = 0; i < 16; i++) {
      for (yk = 0; yk < 10; yk++) {
        X[(yk + 11 * i) + 1] = b_x[i + (yk << 4)];
      }
      X[11 * i] = d_obj_next_next_next_next_next_->x[i];
    }
    for (b_i = 0; b_i < 4; b_i++) {
      Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
      memcpy(&U[b_i * 11], &Umv[b_i * 11], 11U * sizeof(double));
    }
    memset(&Ceq_workspace[0], 0, 160U * sizeof(double));
    for (i = 0; i < 16; i++) {
      ic[i] = (short)(i + 1);
    }
    for (i = 0; i < 11; i++) {
      yk = i << 2;
      Umv[yk] = U[i];
      Umv[yk + 1] = U[i + 11];
      Umv[yk + 2] = U[i + 22];
      Umv[yk + 3] = U[i + 33];
    }
    for (i = 0; i < 11; i++) {
      for (yk = 0; yk < 16; yk++) {
        b_X[yk + (i << 4)] = X[i + 11 * yk];
      }
    }
    a_tmp = d_obj_next_next_next_next_next_->Parameters[0] / 2.0;
    b_a = d_obj_next_next_next_next_next_->Parameters[0] / 6.0;
    for (b_i = 0; b_i < 10; b_i++) {
      double c_X[16];
      double dv[16];
      double k1[16];
      double k2[16];
      double k3[16];
      /*  States = {x,y,Vx,Vy,theta, omega} */
      /*  Inputs = {T, alpha_t} */
      /*  RK4 */
      yk = b_i << 4;
      k = b_i << 2;
      state_deriv(&b_X[yk], &Umv[k], k1);
      for (i = 0; i < 16; i++) {
        c_X[i] = b_X[i + yk] + a_tmp * k1[i];
      }
      state_deriv(c_X, &Umv[k], k2);
      for (i = 0; i < 16; i++) {
        c_X[i] = b_X[i + yk] + a_tmp * k2[i];
      }
      state_deriv(c_X, &Umv[k], k3);
      /*  disp("state") */
      /*  disp(state) */
      /*  disp("new_state") */
      /*  disp(new_state) */
      /* aero_force_x = - 1/(2)*rho*S*V* ( Cd*(vx*cos(theta) + vy*sin(theta)));
       */
      /* aero_force_y = - 1/(2)*rho*S*V* ( (CLa + Cd) * (-vx*sin(theta) +
       * vy*cos(theta)) ); */
      for (i = 0; i < 16; i++) {
        c_X[i] = b_X[i + yk] +
                 d_obj_next_next_next_next_next_->Parameters[0] * k3[i];
      }
      state_deriv(c_X, &Umv[k], dv);
      for (i = 0; i < 16; i++) {
        input_sizes_idx_0 = ic[i];
        Ceq_workspace[input_sizes_idx_0 - 1] =
            b_X[i + ((b_i + 1) << 4)] -
            (b_X[i + yk] +
             b_a * (((k1[i] + 2.0 * k2[i]) + 2.0 * k3[i]) + dv[i]));
        input_sizes_idx_0 = (short)(input_sizes_idx_0 + 16);
        ic[i] = input_sizes_idx_0;
      }
    }
    for (i = 0; i < 160; i++) {
      bv[i] = rtIsInf(d_obj_next_next_next_next_next_->OutputMin[i]);
    }
    all(bv, c_x);
    y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 16)) {
      if (!c_x[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
    guard1 = false;
    if (y) {
      for (i = 0; i < 160; i++) {
        bv[i] = rtIsInf(d_obj_next_next_next_next_next_->OutputMax[i]);
      }
      all(bv, c_x);
      y = true;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k < 16)) {
        if (!c_x[k]) {
          y = false;
          exitg1 = true;
        } else {
          k++;
        }
      }
      if (y) {
        k = 0;
        yk = 0;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      bool icf[320];
      for (b_i = 0; b_i < 320; b_i++) {
        c[b_i] = 0.0;
        icf[b_i] = true;
      }
      for (i = 0; i < 16; i++) {
        ic[i] = (short)(i + 1);
      }
      for (b_i = 0; b_i < 10; b_i++) {
        bool bv1[16];
        for (i = 0; i < 16; i++) {
          yk = b_i + 10 * i;
          a_tmp = d_obj_next_next_next_next_next_->OutputMin[yk];
          icf[ic[i] - 1] = ((!rtIsInf(a_tmp)) && (!rtIsNaN(a_tmp)));
          a_tmp = d_obj_next_next_next_next_next_->OutputMax[yk];
          c_x[i] = rtIsInf(a_tmp);
          bv1[i] = rtIsNaN(a_tmp);
        }
        for (i = 0; i < 16; i++) {
          icf[ic[i] + 15] = ((!c_x[i]) && (!bv1[i]));
        }
        y = false;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k <= 31)) {
          int b_ic[32];
          for (i = 0; i < 16; i++) {
            input_sizes_idx_0 = ic[i];
            b_ic[i] = input_sizes_idx_0 - 1;
            b_ic[i + 16] = input_sizes_idx_0 + 15;
          }
          if (icf[b_ic[k]]) {
            y = true;
            exitg1 = true;
          } else {
            k++;
          }
        }
        if (y) {
          for (i = 0; i < 16; i++) {
            c[ic[i] - 1] =
                (d_obj_next_next_next_next_next_->OutputMin[b_i + 10 * i] - e) -
                X[(b_i + 11 * i) + 1];
          }
          for (i = 0; i < 16; i++) {
            c[ic[i] + 15] =
                (X[(b_i + 11 * i) + 1] -
                 d_obj_next_next_next_next_next_->OutputMax[b_i + 10 * i]) -
                e;
          }
        }
        for (i = 0; i < 16; i++) {
          ic[i] = (short)(ic[i] + 32);
        }
      }
      k = 0;
      yk = 0;
      for (b_i = 0; b_i < 320; b_i++) {
        if (icf[b_i]) {
          k++;
          tmp_data[yk] = (short)(b_i + 1);
          yk++;
        }
      }
      for (i = 0; i < k; i++) {
        b_c_data[i] = c[tmp_data[i] - 1];
      }
      yk = 1;
      if (k - 1 >= 0) {
        memcpy(&c[0], &b_c_data[0], (unsigned int)k * sizeof(double));
      }
    }
    sizes_idx_1 = (signed char)((k != 0) && (yk != 0));
    if ((sizes_idx_1 == 0) || ((k != 0) && (yk != 0))) {
      input_sizes_idx_0 = (short)k;
    } else {
      input_sizes_idx_0 = 0;
    }
    yk = sizes_idx_1;
    for (i = 0; i < yk; i++) {
      k = input_sizes_idx_0;
      if (k - 1 >= 0) {
        memcpy(&c_data[0], &c[0], (unsigned int)k * sizeof(double));
      }
    }
    for (i = 0; i < n; i++) {
      Cineq_workspace_data[ineqRange_data[i] - 1] = c_data[i];
    }
    *status = checkVectorNonFinite(c_obj_next_next_next_next_next_,
                                   Cineq_workspace_data, ineq0);
    if (*status == 1) {
      *status = b_checkVectorNonFinite(Ceq_workspace);
    }
  }
}

/*
 * File trailer for evalObjAndConstr.c
 *
 * [EOF]
 */
